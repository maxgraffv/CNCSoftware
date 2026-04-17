cmake_minimum_required(VERSION 3.16)
project(CNCSoftware CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(cncOS ${SOURCES})

target_include_directories(cncOS PRIVATE
    include/core
    include/motion
    include/gcode
    include/tools
    include/hal
    include/config
)

# wiringPi is only available on Raspberry Pi
if(NOT APPLE)
    target_link_libraries(cncOS wiringPi)
endif()

target_compile_options(cncOS PRIVATE -Wall -Wextra)
