#!/usr/bin/python
# -*- coding: utf-8 -*-
## License: Apache 2.0. See LICENSE file in root directory.
## Copyright(c) 2019 Intel Corporation. All Rights Reserved.

#####################################################
##           librealsense T265 rpy example         ##
#####################################################

# First import the library
import numpy as np
import time
import serial
import pyrealsense2 as rs
import math as m
import Jetson.GPIO as GPIO

GPIO.setmode(GPIO.BOARD) # 采用实际的物理管脚给GPIO口
GPIO.setwarnings(False) # 忽略GPIO操作注意警告

TRIG_pin = 11  # 超声波模块Trig控制管脚, BCM 17 18
ECHO_pin = 12  # 超声波模块Echo控制管脚

# 超声波模块初始化工作
def init_setup():     
    GPIO.setmode(GPIO.BOARD) # 采用实际的物理管脚给GPIO口
    GPIO.setwarnings(False) # 忽略GPIO操作注意警告
    GPIO.setup(TRIG_pin, GPIO.OUT) # Tring设置为输出模式
    GPIO.setup(ECHO_pin, GPIO.IN)  # Echo设置为输入模式

# 超声波计算距离函数
def distance():
    GPIO.output(TRIG_pin, 0)  # 开始起始
    time.sleep(0.000002)  # 延时2us
    GPIO.output(TRIG_pin, 1)  # 超声波启动信号，延时10us
    time.sleep(0.00001)    # 发出超声波脉冲
    GPIO.output(TRIG_pin, 0)  # 设置为低电平

    while GPIO.input(ECHO_pin) == 0: # 等待回传信号
        us_a = 0
    us_time1 = time.time()      # 获取当前时间
    while GPIO.input(ECHO_pin) == 1: # 回传信号截止信息
        us_a = 1
    us_time2 = time.time()     # 获取当前时间
    during = us_time2 - us_time1          # 转换微秒级的时间

    # 声速在空气中的传播速度为340m/s, 超声波要经历一个发送信号和一个回波信息
    # 计算公式如下所示：
    return during * 340 / 2 * 100        # 求出距离

# 超声波发送函数
def distance_return():
        us_dis = distance()   # 获取超声波计算距离        
        return us_dis

# 资源释放函数
def destroy():
    GPIO.cleanup() # 释放资源

# 取整数的补码（T265）
def int2hex(data):
    x = hex((data + (1 << 16)) % (1 << 16))
    y = x[2:]
    z = int(y, 16)
    return z

if __name__ == "__main__":
    init_setup() # 调用初始化函数
    while True:
        try:
            cnt = 0
            ser = serial.Serial("/dev/ttyTHS1", 500000)  # 串口设置500000
            pipe = rs.pipeline()
            cfg = rs.config()
            cfg.enable_stream(rs.stream.pose)
            pipe.start(cfg)
        except:
            # print('T265初始化失败')
            continue
        try:
            while True:
                frames = pipe.wait_for_frames()
                pose = frames.get_pose_frame()
                if pose:
                    
                    data = pose.get_pose_data()

                    # xyz
                    my_x = data.translation.x * 100
                    my_y = data.translation.y * 100
                    my_z = data.translation.z * 100

                    my_x = int2hex(int(my_x))
                    my_y = int2hex(int(my_y))
                    my_z = int2hex(int(my_z))

                    dis_spy= distance_return()
                    pri_spy=dis_spy
                    dis_spy = int2hex(int(dis_spy))

                    my_data2 = bytearray(
                        [0xaa, 0x29, 0x05, 0x34, 0x08, my_x >> 8, my_x & 0xff, my_y >> 8, my_y & 0xff, my_z >> 8,
                         my_z & 0xff, dis_spy >> 8, dis_spy & 0xff,0x00])
                    ser.write(my_data2)
                    print("pos:{}".format(data.translation),end=" ")
                    time.sleep(0.01)#防止刷掉数据
                    us_1=str(pri_spy)
                    print(us_1+'cm')       # 打印超声波距离值
                    time.sleep(0.1)  #调试时使用，方便观察

        except KeyboardInterrupt: # 当按下Ctrl+C时，将执行destroy()子程序
            print("异常2发生，重新执行程序")
            destroy() # 释放资源
            pipe.stop()
            # ser.write(bytearray([0xaa,0x29,0x05,0x55,0x06,0,0,0,0,0,0,0x00]))   #发送异常
        finally:
            destroy() # 释放资源
            pipe.stop()
