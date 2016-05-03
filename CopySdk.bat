@echo off
REM Reduce sdk folder
REM Make directorys of sdk vender item
REM only copy *.dll files
SETLOCAL
SET SDKDIR=sdk
SET SDKDEST=bin\factorys
SET REPLACESTRING=VideoServer

IF NOT EXIST %CD%\%SDKDIR% GOTO :EOF
IF NOT EXIST %CD%\%SDKDEST% GOTO :EOF

FOR /F "delims=" %%A IN ('DIR /AD /B %SDKDIR%') DO (

	REM IF NOT EXIST %CD%\%SDKDEST%\%%A MD %CD%\%SDKDEST%\%%A
	@ECHO COPY DLL 
	@ECHO FROM %CD%\%SDKDIR%\%%A\SDK\ 
	@ECHO TO %CD%\%SDKDEST%\%%A
	REM %%A has VideoServer postfix remove it
	CALL :SUPERCOPY %%A
	REM XCOPY %CD%\%SDKDIR%\%%A\SDK\*.dll %CD%\%SDKDEST%\test\%DIRNAME:VideoServer=% /S /Q /Y 2>nul
)
ENDLOCAL & GOTO :EOF

:SUPERCOPY [%1 - PARAM]
SETLOCAL
@ECHO "ProcessParam : %1"
SET PARAM=%1
SET DNAME=%PARAM:VideoServer=%
ECHO %CD%\%SDKDIR%\%PARAM%\SDK\*.dll %CD%\%SDKDEST%\%DNAME%\ /S /Q /Y 2>nul
XCOPY %CD%\%SDKDIR%\%PARAM%\SDK\*.dll %CD%\%SDKDEST%\%DNAME%\ /S /Q /Y 2>nul
ENDLOCAL




