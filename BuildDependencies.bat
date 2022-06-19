@echo off
cls
set BAT=build.bat

cd .\ElHorno\dependencies\

cd .\Ogre\
call %BAT%

cd ..\Bullet\
call %BAT%

cd ..\FMOD\
call %BAT%

cd ..\lua\
call %BAT%

cd ..\cegui\
call %BAT%
