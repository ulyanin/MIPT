cmake_minimum_required(VERSION 3.8)
project(14_10_2017)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES main.cpp lock_free_stack.h)
add_executable(14_10_2017 ${SOURCE_FILES})
target_link_libraries(14_10_2017 Threads::Threads)