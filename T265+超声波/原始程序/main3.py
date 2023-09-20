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

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

Led = 11
GPIO.setup(Led, GPIO.OUT)

Buzzer = 12
GPIO.setup(Buzzer, GPIO.OUT)


# 取整数的补码
def int2hex(data):
    x = hex((data + (1 << 16)) % (1 << 16))
    y = x[2:]
    z = int(y, 16)
    return z


if __name__ == "__main__":
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
            GPIO.output(Led, GPIO.LOW)
            continue
        try:
            while True:
                frames = pipe.wait_for_frames()
                pose = frames.get_pose_frame()
                if pose:
                    # rpy角度传输
                    data = pose.get_pose_data()
                    #w = data.rotation.w
                    #x = -data.rotation.z
                    #y = data.rotation.x
                    #z = -data.rotation.y

                    #pitch = -m.asin(2.0 * (x * z - w * y)) * 180.0 / m.pi;
                    #roll = m.atan2(2.0 * (w * x + y * z), w * w - x * x - y * y + z * z) * 180.0 / m.pi;
                    #yaw = m.atan2(2.0 * (w * z + x * y), w * w + x * x - y * y - z * z) * 180.0 / m.pi;

                    #pi = int2hex(int(pitch))
                    #ro = int2hex(int(roll))
                    #ya = int2hex(int(yaw))
                    #my_data1 = bytearray(
                     #   [0xaa, 0x29, 0x05, 0x35, 0x06, pi >> 8, pi & 0xff, ro >> 8, ro & 0xff, ya >> 8, ya & 0xff,
                     #   0x00])
                    #ser.write(my_data1)

                    # xyz
                    my_x = data.translation.x * 100
                    my_y = data.translation.y * 100
                    my_z = data.translation.z * 100

                    my_x = int2hex(int(my_x))
                    my_y = int2hex(int(my_y))
                    my_z = int2hex(int(my_z))
                    my_data2 = bytearray(
                        [0xaa, 0x29, 0x05, 0x34, 0x06, my_x >> 8, my_x & 0xff, my_y >> 8, my_y & 0xff, my_z >> 8,
                         my_z & 0xff, 0x00])
                    ser.write(my_data2)
                    print("pos:{}".format(data.translation))
                    time.sleep(0.1)  #调试时使用，方便观察

                     #x,z方向速度
                     #v_x = data.velocity.x*m.cos(roll/360.0*2*pi)*100
                     #v_z = -data.velocity.z*m.cos(pitch/360.0*2*pi)*100
                     #v_y = data.velocity.y*100

                    #v_x = data.velocity.x * 100
                    #v_z = -data.velocity.z * 100
                    #v_y = data.velocity.y * 100
                    #print("xy::",v_x,v_y)
                    # 坐标转换后的xy速度
                    #x_v = v_z * m.cos(yaw / 180.0 * m.pi) + v_x * m.sin(yaw / 180.0 * m.pi)
                    #y_v = v_z * m.sin(yaw / 180.0 * m.pi) - v_x * m.cos(yaw / 180.0 * m.pi)

                    #print("...V-XY%.3f      ,     %.3f:"%(x_v,y_v))
                    #v_x = int2hex(int(x_v))
                    #v_z = int2hex(int(v_y))
                    #v_y = int2hex(int(y_v))

                    #my_data3 = bytearray(
                     #   [0xaa, 0x29, 0x05, 0x33, 0x06, v_x >> 8, v_x & 0xff, v_y >> 8, v_y & 0xff, v_z >> 8, v_z & 0xff,
                      #   0x00])
                    #ser.write(my_data3)
                     #print("Velocity: {}".format(data.velocity))
                     #print("%.3f,%.3f"%(v_x,v_z))
                     #time.sleep(1)
                    cnt += 1
                    if cnt >= 50:
                        GPIO.output(Led, GPIO.HIGH)
                    if cnt >= 100:
                        GPIO.output(Led, GPIO.LOW)
                        cnt = 0
        except:
            print("异常2发生，重新执行程序")
            # ser.write(bytearray([0xaa,0x29,0x05,0x55,0x06,0,0,0,0,0,0,0x00]))   #发送异常
            GPIO.output(Led, GPIO.HIGH)
            GPIO.output(Buzzer, GPIO.HIGH)
            time.sleep(1)
            GPIO.output(Buzzer, GPIO.LOW)
        finally:
            GPIO.output(Led, GPIO.LOW)
            GPIO.output(Buzzer, GPIO.LOW)
            pipe.stop()
