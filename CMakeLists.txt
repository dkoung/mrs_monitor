cmake_minimum_required(VERSION 3.0.2)
project(mrs_monitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

find_package(catkin REQUIRED COMPONENTS
cmake_modules
roscpp
nav_msgs
sensor_msgs
std_srvs
tf2_ros
urdf
message_generation
global_planner
costmap_2d
dwa_local_planner
)

add_service_files(
   FILES
   Cancel.srv
   Estimate.srv
   Move.srv
   Status.srv
 )

generate_messages(DEPENDENCIES std_msgs geometry_msgs)

catkin_package(
INCLUDE_DIRS include ${EIGEN3_INCLUDE_DIRS}
 LIBRARIES mrs_monitor_io
 CATKIN_DEPENDS
    roscpp
    geometry_msgs
    nav_msgs
    message_runtime
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(sim_time src/sim_time.cpp)
target_include_directories(sim_time PRIVATE ${catkin_INCLUDE_DIRS})
target_link_libraries(sim_time ${catkin_LIBRARIES})

add_executable(mrs_monitor src/mrs_monitor.cpp src/robot.cpp src/fleet.cpp src/geometry.cpp)
target_include_directories(mrs_monitor PRIVATE include ${catkin_INCLUDE_DIRS})
add_dependencies(mrs_monitor mrs_monitor_gencpp)
target_link_libraries(mrs_monitor ${catkin_LIBRARIES})

# node for global planning
add_executable(mrs_planner src/planner.cpp)
target_include_directories(mrs_planner PRIVATE include ${catkin_INCLUDE_DIRS})
add_dependencies(mrs_planner mrs_monitor_gencpp)
target_link_libraries(mrs_planner ${catkin_LIBRARIES})

# node for local control
add_executable(mrs_control src/control.cpp)
target_include_directories(mrs_control PRIVATE include ${catkin_INCLUDE_DIRS})
add_dependencies(mrs_control mrs_monitor_gencpp)
target_link_libraries(mrs_control ${catkin_LIBRARIES})


# lib to use from a manager node
add_library(mrs_monitor_io src/monitor_io.cpp)
target_include_directories(mrs_monitor_io PRIVATE include ${catkin_INCLUDE_DIRS})
add_dependencies(mrs_monitor_io mrs_monitor_gencpp)
target_link_libraries(mrs_monitor_io ${catkin_LIBRARIES})

add_executable(demo_cpp demo/demo.cpp)
target_include_directories(demo_cpp PRIVATE include ${catkin_INCLUDE_DIRS})
add_dependencies(demo_cpp mrs_monitor_gencpp)
target_link_libraries(demo_cpp ${catkin_LIBRARIES} mrs_monitor_io)

