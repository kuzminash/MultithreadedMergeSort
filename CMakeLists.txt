cmake_minimum_required(VERSION 3.16)
project(lab_16)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads REQUIRED)
include_directories(src)
include_directories(include)
add_executable(lab_16 src/main.cpp include/parallel_sort.hpp include/parallel_sort.inl)
target_link_libraries (lab_16 ${CMAKE_THREAD_LIBS_INIT})