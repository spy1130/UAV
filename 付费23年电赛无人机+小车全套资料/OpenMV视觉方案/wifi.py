# MJPEG Streaming AP.
#
# 这个例子展示了如何在AccessPoint模式下进行MJPEG流式传输。
# Android上的Chrome，Firefox和MJpegViewer App已经过测试。
# 连接到OPENMV_AP并使用此URL：http://192.168.1.1:8080查看流。

import sensor, image, time, network, usocket, sys

SSID ='OPENMV_AP'    # Network SSID
KEY  ='1234567890'   # wifi密码(必须为10字符)
HOST = ''           # 使用第一个可用的端口
PORT = 8080         # 任意非特权端口

# 重置传感器
sensor.reset()
# 设置传感器设置
sensor.set_contrast(1)
sensor.set_brightness(1)
sensor.set_saturation(1)
sensor.set_gainceiling(16)
sensor.set_framesize(sensor.QQVGA)
sensor.set_pixformat(sensor.GRAYSCALE)

# 在AP模式下启动wlan模块。
wlan = network.WINC(mode=network.WINC.MODE_AP)
wlan.start_ap(SSID, key=KEY, security=wlan.WEP, channel=2)

#您可以阻止等待客户端连接
#print(wlan.wait_for_sta(10000))

def start_streaming(s):
    print ('Waiting for connections..')
    client, addr = s.accept()
    # 将客户端套接字超时设置为2秒
    client.settimeout(2.0)
    print ('Connected to ' + addr[0] + ':' + str(addr[1]))

    # 从客户端读取请求
    data = client.recv(1024)
    # 应该在这里解析客户端请求

    # 发送多部分head
    client.send("HTTP/1.1 200 OK\r\n" \
                "Server: OpenMV\r\n" \
                "Content-Type: multipart/x-mixed-replace;boundary=openmv\r\n" \
                "Cache-Control: no-cache\r\n" \
                "Pragma: no-cache\r\n\r\n")

    # FPS clock
    clock = time.clock()

    # 开始流媒体图像
    #注：禁用IDE预览以增加流式FPS。
    while (True):
        clock.tick() # 跟踪snapshots()之间经过的毫秒数。
        frame = sensor.snapshot()
        cframe = frame.compressed(quality=35)
        header = "\r\n--openmv\r\n" \
                 "Content-Type: image/jpeg\r\n"\
                 "Content-Length:"+str(cframe.size())+"\r\n\r\n"
        client.send(header)
        client.send(cframe)
        print(clock.fps())

while (True):
    # 创建服务器套接字
    s = usocket.socket(usocket.AF_INET, usocket.SOCK_STREAM)
    try:
        # Bind and listen
        s.bind([HOST, PORT])
        s.listen(5)

        # 设置服务器套接字超时
        # 注意：由于WINC FW bug，如果客户端断开连接，服务器套接字必须
        # 关闭并重新打开。在这里使用超时关闭并重新创建套接字。
        s.settimeout(3)
        start_streaming(s)
    except OSError as e:
        s.close()
        print("socket error: ", e)
        #sys.print_exception(e)
