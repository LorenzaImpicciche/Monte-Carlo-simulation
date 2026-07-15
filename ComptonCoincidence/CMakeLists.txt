cmake_minimum_required(VERSION 3.16)
project(ComptonCoincidence)

# Trova Geant4 con i moduli per l'interfaccia UI e la Visualizzazione
find_package(Geant4 REQUIRED ui_all vis_all)

# Configura l'uso di Geant4
include(${Geant4_USE_FILE})

# Include la cartella degli header
include_directories(${PROJECT_SOURCE_DIR}/include)

# Cerca tutti i file sorgente nella cartella src
file(GLOB SOURCES src/*.cc)

# Crea l'eseguibile
add_executable(ComptonSim ComptonSim.cc ${SOURCES})
target_link_libraries(ComptonSim ${Geant4_LIBRARIES})

# Copia i file macro nella cartella build per comodità
set(SCRIPTS study_geom.mac)
foreach(_script ${SCRIPTS})
  configure_file(${PROJECT_SOURCE_DIR}/${_script} ${PROJECT_BINARY_DIR}/${_script} COPYONLY)
endforeach()