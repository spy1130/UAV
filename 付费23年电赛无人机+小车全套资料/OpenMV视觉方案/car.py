#小车上
import sensor, image, time, pyb
from pyb import UART

uart3 = UART(3,115200)#与车
uart1 = UART(1,115200)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
#预设大小   窗口宽度    窗口高度
#VGA        640         480
#QVGA       320         240
#QQVGA      160         120
#视觉中心点：（160，120）
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # 在进行颜色追踪时，必须关闭
sensor.set_auto_whitebal(False) # 在进行颜色追踪时，必须关闭
clock = time.clock()

a=1
#a=''
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
        #a=int(recv_data[0])-48
        #print(a,b)
    if (uart1.any()):   # 更新串口接收数据
        recv_datao = uart1.read()  #接收读取的字符串
        o0=int(recv_datao[0])
        o1=int(recv_datao[1])
        o2=int(recv_datao[2])
        o3=int(recv_datao[3])
        o4=int(recv_datao[4])
        #print(o0,o1,o2,o3,o4,o5,o6)
    img = sensor.snapshot()
    if(a==1):
        blobs = img.find_blobs([(0, 100, 20, 127, -128, 127)],area_threshold=3,pixels_threshold=3)
        #blobs = img.find_blobs([(24, 70, 17, 127, -10, 127)],area_threshold=3,pixels_threshold=3)
        if blobs:
            c = blobs[0]
            x=int(c[5])
            y=int(c[6])
            img.draw_cross(c[5], c[6],(255,255,255)) # 在物体的中心点(cx,xy)画一个十字
            data1 = bytearray([1,x,y,0x0A])
            print("(%d,%d)" %(x,y))
            uart3.write(data1)
    else:
        print("no")
        data2 = bytearray([9,0x0A])
        uart3.write(data2)

