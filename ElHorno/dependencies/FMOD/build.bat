@echo off 
set EXES=.\..\..\Exes

XCOPY /y /s .\Src\lib\fmod.dll %EXES%
XCOPY /y /s .\Src\lib\fmodL.dll %EXES%

XCOPY /y /s .\Src\lib\fmodstudio.dll %EXES%
XCOPY /y /s .\Src\lib\fmodstudioL.dll %EXES%

XCOPY /y /s .\Src\lib\fsbank.dll %EXES%
XCOPY /y /s .\Src\lib\libfsbvorbis.dll %EXES%
XCOPY /y /s .\Src\lib\opus.dll %EXES%