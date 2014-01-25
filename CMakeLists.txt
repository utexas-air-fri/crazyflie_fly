cmake_minimum_required(VERSION 2.8.3)

include(ExternalProject)
ExternalProject_Add(
	cflie
	GIT_REPOSITORY https://github.com/fairlight1337/libcflie.git
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cflie
	BUILD_COMMAND cmake --build .
	INSTALL_COMMAND ""
)
ExternalProject_Get_Property(cflie INSTALL_DIR)
include_directories(${INSTALL_DIR}/src/cflie/include/)
link_directories(${INSTALL_DIR}/src/cflie/lib/)

project(crazyflie_autonomy)
find_package(
	catkin REQUIRED COMPONENTS 
    roscpp
	std_msgs
	sensor_msgs
)

catkin_package()

add_executable(crazyflie_fly src/crazyflie_fly.cpp)
target_link_libraries(crazyflie_fly libcflie.a ${catkin_LIBRARIES})
install(TARGETS crazyflie_fly RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
add_dependencies(crazyflie_fly cflie ${catkin_EXPORTED_TARGETS})

