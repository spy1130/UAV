import sensor, image, time, pyb

yellow_thresholds = (47, 0, 78, 11, 65, -31)    #定义变量
sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    img.draw_rectangle((131, 122, 20, 20), color = (255,255,255))   #画roi框
    statistics_Data = img.get_statistics(roi = (131, 122, 20, 20) )
#    print(statistics_Data)
#    print(statistics_Data.l_mode()) #LAB众数，打印出来看看效果稳定不稳定
#    print(statistics_Data.a_mode())
#    print(statistics_Data.b_mode())
    color_L_Mode = statistics_Data.l_mode()     #分别赋值LAB的众数
    color_A_Mode = statistics_Data.a_mode()
    color_B_Mode = statistics_Data.b_mode()
    #计算颜色阈值，这样写的话，颜色阈值是实时变化的，后续想要什么效果可以自己修改
    yellow_thresholds = (color_L_Mode-20, color_L_Mode+20, color_A_Mode-20, \
                         color_A_Mode+20, color_B_Mode-20, color_B_Mode+20)
    img.binary([yellow_thresholds]) #二值化看图像效果
    print(yellow_thresholds)        #打印输出颜色阈值
    print(clock.fps())
