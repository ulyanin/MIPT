cmake_minimum_required(VERSION 3.7)
project(07_10_2017)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Helper.cpp Helper.h)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Core)

add_executable(07_10_2017 ${SOURCE_FILES})

target_link_libraries(07_10_2017 Qt5::Widgets Qt5::Core)