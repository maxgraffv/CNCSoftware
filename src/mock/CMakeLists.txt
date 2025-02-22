add_library(WiringMac STATIC wiringMac.cpp)

# Include the current directory for header files
target_include_directories(WiringMac PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
