function c() { make clean; rm cmake_install.cmake; rm CMakeLists.txt.user; rm CMakeCache.txt; rm -rf CMakeFiles; rm -rf bin; }

function v() { cmake .; make -j8; }
function vd() { cmake -DCMAKE_BUILD_TYPE=Debug .; make -j8; ldd bin/dbg/libdedicatedslave.so; readelf -d bin/dbg/libdedicatedslave.so; }

function b() { v && bin/dbg/dedicatedslave-gui; }

echo "‘c’ - Removes the build files"
echo "‘v’ - Compiles DedicatedSlave"
echo "'vd' - Compiles DedicatedSlave w/ Debug flag"
echo "‘b’ - Compiles and runs DedicatedSlave"

# Windows Packaging
# windeployqt --release build\release\DedicatedSlave.exe
