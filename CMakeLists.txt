cmake_minimum_required(VERSION 3.7)
project(Testimony)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES temp/main.c ButtHandlers.h ButtHandlers.cpp FSMUtils.h FSMUtils.cpp)
add_executable(Testimony ${SOURCE_FILES})