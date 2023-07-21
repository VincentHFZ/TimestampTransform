cmake_minimum_required(VERSION 3.0)

project(timestamp_transform)

add_compile_options(-std=c++14)

set(CMAKE_BUILD_TYPE Release)

add_executable(timestamp_transform src/main.cpp)
target_link_libraries(timestamp_transform 
    glog 
    gflags
    ) 

install(TARGETS timestamp_transform 
    RUNTIME DESTINATION /usr/local/bin)