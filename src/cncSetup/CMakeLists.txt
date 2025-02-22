add_library(CNCSetup STATIC cncSetup.cpp)

target_link_libraries(CNCSetup PUBLIC StepperMotor)
target_link_libraries(CNCSetup PUBLIC Spindle)
target_link_libraries(CNCSetup PUBLIC GcodeFile)
target_link_libraries(CNCSetup PUBLIC Tool)
target_link_libraries(CNCSetup PUBLIC CoordinateSystem)
target_link_libraries(CNCSetup PUBLIC LimitSwitch)
target_link_libraries(CNCSetup PUBLIC ArcPathGenerator)
# Include the current directory for header files
target_include_directories(CNCSetup PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
