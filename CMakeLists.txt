cmake_minimum_required(VERSION 3.16)
project(RealtimeVisionAI)
set(CMAKE_CXX_STANDARD 17)
add_executable(
	p1_app
	src/main.cpp
 src/app_info.cpp
 include/app_info.h)
 target_include_directories(
    p1_app
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)