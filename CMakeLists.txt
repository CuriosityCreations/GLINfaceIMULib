
cmake_minimum_required(VERSION 2.8)
project(GL)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(RTIMULib)
include_directories(GLINface)

file(GLOB GL GLINface/*.cpp GLINface/*.h)
file(GLOB IMU RTIMULib/*.cpp RTIMULib/*.h)
file(GLOB IMUDrives RTIMULib/IMUDrivers/*.cpp RTIMULib/IMUDrivers/*.h)

add_executable(GL main.cpp ${GL} ${IMU} ${IMUDrives})

set(ALL_LIBS
	${OPENGL_LIBRARY}
        ${GLUT_LIBRARY}
)


target_link_libraries(GL
	${ALL_LIBS}
)
