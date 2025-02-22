add_library(Spindle STATIC spindle.cpp)

target_link_libraries(Spindle PUBLIC Motor)
target_link_libraries(Spindle PUBLIC WiringMac)

# Include the current directory for header files
target_include_directories(Spindle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
