add_library(ArcPathGenerator STATIC arcPathGenerator.cpp)

target_link_libraries(ArcPathGenerator PUBLIC Enums)
# Include the current directory for header files
target_include_directories(ArcPathGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
