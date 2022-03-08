@echo off
set CEGUIDir=%~dp0\
set EXES=.\..\..\..\..\Exes
set CMAKE=.\..\..\cmake\bin\cmake.exe
set CMAKEDEP=.\..\..\..\cmake\bin\cmake.exe

mkdir .\dependencies\build
cd .\dependencies\build

%CMAKEDEP% -DCEGUI_BUILD_EFFECTS11:BOOL="0" -DCEGUI_BUILD_GLFW:BOOL="0" ..\
pause
msbuild "CEGUI-DEPS.sln" /p:configuration=Debug /maxcpucount
msbuild "CEGUI-DEPS.sln" /p:configuration=Release /maxcpucount

xcopy /y /s .\dependencies .\..\..\Src
cd .\..\..

mkdir .\build
cd .\build 
%CMAKE% -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="0" -DCEGUI_BUILD_IMAGECODEC_SDL2:BOOL="1" -DCEGUI_BUILD_RENDERER_OGRE:BOOL="1" -DCEGUI_BUILD_OPENGL:BOOL="0" -DOGRE_LIB_DBG:FILEPATH=".\..\..\Ogre\Build\lib\Debug\OgreMain_d.lib" -DOGRE_H_PATH:PATH=".\..\..\Ogre\Src\OgreMain\include" -DOGRE_LIB:FILEPATH=".\..\..\Ogre\Build\lib\Release\OgreMain.lib" -DOGRE_H_BUILD_SETTINGS_PATH:PATH=".\..\..\Ogre\Build\include" ..\Src
msbuild "cegui.sln" /p:configuration=Release /maxcpucount
msbuild "cegui.sln" /p:configuration=Debug /maxcpucount

cd .\bin

xcopy .\CEGUIBase-0.dll %EXES%
xcopy .\CEGUIBase-0_d.dll %EXES%

xcopy .\CEGUIExpatParser.dll %EXES%
xcopy .\CEGUIExpatParser_d.dll %EXES%

xcopy .\CEGUIOgreRenderer-0.dll %EXES%
xcopy .\CEGUIOgreRenderer-0_d.dll %EXES%

cd ..\..\dependencies\bin
xcopy .\FreeImage_d.dll %EXES%
xcopy .\freetype_d.dll %EXES%
xcopy .\freetype.dll %EXES%

xcopy .\glew.dll %EXES%
xcopy .\glew_d.dll %EXES%

xcopy .\jpeg.dll %EXES%
xcopy .\jpeg_d.dll %EXES%

xcopy .\libexpat.dll %EXES%
xcopy .\libexpat_d.dll %EXES%

xcopy .\pcre.dll %EXES%
xcopy .\pcre_d.dll %EXES%

cd ..\..

pause