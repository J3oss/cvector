cmake_minimum_required(VERSION 3.15)

project(vec VERSION 0.0.1 LANGUAGES C)

option(VEC_BUILD_TEST "Build Test" ON)
option(VEC_LIB "Build Lib" OFF)

if(VEC_BUILD_TEST)
    add_subdirectory(test)
endif()

if(VEC_LIB)
    add_library(vec vec.c)
    target_include_directories(vec PRIVATE include)
endif()