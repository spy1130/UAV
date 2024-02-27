import sensor, image, time, math
from pyb import UART

uart3 = UART(3,115200)#与飞机

thresholds = [(0, 100, 41, 127, -6, 127)] # generic_red_thresholds
thresholdc = [(21, 100, -32, 127, -128, -46)] # generic_blue_thresholds
black_threshold = (22, 37, -37, 10, -35, 1)
sensor.reset() #初始化设置
sensor.set_pixformat(sensor.RGB565) #设置为彩色
sensor.set_framesize(sensor.QVGA) #设置清晰度
sensor.skip_frames(time = 2000) #跳过前2000ms的图像
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

a=1
a=''

while(True): #不断拍照
    clock.tick()
    if (uart3.any()):   # 更新串口接收数据
        recv_data = uart3.read()  #接收读取的字符串
        a=int(recv_data[0])
    img = sensor.snapshot().lens_corr(1.8)
#检测“十”起降点
#(0, 10, -19, 127, -18, 127)
    if(a==1):
        cir = img.find_circles(threshold = 2500, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 1, r_max = 100, r_step = 2)
        if cir :
            for c in cir :
                area = (c.x()-c.r(), c.y()-c.r(), 2*c.r(), 2*c.r())
                #area为识别到的圆的区域，即圆的外接矩形框
                statistics = img.get_statistics(roi=area)#像素颜色统计
                if 22<statistics.l_mode()<37 and -37<statistics.a_mode()<10 and -35<statistics.b_mode()<1:#if the circle is red
                    print("black",c.x(),c.y())
                    img.draw_cross(c.x(), c.y()) # 在物体的中心点(cx,xy)画一个十字
                    img.draw_circle(c.x(), c.y(), c.r(), color = (255, 0, 0))#识别到的红色圆形用红色的圆框出来
                    x_L8 = int(c.x()) & 0x00FF #取低八位
                    x_H8 = (int(c.x())>>8) & 0x00FF #取高八位
                    y_L8 = int(c.y()) & 0x00FF #取低八位
                    y_H8 = (int(c.y())>>8) & 0x00FF #取高八位
                    data1 = bytearray([0x08,x_L8,x_H8,y_L8,y_H8,0x0A])
                    uart3.write(data1)
                else:
                    print("9")
                    data1=bytearray([0x09,0x0A])
                    uart3.write(data1)
#检测图形
    elif(a==2):
        blobs = img.find_blobs(thresholds,pixels_threshold=10,area_threshold=10)
        blobz = img.find_blobs(thresholdc,pixels_threshold=10,area_threshold=10)
        if blobs:
            for blob in blobs:
                print('该形状占空比为',blob.density())
                if blob.solidity()>0.9 or blob.density()>0.84:
                    print("检测为红长方形  ",end='')
                    img.draw_rectangle(blob.rect(),color = (255, 0, 0))
                    print("(%d,%d)",(blob.cx(),blob.cy()))
                    x1_L8 = int(blob.cx()) & 0x00FF #取低八位
                    x1_H8 = (int(blob.cx())>>8) & 0x00FF #取高八位
                    y1_L8 = int(blob.cy()) & 0x00FF #取低八位
                    y1_H8 = (int(blob.cy())>>8) & 0x00FF #取高八位
                    data1 = bytearray([0x01,x1_L8,x1_H8,y1_L8,y1_H8,0x0A])
                    uart3.write(data1)
                elif blob.density()>0.6:
                    print("检测为红圆  ",end='')
                    img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
                    img.draw_circle((blob.cx(), blob.cy(),int((blob.w()+blob.h())/4)),color = (255, 0, 0))
                    print("(%d,%d)",(blob.cx(),blob.cy()))
                    x2_L8 = int(blob.cx()) & 0x00FF #取低八位
                    x2_H8 = (int(blob.cx())>>8) & 0x00FF #取高八位
                    y2_L8 = int(blob.cy()) & 0x00FF #取低八位
                    y2_H8 = (int(blob.cy())>>8) & 0x00FF #取高八位
                    data2 = bytearray([0x02,x2_L8,x2_H8,y2_L8,y2_H8,0x0A])
                    uart3.write(data2)
                elif blob.density()>0.40:
                    print("检测为红三角型  ",end='')
                    img.draw_cross(blob.cx(), blob.cy(),color = (255, 0, 0))
                    print("(%d,%d)",(blob.cx(),blob.cy()))
                    x3_L8 = int(blob.cx()) & 0x00FF #取低八位
                    x3_H8 = (int(blob.cx())>>8) & 0x00FF #取高八位
                    y3_L8 = int(blob.cy()) & 0x00FF #取低八位
                    y3_H8 = (int(blob.cy())>>8) & 0x00FF #取高八位
                    data3 = bytearray([0x03,x3_L8,x3_H8,y3_L8,y3_H8,0x0A])
                    uart3.write(data3)
                else: #基本上占空比小于0.4的都是干扰或者三角形，索性全忽略了。
                    print("no dectedtion")
                    data4 = bytearray([0x09,0x0A])
                    uart3.write(data4)
        elif blobz:
            for blob in blobz:
                print('该形状占空比为',blob.density())
                if blob.solidity()>0.9 or blob.density()>0.84:
                    print("检测为蓝长方形  ",end='')
                    img.draw_rectangle(blob.rect())
                    print("(%d,%d)",(blob.cx(),blob.cy()))
                    x5_L8 = int(blob.cx()) & 0x00FF #取低八位
                    x5_H8 = (int(blob.cx())>>8) & 0x00FF #取高八位
                    y5_L8 = int(blob.cy()) & 0x00FF #取低八位
                    y5_H8 = (int(blob.cy())>>8) & 0x00FF #取高八位
                    data5 = bytearray([0x05,x5_L8,x5_H8,y5_L8,y5_H8,0x0A])
                    uart3.write(data5)
                elif blob.density()>0.6:
                    print("检测为蓝圆  ",end='')
                    img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
                    img.draw_circle((blob.cx(), blob.cy(),int((blob.w()+blob.h())/4)))
                    print("(%d,%d)",(blob.cx(),blob.cy()))
                    x6_L8 = int(blob.cx()) & 0x00FF #取低八位
                    x6_H8 = (int(blob.cx())>>8) & 0x00FF #取高八位
                    y6_L8 = int(blob.cy()) & 0x00FF #取低八位
                    y6_H8 = (int(blob.cy())>>8) & 0x00FF #取高八位
                    data6 = bytearray([0x06,x6_L8,x6_H8,y6_L8,y6_H8,0x0A])
                    uart3.write(data6)
                elif blob.density()>0.40:
                    print("检测为蓝三角型  ",end='')
                    img.draw_cross(blob.cx(), blob.cy())
                    print("(%d,%d)",(blob.cx(),blob.cy()))
                    x7_L8 = int(blob.cx()) & 0x00FF #取低八位
                    x7_H8 = (int(blob.cx())>>8) & 0x00FF #取高八位
                    y7_L8 = int(blob.cy()) & 0x00FF #取低八位
                    y7_H8 = (int(blob.cy())>>8) & 0x00FF #取高八位
                    data7 = bytearray([0x07,x7_L8,x7_H8,y7_L8,y7_H8,0x0A])
                    uart3.write(data7)
                else: #基本上占空比小于0.4的都是干扰或者三角形，索性全忽略了。
                    print("no dectedtion")
                    data8 = bytearray([0x09,0x0A])
                    uart3.write(data8)
        else:
            print("9")
            data9=bytearray([0x09,0x0A])
            uart3.write(data9)
