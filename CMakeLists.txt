cmake_minimum_required(VERSION 2.8)
project(hello-world)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
add_definitions("-DQT_NO_PRINTER=1")
add_executable(hello_world main.cc plot.cc thirdparty/qcustomplot.cpp)

qt5_use_modules(hello_world Widgets)
