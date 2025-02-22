add_library(GcodeCommand STATIC gcodeCommand.cpp)

target_link_libraries(GcodeCommand PUBLIC Priority)
# Include the current directory for header files
target_include_directories(GcodeCommand PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
