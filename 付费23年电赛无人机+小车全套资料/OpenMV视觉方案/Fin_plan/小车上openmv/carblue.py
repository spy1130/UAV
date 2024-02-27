#小车上
import sensor, image, time, pyb
from pyb import UART

uart3 = UART(3,115200)#与车
#uart1 = UART(3,115200)

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

#a=2
#a=''
#o0=''
#o1=''
#o2=''
#o3=''
#o4=''

#def find_max(blobs):
    #max_size=0
    #for blob in blobs:
        #if blob[2]*blob[3] > max_size:
            #max_blob=blob
            #max_size = blob[2]*blob[3]
    #return max_blob

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob = blob
            max_size = blob.pixels()
    return max_blob

while(True):
    clock.tick()
    img = sensor.snapshot()
    #找蓝色(24, 80, -48, 60, -75, -20)(0, 47, -20, 27, -78, -6)
    blobs = img.find_blobs([(24, 80, -48, 60, -75, -20)],area_threshold=3,pixels_threshold=3)
    #blobs = img.find_blobs([(24, 70, 17, 127, -10, 127)],area_threshold=3,pixels_threshold=3)
    #max_blob = find_max(blobs)
    if blobs:
        max_blob = find_max(blobs)
        #c = max_blob[0]
        x=max_blob[5]-160
        y=max_blob[6]-120
        img.draw_cross(max_blob[5], max_blob[6],(255,255,255)) # 在物体的中心点(cx,xy)画一个十字
        x_L8 = int(x) & 0x00FF #取低八位
        x_H8 = (int(x)>>8) & 0x00FF #取高八位
        y_L8 = int(y) & 0x00FF #取低八位
        y_H8 = (int(y)>>8) & 0x00FF #取高八位
        data1 = bytearray([1,x_L8,x_H8,y_L8,y_H8,0x0A])
        print("(%d,%d)" %(x,y))
        uart3.write(data1)
    else:
        print("no")
        data1 = bytearray([9,0x0A])
        uart3.write(data1)

