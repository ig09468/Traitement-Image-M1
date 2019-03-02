cmake_minimum_required(VERSION 3.13)
project(TP1)

set(OpenCV_INCLUDE_DIR /usr/local/include/opencv4/opencv2)

find_package(OpenCV REQUIRED)


set(CMAKE_CXX_STANDARD 14)

add_executable(TP1 main.cpp)


include_directories(${OpenCV_INCLUDE_DIR})
target_link_libraries(TP1 ${OpenCV_LIBS})