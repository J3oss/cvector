cmake_minimum_required(VERSION 3.15)

project(cvec VERSION 0.0.1 LANGUAGES C)

option(CVEC_BUILD_TEST "Build Test" ON)
option(CVEC_LIB "Build Lib" OFF)

if(CVEC_BUILD_TEST)
    add_subdirectory(test)
endif()

if(CVEC_LIB)
    add_library(cvec cvec.c)
    target_include_directories(cvec PRIVATE include)
endif()