add_library(Priority STATIC GPriority.cpp MPriority.cpp)

# Include the current directory for header files
target_include_directories(Priority PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
