; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "VideoDownLoad"
;#define MyAppVersion "v2.0.8.1"
#define MyAppVersion "v1.3.5"
#define MyAppPublisher "龙脉安信"
#define MyAppURL "http://www.sisec.com.cn/"
#define MyAppExeName "FastVideo.exe"

[Setup]
; 注: AppId的值为单独标识该应用程序。
; 不要为其他安装程序使用相同的AppId值。
; (生成新的GUID，点击 工具|在IDE中生成GUID。)
AppId={{92156374-EE64-4A6B-9486-DEB0EFAD5FB3}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName=C:\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputBaseFilename=高速下载器{#MyAppVersion}
Compression=lzma
ShowLanguageDialog=no
SolidCompression=yes
UsePreviousUserInfo=no
UsePreviousAppDir=no 
UsePreviousGroup=no 
UsePreviousLanguage=no 
UsePreviousSetupType=no 
UsePreviousTasks=no 
DisableDirPage=yes 
DisableFinishedPage=no 
DisableProgramGroupPage=yes 
DisableReadyMemo=yes 
DisableReadyPage=yes 
DisableStartupPrompt=yes 
DisableWelcomePage=no 

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\work\downloadVideo\bin\*.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\fast_video.db"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\auto.bat"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\WinPcap_4_1_3.exe"; DestDir: "{app}"; Flags: ignoreversion  
Source: "D:\work\downloadVideo\bin\*.sys"; DestDir: "{app}"; Flags: ignoreversion

Source: "D:\work\downloadVideo\bin\CodeClient.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\CreateVolume_Client.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\download.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\FastVideo.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\MountVolume_Client.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\Start.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\StartSsd.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\VideoService.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\downloadVideo\bin\file\ipListAddress.txt"; DestDir: "{app}\file"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\work\downloadVideo\bin\log"; DestDir: "{app}\log"; Flags: ignoreversion recursesubdirs createallsubdirs 
Source: "D:\work\downloadVideo\bin\DaHuaTool\*"; DestDir: "{app}\DaHuaTool"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\work\downloadVideo\bin\factorys\*"; DestDir: "{app}\factorys"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\work\downloadVideo\bin\hikPlay\*"; DestDir: "{app}\hikPlay"; Flags: ignoreversion recursesubdirs createallsubdirs
;Source: "D:\work\downloadVideo\bin\image\*"; DestDir: "{app}\image"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\work\downloadVideo\bin\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\work\downloadVideo\bin\screenRecord\*"; DestDir: "{app}\screenRecord"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\work\downloadVideo\bin\sqldrivers\*"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\work\downloadVideo\bin\tool\*"; DestDir: "{app}\tool"; Flags: ignoreversion recursesubdirs createallsubdirs
; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{userdesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\WinPcap_4_1_3.exe"; Description: "抓包工具"; Flags: skipifsilent shellexec runhidden nowait postinstall
Filename: "{app}\auto.bat"; Description: "自动注册"; Flags: skipifsilent shellexec runhidden nowait postinstall
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent