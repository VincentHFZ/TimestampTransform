cmake_minimum_required(VERSION 3.0)

project(timestamp_transform)

add_compile_options(-std=c++14)

add_executable(timestamp_transform src/main.cpp)
target_link_libraries(timestamp_transform 
    glog 
    gflags
    ) 