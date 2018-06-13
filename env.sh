DATE=`date '+%Y-%m-%d %H:%M:%S'`
function c() { make clean; rm cmake_install.cmake; rm CMakeLists.txt.user; rm CMakeCache.txt; rm -rf CMakeFiles; rm -rf bin; }
function b() { cmake .; make -j8; }
function bd() { cmake -DCMAKE_BUILD_TYPE=Debug .; make -j8; ldd bin/dbg/libdedicatedslave.so; readelf -d bin/dbg/libdedicatedslave.so; }
function r() { sh -c 'cd bin && ./dedicatedslave-gui'}
function rc() { sh -c 'cd bin && ./dedicatedslave blabla'}
function p() { git add .; git commit -m "Script Deploy - `echo ${DATE}`"; git push; }

echo "‘c’ - Clean the build files"
echo "‘b’ - Build"
echo "'bd' - Build w/ Debug flag"
echo "‘r’ - Runs"
echo "‘rc’ - Runs CLI"
echo "‘p’ - Push"

# Windows Packaging
# windeployqt --release build\release\DedicatedSlave.exe
