;; Auto-generated. Do not edit!


(when (boundp 'lslidar_msgs::LslidarDifop)
  (if (not (find-package "LSLIDAR_MSGS"))
    (make-package "LSLIDAR_MSGS"))
  (shadow 'LslidarDifop (find-package "LSLIDAR_MSGS")))
(unless (find-package "LSLIDAR_MSGS::LSLIDARDIFOP")
  (make-package "LSLIDAR_MSGS::LSLIDARDIFOP"))

(in-package "ROS")
;;//! \htmlinclude LslidarDifop.msg.html


(defclass lslidar_msgs::LslidarDifop
  :super ros::object
  :slots (_rpm ))

(defmethod lslidar_msgs::LslidarDifop
  (:init
   (&key
    ((:rpm __rpm) 0)
    )
   (send-super :init)
   (setq _rpm (round __rpm))
   self)
  (:rpm
   (&optional __rpm)
   (if __rpm (setq _rpm __rpm)) _rpm)
  (:serialization-length
   ()
   (+
    ;; int64 _rpm
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _rpm
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _rpm (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _rpm) (= (length (_rpm . bv)) 2)) ;; bignum
              (write-long (ash (elt (_rpm . bv) 0) 0) s)
              (write-long (ash (elt (_rpm . bv) 1) -1) s))
             ((and (class _rpm) (= (length (_rpm . bv)) 1)) ;; big1
              (write-long (elt (_rpm . bv) 0) s)
              (write-long (if (>= _rpm 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _rpm s)(write-long (if (>= _rpm 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _rpm
#+(or :alpha :irix6 :x86_64)
      (setf _rpm (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _rpm (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(setf (get lslidar_msgs::LslidarDifop :md5sum-) "50442aa210dd5f42de9c4e1b86df3045")
(setf (get lslidar_msgs::LslidarDifop :datatype-) "lslidar_msgs/LslidarDifop")
(setf (get lslidar_msgs::LslidarDifop :definition-)
      "int64 rpm

")



(provide :lslidar_msgs/LslidarDifop "50442aa210dd5f42de9c4e1b86df3045")


