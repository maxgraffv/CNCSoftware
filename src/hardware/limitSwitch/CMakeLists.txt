add_library(LimitSwitch STATIC LimitSwitch.cpp)

# Include the current directory for header files
target_include_directories(LimitSwitch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
