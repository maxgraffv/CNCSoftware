add_library(FileHandling STATIC fileHandling.cpp)

# Include the current directory for header files
target_include_directories(FileHandling PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
