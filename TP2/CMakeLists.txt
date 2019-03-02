cmake_minimum_required(VERSION 3.13)
project(tp2)

set(OpenCV_INCLUDE_DIR /usr/local/include/opencv4/opencv2)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(tp2 main.cpp Filter.cpp Filter.h)

include_directories(${OpenCV_INCLUDE_DIR})
target_link_libraries(tp2 ${OpenCV_LIBS})




