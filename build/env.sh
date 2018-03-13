function c() { make clean; rm cmake_install.cmake; rm CMakeLists.txt.user; rm CMakeCache.txt; rm -rf CMakeFiles; rm -rf bin; }
function b() { cmake .; make -j8; }
function bd() { cmake -DCMAKE_BUILD_TYPE=Debug .; make -j8; ldd bin/dbg/libdedicatedslave.so; readelf -d bin/dbg/libdedicatedslave.so; }
function br() { v && sh -c 'cd bin && ./dedicatedslave-gui' }
function r() { sh -c 'cd bin && ./dedicatedslave-gui'}

echo "‘c’ - Clean the build files"
echo "‘b’ - Build DedicatedSlave"
echo "'bd' - Build DedicatedSlave w/ Debug flag"
echo "‘br’ - Build and runs DedicatedSlave"
echo "‘r’ - Runs DedicatedSlave"

# Windows Packaging
# windeployqt --release build\release\DedicatedSlave.exe