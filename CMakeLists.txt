cmake_minimum_required(VERSION 3.16)
project(G4Sim)

# Find Geant4 package
find_package(Geant4 REQUIRED)

# Include Geant4 headers and libraries
include(${Geant4_USE_FILE})

# This tells the compiler to look in the 'include' folder for .hh files
include_directories(include)

# Create the executable
add_executable(sim sim.cc src/construction.cc src/generator.cc src/action.cc)
target_link_libraries(sim ${Geant4_LIBRARIES})