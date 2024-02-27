
(cl:in-package :asdf)

(defsystem "lslidar_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "LslidarDifop" :depends-on ("_package_LslidarDifop"))
    (:file "_package_LslidarDifop" :depends-on ("_package"))
    (:file "LslidarPacket" :depends-on ("_package_LslidarPacket"))
    (:file "_package_LslidarPacket" :depends-on ("_package"))
    (:file "LslidarPoint" :depends-on ("_package_LslidarPoint"))
    (:file "_package_LslidarPoint" :depends-on ("_package"))
    (:file "LslidarScan" :depends-on ("_package_LslidarScan"))
    (:file "_package_LslidarScan" :depends-on ("_package"))
    (:file "LslidarSweep" :depends-on ("_package_LslidarSweep"))
    (:file "_package_LslidarSweep" :depends-on ("_package"))
  ))