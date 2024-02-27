import sensor, image, time, machine
from pyb import UART,Pin

# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.RGB565)#GRAYSCALE
sensor.set_framesize(sensor.QQVGA) #320*240
#sensor.set_hmirror(True)#图像反转
#sensor.set_vflip(True)
sensor.set_auto_gain(True)      # 关闭自动增益     True
#sensor.set_auto_whitebal(False)  # 关闭自动白平衡  False
sensor.skip_frames(time=2000)
#sensor.set_contrast(3)#设置相机图像对比度 -3至+3
#sensor.set_saturation(3)#设置相机图像饱和度 -3至+3
#sensor.set_auto_exposure(True)#自动曝光

clock = time.clock()

Black_Threshold_1 = (0, 29, -5, 34, -10, 10)#(11, 29, -16, 31, -11, 22)#起点色块
Black_Threshold = (0,100)#(0, 27, -24, 39, -41, 40)#(0, 30, -19, 127, -18, 127)#(1, 27, 6, 38, -24, 31)
Yellow_Threshold = (13, 49, 18, 61, 6, 47)
Red_Threshold = (38, 57, 31, 87, 20, 81)

ROI_Threshold = (0,0,320,240)
White_Threshold = (252,255)  # 白色灰度
Find_Threshold = (0,0,0,0,0,0)

uart = UART(3,115200)        #初始化串口3

#Flag = ''
Flag = 2
Flag_last = 0


#最大的色块
def max_blob(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob
#def find_maxblob_black(blobs):
    #if blobs:
        #max_n = 0
        #max_area = 0
        #n=0
        #for b in blobs:
            #if b.area() > max_area:
                #max_area = b.area()
                #max_n = n
            #n += 1
        #return blobs[max_n]
    #else:return None

def find_high_black(blobs):
    if blobs:
        max_n = 0
        max_h = 0
        n=0
        for b in blobs:
            if b.h() > max_h and b.w()<50:
                max_h = b.h()
                max_n = n
            n += 1
        return blobs[max_n]
    else:return None

def find_width_black(blobs):
    if blobs:
        max_n = 0
        max_w = 0
        n=0
        for b in blobs:
            if b.w() > max_w and b.h()<50:
                max_w = b.w()
                max_n = n
            n += 1
        return blobs[max_n]
    else:return None

while True:
    clock.tick()
    #if (uart.any()):   # 更新串口接收数据
        #recv_data = uart.read()  #接收读取的字符串
        #Flag = int(recv_data[0])
        #print(Flag)
    #img = sensor.snapshot().lens_corr(1.8)
    #img = sensor.snapshot().lens_corr(strength = 2.4, zoom = 1.0)
    img = sensor.snapshot().lens_corr(1.8).histeq(adaptive=True, clip_limit=5)#增加对比度

    #Flag = uart.readchar()
    #Flag = int(Flag)
    #print(Flag)

    #Flag = 2

    if Flag == 1:
        Find_Threshold = Black_Threshold_1
        ROI_Threshold = (0,0,320,240)
    #elif Flag == 1:
        #Find_Threshold = Red_Threshold
        #ROI_Threshold = (0,0,320,240)
    #elif Flag == 2:#宽1
        #Find_Threshold = Black_Threshold
        #ROI_Threshold = (160,0,160,240)
    elif Flag == 2:#宽2
        Find_Threshold = Black_Threshold
        ROI_Threshold = (0,0,160,240)
    elif Flag == 3:#高
        Find_Threshold = Black_Threshold
        #ROI_Threshold = (0,0,320,240)
        #ROI_Threshold = (160,120,160,120)
        ROI_Threshold = (0,120,320,120)

    #img.binary([Find_Threshold])
    img.to_grayscale()
    #img.dilate(2)
    #img.erode(2)

    #blobs = img.find_blobs([White_Threshold],roi=ROI_Threshold,x_stride=2,y_stride=2,
                            #pixels_threshold=100,area_thresholds=500,merge=True)
    #blobs = img.find_blobs([(0, 80)],roi=ROI_Threshold,x_stride=2,y_stride=2,
                            #pixels_threshold=100,area_thresholds=500,merge=True)
    if Flag == 1:
        blobs = img.find_blobs([(0, 80)],roi=(0,0,320,240),x_stride=10,y_stride=10,
                            pixels_threshold=1000,area_thresholds=1000,merge=False)
        max_b = max_blob(blobs)
        if max_b:
            for r in img.find_rects(threshold = 10000):
                img.draw_rectangle(r.rect(), color = (255, 0, 0))
                x_coordinate = int(r.x()+r.w()/2)
                y_coordinate = int(r.y()+r.h()/2)
            #x_coordinate = max_blob.cx()
            #y_coordinate = max_blob.cy()

            #for l in img.find_lines(threshold = 800, roi=(max_blob[0],max_blob[1],max_blob[2],max_blob[3]),theta_margin = 25, rho_margin = 25):
                #img.draw_line(l.line(), color = (255, 0, 0))

                x_L8 = x_coordinate & 0x00FF
                x_H8 = (x_coordinate>>8) & 0x00FF
                y_L8 = y_coordinate & 0x00FF
                y_H8 = (y_coordinate>>8) & 0x00FF

                data = bytearray([0x01,x_L8,x_H8,y_L8,y_H8,0x0A])
                uart.write(data)
                print(x_coordinate,y_coordinate,max_b.cx(),max_b.cy())

                img.draw_cross(max_b.cx(),max_b.cy(),size=10,color=(0,255,0),thickness=2)
                img.draw_rectangle(max_b.rect())
        else:
            Mis_Find = bytearray([0x09,0x0A])
            uart.write(Mis_Find)
            print('9')
    #elif Flag == 1:
        #max_blob = find_maxblob_black(blobs)
    elif Flag == 2:
        blobs = img.find_blobs([(0, 80)],roi=(0,0,160,240),x_stride=2,y_stride=2,
                            pixels_threshold=100,area_thresholds=500,merge=False)
        max_b = find_width_black(blobs)
        if max_b:
            x_coordinate = max_b.cx()
            y_coordinate = max_b.cy()

            #for l in img.find_lines(threshold = 800, roi=(max_blob[0],max_blob[1],max_blob[2],max_blob[3]),theta_margin = 25, rho_margin = 25):
                #img.draw_line(l.line(), color = (255, 0, 0))

            x_L8 = x_coordinate & 0x00FF
            x_H8 = (x_coordinate>>8) & 0x00FF
            y_L8 = y_coordinate & 0x00FF
            y_H8 = (y_coordinate>>8) & 0x00FF

            data = bytearray([0x02,y_L8,y_H8,0x0A])
            uart.write(data)
            print(x_coordinate,y_coordinate)

            img.draw_cross(max_b.cx(),max_b.cy(),size=10,color=(0,255,0),thickness=2)
            img.draw_rectangle(max_b.rect())
        else:
            Mis_Find = bytearray([0x09,0x0A])
            uart.write(Mis_Find)
            print('9')
    #elif Flag == 0x03:
        #max_blob = find_width_black(blobs)
    elif Flag == 3:
        blobs = img.find_blobs([(0, 80)],roi=(0,120,320,120),x_stride=2,y_stride=2,
                            pixels_threshold=100,area_thresholds=500,merge=True)
        max_b = find_high_black(blobs)
        if max_blob:
            x_coordinate = max_b.cx()
            y_coordinate = max_b.cy()

            #for l in img.find_lines(threshold = 800, roi=(max_blob[0],max_blob[1],max_blob[2],max_blob[3]),theta_margin = 25, rho_margin = 25):
                #img.draw_line(l.line(), color = (255, 0, 0))

            x_L8 = x_coordinate & 0x00FF
            x_H8 = (x_coordinate>>8) & 0x00FF
            y_L8 = y_coordinate & 0x00FF
            y_H8 = (y_coordinate>>8) & 0x00FF

            data = bytearray([0x03,x_L8,x_H8,0x0A])
            uart.write(data)
            print(x_coordinate,y_coordinate)

            img.draw_cross(max_b.cx(),max_b.cy(),size=10,color=(0,255,0),thickness=2)
            img.draw_rectangle(max_b.rect())
        else:
            Mis_Find = bytearray([0x09,0x0A])
            uart.write(Mis_Find)
            print('9')
    else:
        Mis_Find = bytearray([0x09,0x0A])
        uart.write(Mis_Find)
        print('9')

    #print(clock.fps())
