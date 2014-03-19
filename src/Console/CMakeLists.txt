# The test app
set(ForgeCLI_SRC
  main.cpp
)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -fno-exceptions")

include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

add_executable(forge-cli ${ForgeCLI_SRC})
add_dependencies(forge-cli Forge)

if(WIN32)
  add_library(ForgeDLL SHARED IMPORTED)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Forge/Forge.dll)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_IMPLIB ${CMAKE_BINARY_DIR}/src/Forge/libForge.dll.a)
else()
  add_library(ForgeDLL SHARED IMPORTED)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Forge/libForge.so)
endif()

target_link_libraries(forge-cli ForgeDLL ${Win32LinkerFlag})
