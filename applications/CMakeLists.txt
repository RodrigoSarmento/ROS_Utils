Cmake_minimum_required(VERSION 2.8.3)
project(ROS_Utils)

#Compile in c++ 11
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-std=c++11)

#Optimizations Flags
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -O3 -march=native ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall   -O3 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

message(STATUS ">>> applications subdirectory")

add_executable(rgbd_loader rgbd_loader.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

target_link_libraries(rgbd_loader  ${catkin_LIBRARIES} ${OpenCV_LIBS})

install(TARGETS rgbd_loader
        RUNTIME DESTINATION bin)
