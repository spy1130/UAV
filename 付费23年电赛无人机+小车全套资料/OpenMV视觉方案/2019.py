#OPENMV平
#无二值化有宽度
#设置阈值，（0，100）检测黑色线
THRESHOLD = (0, 40) # Grayscale threshold for dark things...
#THRESHOLD = (135, 255)#白线

import sensor, image, time, pyb
from pyb import UART

uart3 = UART(3,115200)#与飞机
#uart1 = UART(3,115200)#与OPENMV斜

RED_LED_PIN = 1
BLUE_LED_PIN = 3

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # 在进行颜色追踪时，必须关闭
sensor.set_auto_whitebal(False) # 在进行颜色追踪时，必须关闭
clock = time.clock()

a=''
o0=''
o1=''
o2=''
o3=''
o4=''
take_flag=''
take_flag=1
#a=2

while(True):
    clock.tick()
    if (uart3.any()):   # 更新串口接收数据
        recv_data = uart3.read()  #接收读取的字符串
        a=int(recv_data[0])
        #a=int(recv_data[0])-48
        #print(a,b)
    img = sensor.snapshot()
    #img = sensor.snapshot().binary([(90, 100, -128, 127, -128, 127)], invert=False, zero=True)
    #img.histeq(adaptive=True, clip_limit=3)
    if(a==1):
        take_flag=1##############################
        #检测红色杆
        #(0, 40, -1, 40, 2, 35)
        #(0, 56, 10, 65, -8, 60)
        blobs = img.find_blobs([(9, 66, 9, 127, 1, 54)],area_threshold=1000,pixels_threshold=1500)
        #blobs = img.find_blobs([(0, 56, 10, 65, -8, 60)],area_threshold=5,pixels_threshold=5)
        if blobs:
            c = blobs[0]
            x=c[5]-160
            y=c[6]
            img.draw_cross(c[5], c[6]) # 在物体的中心点(cx,xy)画一个十字
            x_L8 = int(x) & 0x00FF #取低八位
            x_H8 = (int(x)>>8) & 0x00FF #取高八位
            data1 = bytearray([0x01,x_L8,x_H8,0x0A])
            print("%d" %x)
            uart3.write(data1)
            #a = ''  # 重置接收缓冲区
        else:
            print("no pole")
            data0=bytearray([0,0x0A])
            uart3.write(data0)
    elif(a==2):
        take_flag=1##############################
        #黄色条形码检测
        blobh = img.find_blobs([(16, 100, -27, 16, 29, 66)],area_threshold=20,pixels_threshold=50,merge=True,margin=50)
        #(16, 100, -27, 5, 18, 53)
        #(31, 90, -47, 28, 31, 73)
        #blobh = img.find_blobs([(5, 21, -52, 27, 10, 34),(40, 100, -17, 17, 12, 57)],merge=True,margin=20,pixel_threshold=30)正光和背光
        if blobh:
            h = blobh[0]
            x2=h[5]-160
            y2=h[6]-120
            #w=h[2]
            #img.draw_rectangle(x2, y2, w, h, color = (255, 0, 0))
            img.draw_rectangle(h[0], h[1], h[2], h[3], color = (255, 0, 0))
            x2_L8 = int(x2) & 0x00FF #取低八位
            x2_H8 = (int(x2)>>8) & 0x00FF #取高八位
            y2_L8 = int(y2) & 0x00FF #取低八位
            y2_H8 = (int(y2)>>8) & 0x00FF #取高八位
            data2 = bytearray([0x02,x2_L8,x2_H8,y2_L8,y2_H8,0x0A])
            print("(%d,%d)" %(x2,y2))
            uart3.write(data2)#返回矩形中心x坐标和矩形宽度差值，x大于-50小于50就可以，宽度大于120小于200就可以
        else:
            print("no core")
            data0=bytearray([0,0x0A])
            uart3.write(data0)
#黄色条形码拍照
    elif(a==3 and take_flag==1):
        #img.to_grayscale()
        sensor.set_pixformat(sensor.GRAYSCALE)
        sensor.set_framesize(sensor.VGA)
        #img.to_grayscale()
        #for code in img.find_barcodes():
            #print(code.payload())
        for i in range(2):
            pyb.delay(100)#############
            pyb.LED(BLUE_LED_PIN).on()
            img = sensor.snapshot()
            filename = "barcodes_" + str(i+1) + ".jpg"
            img.save(filename)
            pyb.LED(BLUE_LED_PIN).off()
            sensor.skip_frames(time=300)
            print("txcore is ok")
        take_flag=0
        data3=bytearray([0x04,0x0A])
        sensor.set_pixformat(sensor.RGB565)#########################
        sensor.set_framesize(sensor.QVGA)############################
        uart3.write(data3)
    elif(a==3 and take_flag==0):
        data3=bytearray([0x04,0x0A])
        uart3.write(data3)
    elif(a==5):
        blobe = img.find_blobs([(0, 51, -37, 15, -32, 36)],roi=(30, 60, 260, 120),area_threshold=1,pixels_threshold=1,merge=True,margin=2)
        #for blob in blobe:
            #img.draw_rectangle(blob.rect(), color = (255, 0, 0))
        if blobe:
            e = blobe[0]
            w5=e[2]
            h5=e[3]
            #img.draw_rectangle(x2, y2, w, h, color = (255, 0, 0))
            img.draw_rectangle(e[0], e[1], e[2], e[3], color = (255, 0, 0))
            w5_L8 = int(w5) & 0x00FF #取低八位
            w5_H8 = (int(w5)>>8) & 0x00FF #取高八位
            h5_L8 = int(h5) & 0x00FF #取低八位
            h5_H8 = (int(h5)>>8) & 0x00FF #取高八位
            data5 = bytearray([0x05,w5_L8,w5_H8,h5_L8,h5_H8,0x0A])
            print("(%d,%d)" %(w5,h5))
            uart3.write(data5)#返回矩形宽度差值和高度差值，w和h大于80小于120就可以
        else:
            data5=bytearray([0,0x0A])
            uart3.write(data5)
#黑白二维码拍照
    elif(a==6 and take_flag==1):
        #img.to_grayscale()
        sensor.set_pixformat(sensor.GRAYSCALE)
        sensor.set_framesize(sensor.VGA)
        #img.to_grayscale()
        #for code in img.find_barcodes():
            #print(code.payload())
        for i in range(2):
            pyb.delay(100)#############
            pyb.LED(BLUE_LED_PIN).on()
            img = sensor.snapshot()
            filename = "ewcodes_" + str(i+1) + ".jpg"
            img.save(filename)
            pyb.LED(BLUE_LED_PIN).off()
            sensor.skip_frames(time=300)
            print("ewcore is ok")
        take_flag=0
        data6=bytearray([0x04,0x0A])
        sensor.set_pixformat(sensor.RGB565)#########################
        sensor.set_framesize(sensor.QVGA)############################
        uart3.write(data6)
    elif(a==6 and take_flag==0):
        data6=bytearray([0x04,0x0A])
        uart3.write(data6)
#红色圆心
    #elif(a==7):
        #for c in img.find_circles(threshold = 3500, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 2, r_max = 100, r_step = 2):
        #area = (c.x()-c.r(), c.y()-c.r(), 2*c.r(), 2*c.r())
        #statistics = img.get_statistics(roi=area)#像素颜色统计
        #if 0<statistics.l_mode()<100 and 0<statistics.a_mode()<127 and 0<statistics.b_mode()<127:#if the circle is red
            #print("red",c.x(),c.y())
            #data7 = bytearray([7,c.x(),c.y(),0x0A])
            #uart3.write(data7)
#    else:
#        print("no")

