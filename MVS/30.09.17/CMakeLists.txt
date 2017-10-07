cmake_minimum_required(VERSION 3.7)
project(30_09_17)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "--std=c++17")
set(SOURCE_FILES main.cpp)
add_executable(30_09_17 ${SOURCE_FILES})
target_link_libraries(30_09_17 Threads::Threads)