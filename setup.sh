# This script sets up git submodules and gets rid of
# the demos of isometric_engine and sdl_wrapper so
# that CMake doesn't try to compile and add these
# to atowers.

git submodule init
git submodule update --init --recursive

mv src/isometric_engine/src/* src/isometric_engine/
rm -rf src/isometric_engine/src/

rm src/isometric_engine/Game.cpp
rm src/isometric_engine/Game.hpp

rm src/isometric_engine/sdl_wrapper/Demo.cpp
rm src/isometric_engine/sdl_wrapper/Demo.hpp

mkdir build/
cp -R res/ build/
