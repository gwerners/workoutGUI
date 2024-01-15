#!/run/current-system/sw/bin/bash
#/bin/bash -x

argc=$#

#https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/
set -euo pipefail

#show commands (for debuging)
#set -x

#move to script dir 
cd "$(dirname "${0}")"

#save current dir as base dir
ROOT=$(pwd)


#avoid rm error if file doesn't exists
function safeRM {
  for file in ${@} ; do
    if [[ -f "${file}" ]]; then
      rm "${file}"
    fi
  done
}
#avoid rm error if directory doesn't exists
function safeRMDIR {
  for dir in ${@} ; do
    if [[ -d "${dir}" ]]; then
      rm -rf "${dir}"
    fi
  done
}
function safeMKDIR {
  if [[ ! -d "$1" ]]; then
    mkdir "$1"
  fi
}
function CheckNeeded {
  NEEDED=$(which ${1})
  if [ ! -f "${NEEDED}" ]; then
    echo "${1} is a dependency, you must install it first!"
    exit 0
  fi
}
function cleanOldBuild {
  ./clean.bash build
}
function get {
  if [ ! -d "rlImGui" ]; then
    if [ ! -f "rlImGui.tar.gz" ]; then
      git clone https://github.com/raylib-extras/rlImGui.git
      tar -czf rlImGui.tar.gz rlImGui
    else
      tar -xzf rlImGui.tar.gz
    fi
  fi
  if [ ! -d "raylib" ]; then
    if [ ! -f "raylib.tar.gz" ]; then
      git clone https://github.com/raysan5/raylib.git
      tar -czf raylib.tar.gz raylib
    else
      tar -xzf raylib.tar.gz
    fi
  fi
  if [ ! -d "imgui" ]; then
    if [ ! -f "imgui.tar.gz" ]; then
      git clone https://github.com/ocornut/imgui.git
      tar -czf imgui.tar.gz imgui
    else
      tar -xzf imgui.tar.gz
    fi
  fi
}
function build {
  pushd raylib
    mkdir -p build
    pushd build
      cmake .. -G Ninja
      ninja
    popd
  popd
  mkdir -p build
  pushd build
    cmake .. -G Ninja
    ninja
  popd
}
function run {
  #nix-index -> need to increase swap!
  #nix-locate libpulse.so
  #export LD_LIBRARY_PATH=/nix/store/pq1n77jycvr305w3sfi6a79scffzwm6x-pulseaudio-16.1/lib
   export LD_LIBRARY_PATH=$(nix eval -f '<nixpkgs>' --raw pulseaudio)/lib
  ./build/src/Convict
}

###############################################################################
#script main:
CheckNeeded g++ || exit 1
CheckNeeded cmake || exit 1
CheckNeeded git  || exit 1
get
build
run

###############################################################################
function tmpSwapFile {
  SWAP_FILE="$(pwd)/myswapfile"
  echo "Deactivating all swaps that are used"
  sudo swapoff -a

  #temporary swap
  sudo fallocate -l 10G $(pwd)/myswapfile
  sudo dd if=/dev/zero of=$(pwd)/myswapfile bs=1024 count=10485760
  sudo chmod 600 $(pwd)/myswapfile
  sudo mkswap $(pwd)/myswapfile
  sudo swapon $(pwd)/myswapfile

  #sudo swapoff $(pwd)/myswapfile
}
