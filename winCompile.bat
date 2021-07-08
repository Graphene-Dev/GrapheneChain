@echo off
echo "This commands run the commands in README for you, if it failes make sure you got cmake and visual studio 2019 and its c++ plugins downloaded"
sleep 5
mkdir build
cd build 
cmake -G "Visual Studio 16 2019" -A x64 .. 
MSBuild GrapheneChain.sln
echo "Compiling is done! Now the files should be in Debug or Release"
sleep 4