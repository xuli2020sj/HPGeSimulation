project(HPGe_simulation)
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)

#set(Geant4_DIR home/xl/Geant4/geant4.10.07.p03-install)
#message("G4DIR = ${Geant4_DIR}")

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)

if(WITH_GEANT4_UIVIS)
find_package(Geant4 REQUIRED ui_all vis_all)
else()
find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/src
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/util/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/util/*.h)

#----------------------------------------------------------------------------

add_executable(sim simulation.cpp ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})


##execute_process(COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/script ${EXECUTABLE_OUTPUT_PATH}/re)

##add_custom_command(TARGET sim PRE_BUILD
 ##                  COMMAND ${CMAKE_COMMAND} -E copy_directory
 ##                      ${CMAKE_SOURCE_DIR}/script/ $<TARGET_FILE_DIR:sim>)

install(TARGETS sim DESTINATION bin)
