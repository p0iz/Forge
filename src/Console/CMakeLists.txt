cmake_minimum_required(VERSION 2.8.10)

# Application for managing Forge projects
project(ForgeConsole)

set(ForgeCLI_SRC
  main.cpp
  commands/cmdparse.cpp
  commands/cmdprinttext.cpp
  commands/cmdrun.cpp
)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -fno-exceptions")

include_directories(../Forge)

add_executable(forge ${ForgeCLI_SRC})
add_dependencies(forge Forge)

if(WIN32)
  add_library(ForgeDLL SHARED IMPORTED)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Forge/Forge.dll)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_IMPLIB ${CMAKE_BINARY_DIR}/src/Forge/libForge.dll.a)
else()
  add_library(ForgeDLL SHARED IMPORTED)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Forge/libForge.so)
endif()

target_link_libraries(forge ForgeDLL ${Win32LinkerFlag})
