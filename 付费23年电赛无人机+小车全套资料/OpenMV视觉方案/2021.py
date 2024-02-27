import sensor, image, time, pyb
from pyb import UART

uart3 = UART(3,115200)#与飞机
uart1 = UART(1,115200)#与飞机
#uart1 = UART(3,115200)#与OPENMV斜

min_degree = 60   #0
max_degree = 120  #179

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
#预设大小   窗口宽度    窗口高度
#VGA        640         480
#QVGA       320         240
#QQVGA      160         120
#视觉中心点：（80，60）
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # 在进行颜色追踪时，必须关闭
sensor.set_auto_whitebal(False) # 在进行颜色追踪时，必须关闭
clock = time.clock()

#a=1
a=''
o0=''
o1=''
o2=''
o3=''
o4=''

while(True):
    clock.tick()
    if (uart3.any()):   # 更新串口接收数据
        recv_data = uart3.read()  #接收读取的字符串
        a=int(recv_data[0])
    img = sensor.snapshot().lens_corr(1.8)
    #img = sensor.snapshot().binary([(90, 100, -128, 127, -128, 127)], invert=False, zero=True)
    #img.histeq(adaptive=True, clip_limit=3)
#检测“十”起降点
#(0, 10, -19, 127, -18, 127)
    if(a==1):
        cir = img.find_circles(threshold = 3000, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 1, r_max = 100, r_step = 2)
        if cir :
            for c in cir :
            #area = (c.x()-c.r(), c.y()-c.r(), 2*c.r(), 2*c.r())
            #area为识别到的圆的区域，即圆的外接矩形框
            #statistics = img.get_statistics(roi=area)#像素颜色统计
            #if 0<statistics.l_mode()<10 and -19<statistics.a_mode()<127 and -18<statistics.b_mode()<127:#if the circle is red
                print("black",c.x()-80,60-c.y())
                img.draw_cross(c.x(), c.y()) # 在物体的中心点(cx,xy)画一个十字
                img.draw_circle(c.x(), c.y(), c.r(), color = (255, 0, 0))#识别到的红色圆形用红色的圆框出来
                x_L8 = int(c.x()) & 0x00FF #取低八位
                x_H8 = (int(c.x())>>8) & 0x00FF #取高八位
                y_L8 = int(c.y()) & 0x00FF #取低八位
                y_H8 = (int(c.y())>>8) & 0x00FF #取高八位
                data1 = bytearray([0x01,x_L8,x_H8,y_L8,y_H8,0x0A])
                #data1 = bytearray([0x01,0x02,0x03,0x04,0x0A])
                uart3.write(data1)
        else:
            print("9")
            #data1=bytearray([9,0x0A])
            #uart3.write(data1)
            data1 = bytearray([0x09,33,0,3,0,0x0A])#测试串口
            uart3.write(data1)
            data1 = bytearray([0x09,11,0,1,0,0x0A])#测试串口
            uart1.write(data1)
#检测A
    elif(a==2):
        blobs = img.find_blobs([(0, 10, -19, 127, -18, 127)],area_threshold=3,pixels_threshold=3)
        if blobs:
            c = blobs[0]
            x=c[5]
            y=c[6]
            img.draw_cross(c[5], c[6]) # 在物体的中心点(cx,xy)画一个十字
            x2_L8 = int(c[5]) & 0x00FF #取低八位
            x2_H8 = (int(c[5])>>8) & 0x00FF #取高八位
            y2_L8 = int(c[6]) & 0x00FF #取低八位
            y2_H8 = (int(c[6])>>8) & 0x00FF #取高八位
            data2 = bytearray([0x02,x2_L8,x2_H8,y2_L8,y2_H8,0x0A])
            print("(%d,%d)" %(int(c[5]),int(c[6])))
            uart3.write(data2)#返回矩形中心x坐标和矩形宽度差值，x大于-50小于50就可以，宽度大于120小于200就可以
        else:
            data2=bytearray([0,0x0A])
            uart3.write(data2)
#绿色播撒
#(60, 100, -69, -15, -18, 127)
    elif(a==3):
        blob = img.find_blobs([(60, 100, -69, -15, -18, 127)],roi=(40, 40, 80, 40),area_threshold=10, pixels_threshold=10, merge=False)
        for l in img.find_lines(threshold = 1000, theta_margin = 25, rho_margin = 25):
            if (min_degree <= l.theta()) and (l.theta() <= max_degree):
                img.draw_line(l.line(), color = (255, 0, 0))
                rho_err = abs(l.rho())-img.height()/2
                if l.theta()>180:
                    theta_err = l.theta()-270
                else:
                    theta_err = l.theta()-90
                rho_L8 = int(rho_err) & 0x00FF #取低八位
                rho_H8 = (int(rho_err)>>8) & 0x00FF #取高八位
                theta_L8 = int(theta_err) & 0x00FF #取低八位
                theta_H8 = (int(theta_err)>>8) & 0x00FF #取高八位
                if blob:
                    for b in blob:
                        img.draw_cross(b[5], b[6])
                        FIND = 1
                        data3=bytearray([0x03,rho_L8,rho_H8,theta_L8,theta_H8,1,0x0A])
                        print(l.rho(),l.theta(),rho_err,theta_err,1)
                        uart3.write(data3)
                else:
                    FIND = 0
                    data3=bytearray([0x03,rho_L8,rho_H8,theta_L8,theta_H8,0,0x0A])
                    print(l.rho(),l.theta(),rho_err,theta_err,0)
                    #data3=bytearray([0,0x0A])
                    uart3.write(data3)
            else:
                img.draw_line(l.line(), color = (0, 255, 0))
                rho_err = abs(l.rho())-img.width()/2
                if l.theta()>90:
                    theta_err = l.theta()-180
                else:
                    theta_err = l.theta()
                rho_L8 = int(rho_err) & 0x00FF #取低八位
                rho_H8 = (int(rho_err)>>8) & 0x00FF #取高八位
                theta_L8 = int(theta_err) & 0x00FF #取低八位
                theta_H8 = (int(theta_err)>>8) & 0x00FF #取高八位
                if blob:
                    for b in blob:
                        img.draw_cross(b[5], b[6])
                        FIND = 1
                        data3=bytearray([0x03,rho_L8,rho_H8,theta_L8,theta_H8,1,0x0A])
                        print(l.rho(),l.theta(),rho_err,theta_err,1)
                        uart3.write(data3)
                else:
                    FIND = 0
                    data3=bytearray([0x03,rho_L8,rho_H8,theta_L8,theta_H8,0,0x0A])
                    print(l.rho(),l.theta(),rho_err,theta_err,0)
                    #data3=bytearray([0,0x0A])
                    uart3.write(data3)
#黑白条形码检测
    elif(a==4):
    #位置确定
        blobh = img.find_blobs([(0, 51, -37, 15, -32, 36)],merge=True,margin=20)
        if blobh:
            h = blobh[0]
            x2=h[5]-160
            w=h[2]
            #img.draw_rectangle(x2, y2, w, h, color = (255, 0, 0))
            img.draw_rectangle(h[0], h[1], h[2], h[3], color = (255, 0, 0))
            x2_L8 = int(x2) & 0x00FF #取低八位
            x2_H8 = (int(x2)>>8) & 0x00FF #取高八位
            w_L8 = int(w) & 0x00FF #取低八位
            w_H8 = (int(w)>>8) & 0x00FF #取高八位
            data4 = bytearray([0x04,x2_L8,x2_H8,w_L8,w_H8,0x0A])
            print("(%d,%d,%d)" %(x2,w,h.pixels()))
            uart3.write(data4)#返回矩形中心x坐标和矩形宽度差值，x大于-50小于50就可以，宽度大于120小于200就可以
        else:
            data4=bytearray([0,0x0A])
            uart3.write(data4)
#黑白条形码读取
    elif(a==5):
        for code in img.find_barcodes():
            print(code.payload())
            b = int(code.payload())
            data5 = bytearray([0x05,b,0x0A])
            uart3.write(data5)
    else:
        print("no")

