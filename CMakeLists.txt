project(HPGe_simulation)
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)


#设置工程源码根目录
set(Simulation_Root ${CMAKE_CURRENT_SOURCE_DIR}/src)

#设置头文件目录
INCLUDE_DIRECTORIES(${Simulation_Root})

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)

if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

add_executable(HPGe_simulation HPGe_simulation.cc ${sources} ${headers})
target_link_libraries(HPGe_simulation ${Geant4_LIBRARIES} )

execute_process(COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/script ${EXECUTABLE_OUTPUT_PATH}/)


