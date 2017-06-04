cmake_minimum_required(VERSION 3.7)
project(poj)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp POJ2185.h POJ1743.h HDU2222.h POJ3321.h POJ2828.h HDU1890.h POJ2019.h HDU2665.h HDU3966.h)
add_executable(poj ${SOURCE_FILES})