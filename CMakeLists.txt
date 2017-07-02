cmake_minimum_required(VERSION 2.8)
project(plot)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
add_definitions("-DQT_NO_PRINTER=1")
add_executable(plot main.cc window.cc color_graph.cc stream_plot.cc thirdparty/qcustomplot.cpp)

qt5_use_modules(plot Widgets)
