cmake_minimum_required(VERSION 3.15)

project(test_vec VERSION 0.0.1 LANGUAGES C)

# Define the executable
add_executable(test_vec main.c ../vec.c)
target_include_directories(test_vec PRIVATE ..)

# Set build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (default: Debug)" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")   
    # Enable address sanitizer, ub sanitizer and warnings
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            message(STATUS "Using Clang on Windows")
            target_link_libraries(test_vec PRIVATE clang_rt.asan-x86_64)
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            message(STATUS "Using Clang on Linux")
            set(SANITIZER_FLAGS "-fsanitize=address,undefined -fno-omit-frame-pointer")
            set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${SANITIZER_FLAGS} -g")
        endif()
        add_compile_options(-Wall -Wextra)
    elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
        set(SANITIZER_FLAGS "/fsanitize=address")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${SANITIZER_FLAGS} /DEBUG /Od")
        add_compile_options(/W4)
    endif()

    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${SANITIZER_FLAGS}")
endif()

enable_testing()
add_test(test_vec test_vec)