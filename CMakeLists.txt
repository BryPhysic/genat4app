cmake_minimum_required(VERSION 3.16)
project(MyGeant4Project)

# Encontrar Geant4
find_package(Geant4 REQUIRED)

# Incluir configuraciones de Geant4
include(${Geant4_USE_FILE})

# Agregar ejecutable
add_executable(mySimulation main.cc MyDetectorConstruction.cc)

# Enlazar todas las bibliotecas necesarias
target_link_libraries(mySimulation ${Geant4_LIBRARIES})