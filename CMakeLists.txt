cmake_minimum_required(VERSION 3.10)
project(CNCSoftware)

set(CMAKE_CXX_STANDARD 20) 

add_executable(CNCSoftware src/main.cpp)

# Add subdirectories for each module
add_subdirectory(src/arch)
add_subdirectory(src/enums)
add_subdirectory(src/hardware)
add_subdirectory(src/cncSetup)
add_subdirectory(src/arcPathGenerator)
add_subdirectory(src/coordinateSystem)
add_subdirectory(src/fileHandling)
add_subdirectory(src/gcodeCommand)
add_subdirectory(src/gcodeFile)
add_subdirectory(src/mock)
add_subdirectory(src/priorities)


# Create the executable from main.cpp

# Link modules (libraries) to the main executable
target_link_libraries(CNCSoftware PRIVATE 
    ArcPathGenerator 
    CoordinateSystem
    FileHandling
    GcodeCommand
    GcodeFile
    WiringMac
    LimitSwitch
    Motor 
    StepperMotor 
    Spindle
    Tool
    CNCSetup 
    Priority
    
)
target_include_directories(CNCSoftware PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/enums)
target_include_directories(CNCSoftware PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/arch)
