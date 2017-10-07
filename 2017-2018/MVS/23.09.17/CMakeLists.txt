cmake_minimum_required(VERSION 3.6)
project(23.09.17-MVS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -DLOCAL")

set(SOURCE_FILES step_assot_cache.cpp)
add_executable(team_train_09_19_2016 ${SOURCE_FILES})