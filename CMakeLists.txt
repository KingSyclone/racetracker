cmake_minimum_required(VERSION 3.10)
project(racetracker)

set(CMAKE_CXX_STANDARD 17)

# Find GeographicLib
find_package(GeographicLib REQUIRED)

# Set up the source files
set(SOURCES
    src/main.cpp
    src/EnduranceEvent.cpp
    src/SkidpadEvent.cpp
    src/AccelerationEvent.cpp
    src/Timer.cpp
    src/utils.cpp
)

# Include directories
include_directories(include)

# Create the executable
add_executable(racetracker ${SOURCES})

# Link GeographicLib
target_link_libraries(racetracker GeographicLib)
