# This submodule contains all the facilities required to run Forge
# on a specific platform (Linux, Windows, Mac)

set(PlatformFileSystemHeaders
  Directory.hpp
  File.hpp
)

if(UNIX)
  set(PlatformFileSystemSources
    Posix/Directory.cpp
  )
elseif(WIN32)
  set(PlatformFileSystemSources
    Win32/Directory.cpp
  )
endif()

list(APPEND PlatformFileSystemSources
  Directory.cpp
  File.cpp
)

add_library(PlatformFileSystem ${PlatformFileSystemSources} ${PlatformFileSystemHeaders})
