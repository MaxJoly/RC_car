cmake_minimum_required(VERSION 2.8.3)
project(rc_car)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)


## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   Command.msg
   Command.msg
   RSRMsg.msg
   CalibMsg.msg
 )

## Generate services in the 'srv' folder
add_service_files(
   FILES
  # AddTwoInts.srv
 )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES rc_car
  CATKIN_DEPENDS message_runtime roscpp rospy std_msgs 
  DEPENDS system_lib

)


include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_library(pwm src/pwm.cpp)

#include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(iDCmotor src/DCmotor.cpp)
target_link_libraries(iDCmotor ${catkin_LIBRARIES})
target_link_libraries(iDCmotor pwm)
add_dependencies(iDCmotor rc_car_gen_cpp)

add_executable(iServomotor src/servomotor.cpp)
target_link_libraries(iServomotor ${catkin_LIBRARIES})
target_link_libraries(iServomotor pwm)
add_dependencies(iServomotor rc_car_gen_cpp)

