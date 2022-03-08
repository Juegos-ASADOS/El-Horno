@echo off
set EXES=.\..\..\..\Exes
set CMAKE=.\..\..\cmake\bin\cmake.exe
set SRC=..\Src

mkdir .\Build
cd .\Build

%CMAKE% -DOGRE_BUILD_COMPONENT_BITES:BOOL="0"  -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE="0" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="1" -DOGRE_BUILD_PLUGIN_DOT_SCENE="0" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE="0" -DOGRE_BUILD_RENDERSYSTEM_GLES2:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE="0" -DOGRE_BUILD_RENDERSYSTEM_D3D11:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE="0" -DOGRE_BUILD_PLUGIN_ASSIMP:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE="0" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_INSTALL_SAMPLES:BOOL="0" %SRC%
msbuild "OGRE.sln" /p:configuration=Debug
msbuild "OGRE.sln" /p:configuration=Release

XCOPY /y /s .\bin\debug\OgreMain_d.dll %EXES%
XCOPY /y /s .\bin\release\OgreMain.dll %EXES%

XCOPY /y /s .\bin\debug\Codec_STBI_d.dll %EXES%
XCOPY /y /s .\bin\release\Codec_STBI.dll %EXES%

XCOPY /y /s .\bin\release\zlib.dll %EXES%

XCOPY /y /s .\bin\debug\RenderSystem_GL3Plus_d.dll %EXES%
XCOPY /y /s .\bin\release\RenderSystem_GL3Plus.dll %EXES%

XCOPY /y /s .\SDL2-build\RelWithDebInfo\SDL2.dll %EXES%
cd..