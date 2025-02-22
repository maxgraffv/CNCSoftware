add_library(Tool STATIC Tool.cpp)

# Include the current directory for header files
target_include_directories(Tool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
