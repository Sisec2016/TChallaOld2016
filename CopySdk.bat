@echo off
REM Reduce sdk folder
REM Make directorys of sdk vender item
REM only copy *.dll files
SETLOCAL
SET SDKDIR=sdk
SET SDKDEST=bin\factorys

IF NOT EXIST %CD%\%SDKDIR% GOTO :EOF
IF NOT EXIST %CD%\%SDKDEST% GOTO :EOF

FOR /F "delims=" %%A IN ('DIR /AD /B %SDKDIR%') DO (

	IF NOT EXIST %CD%\%SDKDEST%\%%A MD %CD%\%SDKDEST%\%%A
	@ECHO COPY DLL 
	@ECHO FROM %CD%\%SDKDIR%\%%A\SDK\ 
	@ECHO TO %CD%\%SDKDEST%\%%A
	XCOPY %CD%\%SDKDIR%\%%A\SDK\*.dll %CD%\%SDKDEST%\%%A /S /Q /Y 2>nul
)
ENDLOCAL
