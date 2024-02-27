;; Auto-generated. Do not edit!


(when (boundp 'lslidar_msgs::LslidarPacket)
  (if (not (find-package "LSLIDAR_MSGS"))
    (make-package "LSLIDAR_MSGS"))
  (shadow 'LslidarPacket (find-package "LSLIDAR_MSGS")))
(unless (find-package "LSLIDAR_MSGS::LSLIDARPACKET")
  (make-package "LSLIDAR_MSGS::LSLIDARPACKET"))

(in-package "ROS")
;;//! \htmlinclude LslidarPacket.msg.html


(defclass lslidar_msgs::LslidarPacket
  :super ros::object
  :slots (_stamp _data ))

(defmethod lslidar_msgs::LslidarPacket
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:data __data) (make-array 2000 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _data __data)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; uint8[2000] _data
    (* 1    2000)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; uint8[2000] _data
     (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8[2000] _data
   (setq _data (make-array 2000 :element-type :char))
   (replace _data buf :start2 ptr-) (incf ptr- 2000)
   ;;
   self)
  )

(setf (get lslidar_msgs::LslidarPacket :md5sum-) "8b4a4c3a12627c71d9c1beffa4ce1941")
(setf (get lslidar_msgs::LslidarPacket :datatype-) "lslidar_msgs/LslidarPacket")
(setf (get lslidar_msgs::LslidarPacket :definition-)
      "# Raw Leishen LIDAR packet.

time stamp              # packet timestamp
uint8[2000] data        # packet contents


")



(provide :lslidar_msgs/LslidarPacket "8b4a4c3a12627c71d9c1beffa4ce1941")


