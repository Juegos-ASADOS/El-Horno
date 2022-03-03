@echo off
set EXES=.\..\..\..\Exes

cd .\Src

msbuild "lua.sln" /p:configuration=Debug
msbuild "lua.sln" /p:configuration=Release

XCOPY /y /s .\lib\Debug\lua_d.dll %EXES%
XCOPY /y /s .\lib\Release\lua.dll %EXES%

cd..