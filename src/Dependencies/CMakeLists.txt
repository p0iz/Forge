cmake_minimum_required(VERSION 2.8.10)

# Project to build all dependencies for Forge
project(ForgeDeps)

include(ExternalProject)

set(DEPS_TARGET_DIR ${CMAKE_SOURCE_DIR}/prefix CACHE PATH "The path where Forge dependencies are stored after building")

ExternalProject_Add(SDL
  DOWNLOAD_COMMAND hg clone http://hg.libsdl.org/SDL
  UPDATE_COMMAND ./autogen.sh
  CONFIGURE_COMMAND ./configure --prefix=${DEPS_TARGET_DIR}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
)

ExternalProject_Add(SDL_image
  DEPENDS SDL
  DOWNLOAD_COMMAND hg clone http://hg.libsdl.org/SDL_image
  UPDATE_COMMAND ./autogen.sh
  CONFIGURE_COMMAND ./configure --with-sdl-prefix=${DEPS_TARGET_DIR} --prefix=${DEPS_TARGET_DIR}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
)

ExternalProject_Add(SDL_ttf
  DEPENDS SDL
  DOWNLOAD_COMMAND hg clone http://hg.libsdl.org/SDL_ttf
  UPDATE_COMMAND ./autogen.sh
  CONFIGURE_COMMAND ./configure --with-sdl-prefix=${DEPS_TARGET_DIR} --prefix=${DEPS_TARGET_DIR}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
)

ExternalProject_Add(GLM
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.5.4
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/GLM-prefix/src/GLM/glm ${DEPS_TARGET_DIR}/include/glm
)

ExternalProject_Add(GLEW
  GIT_REPOSITORY https://github.com/nigels-com/glew.git
  CONFIGURE_COMMAND make -C auto
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND GLEW_DEST=${DEPS_TARGET_DIR} make install
)

ExternalProject_Add(LuaJIT
  GIT_REPOSITORY http://luajit.org/git/luajit-2.0.git
  CONFIGURE_COMMAND echo Auto-configuring LuaJIT
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install PREFIX=${DEPS_TARGET_DIR}
)
