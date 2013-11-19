# This submodule contains all the facilities required to run Forge
# on a specific platform (Linux, Windows, Mac)
set(PlatformFileSystemSources
  File.cpp
)

set(PlatformFileSystemHeaders
  Directory.hpp
  File.hpp
)

if (UNIX)
  list(APPEND PlatformFileSystemSources
    Posix/Directory.cpp
  )
endif()

add_library(PlatformFileSystem ${PlatformFileSystemSources} ${PlatformFileSystemHeaders})
