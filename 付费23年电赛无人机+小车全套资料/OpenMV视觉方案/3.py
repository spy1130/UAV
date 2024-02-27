import sensor, image, time ,pyb
from pyb import UART

uart3 = UART(3,115200)#与飞机

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

clock = time.clock()

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

#a=2
a=''

while(True):
    clock.tick()
    if (uart3.any()):   # 更新串口接收数据
        recv_data = uart3.read()  #接收读取的字符串
        a=int(recv_data[0])
    #img = sensor.snapshot().lens_corr(1.8)
    img = sensor.snapshot().lens_corr(strength = 2.4, zoom = 1.0)
    if(a==1):
        blobs = img.find_blobs([(0, 21, 1, 127, -5, 6)],area_threshold=3,pixels_threshold=3)
        if blobs:
            max_blob = find_max(blobs)
            #c = blobs[0]
            x=max_blob[5]
            y=max_blob[6]
            img.draw_cross(max_blob[5], max_blob[6]) # 在物体的中心点(cx,xy)画一个十字
            x2_L8 = int(max_blob[5]) & 0x00FF #取低八位
            x2_H8 = (int(max_blob[5])>>8) & 0x00FF #取高八位
            y2_L8 = int(max_blob[6]) & 0x00FF #取低八位
            y2_H8 = (int(max_blob[6])>>8) & 0x00FF #取高八位
            data1 = bytearray([0x01,x2_L8,x2_H8,y2_L8,y2_H8,0x0A])
            print("(%d,%d)" %(int(max_blob[5]),int(max_blob[6])))
            uart3.write(data1)#返回矩形中心x坐标和矩形宽度差值，x大于-50小于50就可以，宽度大于120小于200就可以
        else:
            print("9")
            data1=bytearray([0x09,0x0A])
            uart3.write(data1)
    elif(a==2):
        for l in img.find_lines(threshold = 600, roi=(0, 0, 160, 60),theta_margin = 25, rho_margin = 25):
            if (min_degree <= l.theta()) and (l.theta() <= max_degree):
                img.draw_line(l.line(), color = (255, 0, 0))
                rho_err = img.height()/2-abs(l.rho())
                if l.theta()>180:
                    theta_err = l.theta()-270
                else:
                    theta_err = l.theta()-90
                rho_L8 = int(rho_err) & 0x00FF #取低八位
                rho_H8 = (int(rho_err)>>8) & 0x00FF #取高八位
                theta_L8 = int(theta_err) & 0x00FF #取低八位
                theta_H8 = (int(theta_err)>>8) & 0x00FF #取高八位
                print(l.rho(),l.theta(),rho_err,theta_err)
                data2 = bytearray([0x02,rho_L8,rho_H8,theta_L8,theta_H8,0x0A])
                uart3.write(data2)
            else:
                print("9")
                data2 = bytearray([0x09,0x0A])
                uart3.write(data2)
    elif(a==3):
        for l in img.find_lines(threshold = 600, roi=(80, 0, 80, 120),theta_margin = 25, rho_margin = 25):
            if (min_degree > l.theta()) or (l.theta() > max_degree):
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
                print(l.rho(),l.theta(),rho_err,theta_err)
                data3 = bytearray([0x03,rho_L8,rho_H8,theta_L8,theta_H8,0x0A])
                uart3.write(data3)
            else:
                print("9")
                data3 = bytearray([0x09,0x0A])
                uart3.write(data3)
    else:
        print("9")
        data4 = bytearray([0x09,0x0A])
        uart3.write(data4)
