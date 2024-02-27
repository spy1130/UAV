#led上
import sensor, image, time, pyb
from pyb import UART
from pyb import Pin

RED_LED_PIN = 1
BLUE_LED_PIN = 3

# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
#预设大小   窗口宽度    窗口高度
#VGA        640         480
#QVGA       320         240
#QQVGA      160         120
#视觉中心点：（160，120）
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # 在进行颜色追踪时，必须关闭
sensor.set_auto_whitebal(False) # 在进行颜色追踪时，必须关闭
clock = time.clock()

detected = False
another = False
other = False
end = False
#pyb.LED(BLUE_LED_PIN).off()
ain1 =  Pin('P9', Pin.OUT_PP)
ain1.high()

# 初始化变量
start_time = 0

# 循环读取摄像头数据
while True:
    # 读取一帧图像
    img = sensor.snapshot()
    key_up = 1
    key_down = 0
    # 检测绿色色块(27, 100, -78, -18, -18, 51)#(27, 100, -62, -26, -50, 40)
    blobs = img.find_blobs([(27, 100, -78, -54, -18, 51)],area_threshold=3,pixels_threshold=3)
    if detected == False:
        if blobs:
            # 显示检测框
            for blob in blobs:
                c = blobs[0]
                x=c[5]-160
                y=c[6]-120
                img.draw_cross(c[5], c[6]) # 在物体的中心点(cx,xy)画一个十字
                img.draw_rectangle(blob.rect())
            if key_up:
                key_up = key_up + 1
                sensor.skip_frames(time=300)
                if key_up ==2 and blobs:
                    key_up = 0
                    key_down = 1
                    if key_down:
                        ain1.low()
                        detected = True
                        print("1")
                        sensor.skip_frames(time=1000)
    elif detected == True and blobs:
        #detected = False  # 标记为未检测到
        c = blobs[0]
        x=c[5]-160
        y=c[6]-120
        img.draw_cross(c[5], c[6]) # 在物体的中心点(cx,xy)画一个十字
        sensor.skip_frames(time=2000)
        #pyb.LED(BLUE_LED_PIN).off()
        ain1.high()
        detected =False
        print("2")
        sensor.skip_frames(time=2000)
    else:
        print(".")
