cmake_minimum_required(VERSION 3.16)
project(RealtimeVisionAI)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenCV REQUIRED)
add_executable(
	p1_app
	src/main.cpp
 src/app_info.cpp
 include/app_info.h
 "include/image_loader.h" 
 "src/image_loader.cpp" 
 "include/image_preprocessor.h" 
 "src/image_preprocessor.cpp"
)
 target_include_directories(p1_app PRIVATE ${OpenCV_INCLUDE_DIRS})
 target_include_directories(
    p1_app
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(p1_app PRIVATE ${OpenCV_LIBS})