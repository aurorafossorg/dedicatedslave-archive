DATE=`date '+%Y-%m-%d %H:%M:%S'`
function c() { make clean; rm cmake_install.cmake; rm CMakeLists.txt.*; rm CMakeCache.txt; rm -rf CMakeFiles; rm -rf out; }
function b() { cmake .; make -j8; }
function bd() { cmake -DCMAKE_BUILD_TYPE=Debug .; make -j8; ldd bin/dbg/libdedicatedslave.so; readelf -d bin/dbg/libdedicatedslave.so; }
function br() { b; r;}
function r() { sh -c 'cd out/bin && ./dedicatedslave-gui'}
function rc() { sh -c 'cd out/bin && ./dedicatedslave'}
function p() { git add .; git commit -m "Script Deploy - `echo ${DATE}`"; git push; }

echo "‘c’ - Clean the build files"
echo "‘b’ - Build"
echo "'bd' - Build w/ Debug flag"
echo "‘br’ - Build and runs"
echo "‘r’ - Runs GUI"
echo "‘rc’ - Runs CLI"
echo "‘p’ - Push"

# Windows Packaging
# windeployqt --release build\release\DedicatedSlave.exe
