add_library(Motor STATIC motor.cpp)

target_link_libraries(Motor PUBLIC Enums)

# Include the current directory for header files
target_include_directories(Motor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
