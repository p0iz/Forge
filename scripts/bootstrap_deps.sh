#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")"/.. && pwd)"

function print_step() {
  echo -e "\033[1;34m==>\033[0m $1"
}

function require_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "Error: required command '$1' not found. Please install it and re-run." >&2
    exit 1
  fi
}

function run_with_sudo() {
  local cmd=("$@")
  if [[ $EUID -ne 0 ]]; then
    cmd=(sudo "${cmd[@]}")
  fi
  "${cmd[@]}"
}

function install_with_apt() {
  print_step "Installing packages via apt"
  local packages=(
    build-essential
    cmake
    pkg-config
    libsdl2-dev
    libglew-dev
    libglm-dev
    libfreetype6-dev
    libfreeimage-dev
    liblua5.4-dev
    qtbase5-dev
  )
  run_with_sudo apt-get update
  run_with_sudo apt-get install -y "${packages[@]}"
}

function install_with_dnf() {
  print_step "Installing packages via dnf"
  local packages=(
    @development-tools
    cmake
    pkgconf-pkg-config
    SDL2-devel
    glew-devel
    glm-devel
    freetype-devel
    FreeImage-devel
    lua-devel
    qt5-qtbase-devel
  )
  run_with_sudo dnf install -y "${packages[@]}"
}

function install_with_pacman() {
  print_step "Installing packages via pacman"
  local packages=(
    base-devel
    cmake
    sdl2
    glew
    glm
    freetype2
    freeimage
    lua
    qt5-base
  )
  run_with_sudo pacman -Sy --needed "${packages[@]}"
}

function install_with_brew() {
  print_step "Installing packages via Homebrew"
  local packages=(
    cmake
    sdl2
    glew
    glm
    freetype
    freeimage
    lua
    qt@5
  )
  brew update
  brew install "${packages[@]}"
  if brew --prefix qt@5 >/dev/null 2>&1; then
    local qt_prefix
    qt_prefix="$(brew --prefix qt@5)"
    print_step "Adding Qt5 to CMAKE_PREFIX_PATH"
    if ! grep -q "CMAKE_PREFIX_PATH" "${ROOT_DIR}/.env" 2>/dev/null; then
      cat <<EOF_ENV >> "${ROOT_DIR}/.env"
# Added by scripts/bootstrap_deps.sh
export CMAKE_PREFIX_PATH="${qt_prefix}/lib/cmake:${CMAKE_PREFIX_PATH:-}"
EOF_ENV
    fi
  fi
}

function unsupported() {
  echo "Unsupported platform or package manager. Please install dependencies manually." >&2
  exit 1
}

print_step "Detecting platform"
uname_out="$(uname -s)"
case "$uname_out" in
  Linux*)
    if command -v apt-get >/dev/null 2>&1; then
      install_with_apt
    elif command -v dnf >/dev/null 2>&1; then
      install_with_dnf
    elif command -v pacman >/dev/null 2>&1; then
      install_with_pacman
    else
      unsupported
    fi
    ;;
  Darwin*)
    require_command brew
    install_with_brew
    ;;
  *)
    unsupported
    ;;
esac

print_step "Dependency bootstrap complete"
