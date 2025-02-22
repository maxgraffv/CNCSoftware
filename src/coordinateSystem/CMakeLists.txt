add_library(CoordinateSystem STATIC CoordinateSystem.cpp)

# Include the current directory for header files
target_include_directories(CoordinateSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
