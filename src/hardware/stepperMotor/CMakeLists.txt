add_library(StepperMotor STATIC stepperMotor.cpp)

target_link_libraries(StepperMotor PUBLIC Enums)
target_link_libraries(StepperMotor PUBLIC Motor)
target_link_libraries(StepperMotor PUBLIC WiringMac)

# Include the current directory for header files
target_include_directories(StepperMotor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
