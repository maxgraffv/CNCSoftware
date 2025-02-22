add_library(GcodeFile STATIC gcodeFile.cpp)

target_link_libraries(GcodeFile PUBLIC FileHandling)
target_link_libraries(GcodeFile PUBLIC GcodeCommand)

# Include the current directory for header files
target_include_directories(GcodeFile PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
