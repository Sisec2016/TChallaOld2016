@echo off
setlocal
echo MSBUILD Clean Project
call "%VS120COMNTOOLS%vsvars32.bat
MSBUILD %CD%\FastVideoPro\FastVideo.sln /t:Clean /p:Configuration=Debug
MSBUILD %CD%\FastVideoPro\FastVideo.sln /t:Clean /p:Configuration=Release

echo Delete Project Generated Files

RD /S /Q  download\release
RD /S /Q  download\GeneratedFiles
RD /S /Q  download\Win32

RD /S /Q  Start\release
RD /S /Q  Start\GeneratedFiles
RD /S /Q  Start\Win32

RD /S /Q  videoReg\release
RD /S /Q  videoReg\GeneratedFiles
RD /S /Q  videoReg\Win32

RD /S /Q  VideoServer\release
RD /S /Q  VideoServer\GeneratedFiles
RD /S /Q  VideoServer\Win32

RD /S /Q FastVideoPro\Win32

RD /S /Q FastVideoPro\FastVideo\release
RD /S /Q FastVideoPro\FastVideo\GeneratedFiles
RD /S /Q FastVideoPro\FastVideo\Win32

RD /S /Q FastVideoPro\FastVideov1\release
RD /S /Q FastVideoPro\FastVideov1\GeneratedFiles

RD /S /Q FastVideoPro\FastVideo\VideoDownloader\Debug
RD /S /Q FastVideoPro\FastVideo\VideoDownloader\release
RD /S /Q FastVideoPro\FastVideo\VideoDownloader\GeneratedFiles
RD /S /Q FastVideoPro\FastVideo\VideoDownloader\Win32

RD /S /Q FastVideoPro\FastVideov1\VideoDownloader\Debug
RD /S /Q FastVideoPro\FastVideov1\VideoDownloader\release
RD /S /Q FastVideoPro\FastVideov1\VideoDownloader\GeneratedFiles
RD /S /Q FastVideoPro\FastVideov1\VideoDownloader\Win32

RD /S /Q sdk\BlueSkyVideoServer\release
RD /S /Q sdk\BoLiVideoServer\release
RD /S /Q sdk\DHVideoServer\release
RD /S /Q sdk\DiZhiPuVideoServer\release
RD /S /Q sdk\DLDMVideoServer\release
RD /S /Q sdk\DongYang\release
RD /S /Q sdk\HAIKVideoServer\release
RD /S /Q sdk\HanBangVideoServer\release
RD /S /Q sdk\HangJingVideoServer\release
RD /S /Q sdk\JiuAnVideoServer\release
RD /S /Q sdk\JunMingShiVideoServer\release
RD /S /Q sdk\JXJVideoServer\release
RD /S /Q sdk\TianDiWeiYe\release
RD /S /Q sdk\TongWeiVideoServer\release
RD /S /Q sdk\VideoDownloader\release
RD /S /Q sdk\WoShiDaVideoServer\release
RD /S /Q sdk\XingWangVideoServer\release
RD /S /Q sdk\YyShiKejiVideoServer\release
RD /S /Q sdk\ZhongWeiVideoServer\release

RD /S /Q sdk\BlueSkyVideoServer\debug
RD /S /Q sdk\BoLiVideoServer\debug
RD /S /Q sdk\DHVideoServer\debug
RD /S /Q sdk\DiZhiPuVideoServer\debug
RD /S /Q sdk\DLDMVideoServer\debug
RD /S /Q sdk\DongYang\debug
RD /S /Q sdk\HAIKVideoServer\debug
RD /S /Q sdk\HanBangVideoServer\debug
RD /S /Q sdk\HangJingVideoServer\debug
RD /S /Q sdk\JiuAnVideoServer\debug
RD /S /Q sdk\JunMingShiVideoServer\debug
RD /S /Q sdk\JXJVideoServer\debug
RD /S /Q sdk\TianDiWeiYe\debug
RD /S /Q sdk\TongWeiVideoServer\debug
RD /S /Q sdk\VideoDownloader\debug
RD /S /Q sdk\WoShiDaVideoServer\debug
RD /S /Q sdk\XingWangVideoServer\debug
RD /S /Q sdk\YyShiKejiVideoServer\debug
RD /S /Q sdk\ZhongWeiVideoServer\debug

RD /S /Q sdk\BlueSkyVideoServer\Win32\
RD /S /Q sdk\BoLiVideoServer\Win32\
RD /S /Q sdk\DHVideoServer\Win32\
RD /S /Q sdk\DiZhiPuVideoServer\Win32\
RD /S /Q sdk\DLDMVideoServer\Win32\
RD /S /Q sdk\DongYang\Win32\
RD /S /Q sdk\HAIKVideoServer\Win32\
RD /S /Q sdk\HanBangVideoServer\Win32\
RD /S /Q sdk\HangJingVideoServer\Win32\
RD /S /Q sdk\JiuAnVideoServer\Win32\
RD /S /Q sdk\JunMingShiVideoServer\Win32\
RD /S /Q sdk\JXJVideoServer\Win32\
RD /S /Q sdk\TianDiWeiYe\Win32\
RD /S /Q sdk\TongWeiVideoServer\Win32\
RD /S /Q sdk\VideoDownloader\Win32\
RD /S /Q sdk\WoShiDaVideoServer\Win32\
RD /S /Q sdk\XingWangVideoServer\Win32\
RD /S /Q sdk\YyShiKejiVideoServer\Win32\
RD /S /Q sdk\ZhongWeiVideoServer\Win32\

exit /b %ERRORLEVEL%
endlocal
pause