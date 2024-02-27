; Auto-generated. Do not edit!


(cl:in-package lslidar_msgs-msg)


;//! \htmlinclude LslidarPacket.msg.html

(cl:defclass <LslidarPacket> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 2000 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass LslidarPacket (<LslidarPacket>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LslidarPacket>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LslidarPacket)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lslidar_msgs-msg:<LslidarPacket> is deprecated: use lslidar_msgs-msg:LslidarPacket instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <LslidarPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lslidar_msgs-msg:stamp-val is deprecated.  Use lslidar_msgs-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <LslidarPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lslidar_msgs-msg:data-val is deprecated.  Use lslidar_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LslidarPacket>) ostream)
  "Serializes a message object of type '<LslidarPacket>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'stamp) (cl:floor (cl:slot-value msg 'stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LslidarPacket>) istream)
  "Deserializes a message object of type '<LslidarPacket>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array 2000))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i 2000)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LslidarPacket>)))
  "Returns string type for a message object of type '<LslidarPacket>"
  "lslidar_msgs/LslidarPacket")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LslidarPacket)))
  "Returns string type for a message object of type 'LslidarPacket"
  "lslidar_msgs/LslidarPacket")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LslidarPacket>)))
  "Returns md5sum for a message object of type '<LslidarPacket>"
  "8b4a4c3a12627c71d9c1beffa4ce1941")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LslidarPacket)))
  "Returns md5sum for a message object of type 'LslidarPacket"
  "8b4a4c3a12627c71d9c1beffa4ce1941")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LslidarPacket>)))
  "Returns full string definition for message of type '<LslidarPacket>"
  (cl:format cl:nil "# Raw Leishen LIDAR packet.~%~%time stamp              # packet timestamp~%uint8[2000] data        # packet contents~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LslidarPacket)))
  "Returns full string definition for message of type 'LslidarPacket"
  (cl:format cl:nil "# Raw Leishen LIDAR packet.~%~%time stamp              # packet timestamp~%uint8[2000] data        # packet contents~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LslidarPacket>))
  (cl:+ 0
     8
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LslidarPacket>))
  "Converts a ROS message object to a list"
  (cl:list 'LslidarPacket
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':data (data msg))
))
