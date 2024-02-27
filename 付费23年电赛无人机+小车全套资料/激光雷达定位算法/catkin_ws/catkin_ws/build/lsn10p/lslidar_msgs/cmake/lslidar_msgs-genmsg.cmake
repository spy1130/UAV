# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "lslidar_msgs: 5 messages, 0 services")

set(MSG_I_FLAGS "-Ilslidar_msgs:/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(lslidar_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg" NAME_WE)
add_custom_target(_lslidar_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "lslidar_msgs" "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg" ""
)

get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg" NAME_WE)
add_custom_target(_lslidar_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "lslidar_msgs" "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg" ""
)

get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg" NAME_WE)
add_custom_target(_lslidar_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "lslidar_msgs" "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg" "lslidar_msgs/LslidarPoint"
)

get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg" NAME_WE)
add_custom_target(_lslidar_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "lslidar_msgs" "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg" "std_msgs/Header:lslidar_msgs/LslidarScan:lslidar_msgs/LslidarPoint"
)

get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg" NAME_WE)
add_custom_target(_lslidar_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "lslidar_msgs" "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_cpp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_cpp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg"
  "${MSG_I_FLAGS}"
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_cpp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_cpp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lslidar_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(lslidar_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lslidar_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(lslidar_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(lslidar_msgs_generate_messages lslidar_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_cpp _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_cpp _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_cpp _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_cpp _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_cpp _lslidar_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lslidar_msgs_gencpp)
add_dependencies(lslidar_msgs_gencpp lslidar_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lslidar_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_eus(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_eus(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg"
  "${MSG_I_FLAGS}"
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_eus(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_eus(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lslidar_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(lslidar_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lslidar_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(lslidar_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(lslidar_msgs_generate_messages lslidar_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_eus _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_eus _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_eus _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_eus _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_eus _lslidar_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lslidar_msgs_geneus)
add_dependencies(lslidar_msgs_geneus lslidar_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lslidar_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_lisp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_lisp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg"
  "${MSG_I_FLAGS}"
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_lisp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_lisp(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lslidar_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(lslidar_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lslidar_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(lslidar_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(lslidar_msgs_generate_messages lslidar_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_lisp _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_lisp _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_lisp _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_lisp _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_lisp _lslidar_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lslidar_msgs_genlisp)
add_dependencies(lslidar_msgs_genlisp lslidar_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lslidar_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_nodejs(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_nodejs(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg"
  "${MSG_I_FLAGS}"
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_nodejs(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_nodejs(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lslidar_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(lslidar_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lslidar_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(lslidar_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(lslidar_msgs_generate_messages lslidar_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_nodejs _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_nodejs _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_nodejs _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_nodejs _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_nodejs _lslidar_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lslidar_msgs_gennodejs)
add_dependencies(lslidar_msgs_gennodejs lslidar_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lslidar_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_py(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_py(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg"
  "${MSG_I_FLAGS}"
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_py(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg;/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs
)
_generate_msg_py(lslidar_msgs
  "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(lslidar_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(lslidar_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(lslidar_msgs_generate_messages lslidar_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPacket.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_py _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarPoint.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_py _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarScan.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_py _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarSweep.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_py _lslidar_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cat/catkin_ws/src/lsn10p/lslidar_msgs/msg/LslidarDifop.msg" NAME_WE)
add_dependencies(lslidar_msgs_generate_messages_py _lslidar_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(lslidar_msgs_genpy)
add_dependencies(lslidar_msgs_genpy lslidar_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS lslidar_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lslidar_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/lslidar_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(lslidar_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lslidar_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/lslidar_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(lslidar_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lslidar_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/lslidar_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(lslidar_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lslidar_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/lslidar_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(lslidar_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/lslidar_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(lslidar_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
