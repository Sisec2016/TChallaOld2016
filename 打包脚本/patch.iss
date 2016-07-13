; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "VideoDownLoad"
#define MyAppVersion "v1.3.4.10.4(widescreen)"
#define MyAppPublisher "珠海经济特区远宏科技有限公司"
#define MyAppURL "http://www.rmax.com/"
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
OutputBaseFilename=patch_{#MyAppVersion}
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
Name: "en"; MessagesFile: "compiler:Default.isl"  
Name: "Chinese"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"  

[Files]   								                            
Source: "C:\VideoDownLoad\FastVideo.exe"; 		          DestDir: "{app}"; Flags: ignoreversion;    Excludes:"unins000.*"  
Source: "C:\VideoDownLoad\VideoService.exe"; 		          DestDir: "{app}"; Flags: ignoreversion;   Excludes:"unins000.*"
Source: "C:\VideoDownLoad\Start.exe"; 		          DestDir: "{app}"; Flags: ignoreversion;   Excludes:"unins000.*"
Source: "C:\VideoDownLoad\factorys\DH\*"; 		      DestDir: "{app}\factorys\DH"; 		Flags: ignoreversion recursesubdirs createallsubdirs;   Excludes:"*.lib;*.pdb"
Source: "C:\VideoDownLoad\factorys\JiaXJ\JXJVideoServer.dll"; 		      DestDir: "{app}\factorys\JiaXJ"; 		Flags: ignoreversion recursesubdirs createallsubdirs;   Excludes:"*.lib;*.pdb"
Source: "C:\VideoDownLoad\factorys\DiZhiPu\DiZhiPuVideoServer.dll"; 		      DestDir: "{app}\factorys\DiZhiPu"; 		Flags: ignoreversion recursesubdirs createallsubdirs;   Excludes:"*.lib;*.pdb"

; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Dirs]
Name: "{app}\log"; 	  Flags: uninsalwaysuninstall
Name: "{app}\file"; 	Flags: uninsalwaysuninstall
