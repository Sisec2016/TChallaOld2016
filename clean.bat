@echo off
setlocal
call "%VS120COMNTOOLS%vsvars32.bat
MSBUILD %CD%\FastVideoPro\FastVideo.sln /t:Clean /p:Configuration=Release

REM RD /S /Q  demo\Launcher\Debug


exit /b %ERRORLEVEL%
endlocal
pause