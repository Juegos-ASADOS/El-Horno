@echo off
cls

cd .\ElHorno

msbuild "ElHorno.sln" /p:configuration=Debug
msbuild "ElHorno.sln" /p:configuration=Release