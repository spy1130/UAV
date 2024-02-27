# Untitled - By: Lenovo - 周四 8月 3 2023

import sensor, image, time

min_degree = 60   #0
max_degree = 120  #179

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot().lens_corr(1.8)
    for l in img.find_lines(threshold = 1000, theta_margin = 25, rho_margin = 25):
            if (min_degree <= l.theta()) and (l.theta() <= max_degree):
                img.draw_line(l.line(), color = (255, 0, 0))
                rho_err = abs(l.rho())-img.height()/2
                if l.theta()>180:
                    theta_err = l.theta()-270
                else:
                    theta_err = l.theta()-90
                rho_L8 = int(rho_err) & 0x00FF #取低八位
                rho_H8 = (int(rho_err)>>8) & 0x00FF #取高八位
                theta_L8 = int(theta_err) & 0x00FF #取低八位
                theta_H8 = (int(theta_err)>>8) & 0x00FF #取高八位
            else:
                img.draw_line(l.line(), color = (0, 255, 0))
                rho_err = abs(l.rho())-img.width()/2
                if l.theta()>90:
                    theta_err = l.theta()-180
                else:
                    theta_err = l.theta()
                rho_L8 = int(rho_err) & 0x00FF #取低八位
                rho_H8 = (int(rho_err)>>8) & 0x00FF #取高八位
                theta_L8 = int(theta_err) & 0x00FF #取低八位
                theta_H8 = (int(theta_err)>>8) & 0x00FF #取高八位
