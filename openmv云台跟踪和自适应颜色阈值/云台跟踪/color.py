# 基于“基于openmv的板球控制系统”的视觉模块
# 导库
import sensor, image, time, math, pyb
from pyb import UART # 串口
import json # 数据格式转换
import gc

gc.collect()
threshold_index = 0
thresholds = [(0, 100, 38, 127, 10, 127)] # 颜色阈值

# 初始化摄像头
sensor.reset()# 重置感光元件
sensor.set_pixformat(sensor.RGB565)# 设置颜色格式
sensor.set_framesize(sensor.QVGA)# 图像大小
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # 白平衡
sensor.set_auto_whitebal(False) # 自动增益

#创建一个UART对象
uart = UART(3, 19200) # 第一个参数是UART总线，这是OpenMV Cam上的UART总线的索引。
                      # 你必须用这个值调用UART构造函数，因为我们正在利用MicroPython的pyboard的 pyb 模块
                      # 第二个值是波特率，它可以是任何你喜欢的标准波特率值
while(True):
    img = sensor.snapshot() # 截取感光元件的图片
    for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=200, area_threshold=200, merge=True):
        # 查找图像中所有色块，并返回一个包括每个色块的色块对象的列表；
        # 若一个色块的像素数小于 pixel_threshold ，则会被过滤掉；
        # 若一个色块的边界框区域小于 area_threshold ，则会被过滤掉；
        # merge 若为True，则合并所有没有被过滤掉的色块，这些色块的边界矩形互相交错重叠

        img.draw_rectangle(blob.rect()) # 若识别到色块则框起来
        img.draw_cross(blob.cx(), blob.cy()) # 在色块画十字坐标

        data1 = json.dumps(blob.cx())
        data2 = json.dumps(blob.cy())

        print(data1,data2)
        uart.write(data1)
        #uart.write(data1+'\t')
        #uart.write(data2+'\n')
        gc.collect()
gc.collect()
