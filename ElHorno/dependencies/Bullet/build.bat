@echo off
set EXES=.\..\..\..\Exes
set CMAKE=.\..\..\cmake\bin\cmake.exe
set SRC=..\Src

mkdir .\Build
cd .\Build

%CMAKE% -DBUILD_BULLET2_DEMOS:BOOL="0" -DBUILD_CLSOCKET:BOOL="0" -DBUILD_CPU_DEMOS:BOOL="0" -DBUILD_ENET:BOOL="0" -DBUILD_OPENGL3_DEMOS:BOOL="0" -DBUILD_UNIT_TESTS:BOOL="0" -DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL="1" %SRC%
msbuild "BULLET_PHYSICS.sln" /p:configuration=Debug
msbuild "BULLET_PHYSICS.sln" /p:configuration=Release

cd..