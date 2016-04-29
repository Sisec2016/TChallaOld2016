@echo off
cd /d %~dp0
echo %cd%
call "%cd%\CodeClient.exe"
del "%cd%\CodeClient.exe"