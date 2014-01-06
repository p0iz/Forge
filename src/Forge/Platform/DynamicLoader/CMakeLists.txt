# This submodule contains all the facilities required to load
# shared libraries at run-time

set(DynamicLoaderHeaders
  DynamicLibrary.hpp
  DynamicLoader.hpp
  LibraryHandle.hpp
)

if(UNIX)
  set(DynamicLoaderSources
    Posix/DynamicLibrary_Posix.cpp
    Posix/DynamicLoader_Posix.cpp
  )
elseif(WIN32)
  set(DynamicLoaderSources
    Win32/DynamicLibrary_Win32.cpp
    Win32/DynamicLoader_Win32.cpp
  )
endif()

list(APPEND DynamicLoaderSources
  DynamicLibrary.cpp
  DynamicLoader.cpp
)

add_library(PlatformDynamicLoader ${DynamicLoaderSources} ${DynamicLoaderHeaders})
