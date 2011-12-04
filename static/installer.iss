[Setup]
AppName=RSys
AppVersion=1.0
DefaultDirName={pf}\RSys
DefaultGroupName=RSys
UninstallDisplayIcon={app}\RSys.exe
Compression=lzma2
SolidCompression=yes
OutputDir=.

[Files]
Source: "qt.conf";        DestDir: "{app}"
Source: "RSys.exe";       DestDir: "{app}"

Source: "kdchart.dll";    DestDir: "{app}"
Source: "QtCore4.dll";    DestDir: "{app}"
Source: "QtGui4.dll";     DestDir: "{app}"
Source: "QtSql4.dll";     DestDir: "{app}"
Source: "QtSvg4.dll";     DestDir: "{app}"
Source: "QtTest4.dll";    DestDir: "{app}"

Source: "libeay32.dll";   DestDir: "{app}"
Source: "libiconv-2.dll"; DestDir: "{app}"
Source: "libintl-8.dll";  DestDir: "{app}"
Source: "libpq.dll";      DestDir: "{app}"
Source: "ssleay32.dll";   DestDir: "{app}"


Source: "plugins\sqldrivers\qsqlite4.dll";  DestDir: "{app}\plugins\sqldrivers"
Source: "plugins\sqldrivers\qsqlpsql4.dll"; DestDir: "{app}\plugins\sqldrivers"

[Icons]
Name: "{group}\RSys"; Filename: "{app}\RSys.exe"; WorkingDir: "{app}"
Name: "{group}\Pašalinti RSys"; Filename: "{uninstallexe}"
Name: "{commondesktop}\RSys"; Filename: "{app}\RSys.exe"; WorkingDir: "{app}"; Tasks: desktopicon

[LangOptions]
LanguageName=Lithuanian

[Run]
Filename: "{app}\RSys.exe"; Description: "Paleisti RSys"; Flags: postinstall nowait

[Tasks]
Name: desktopicon; Description: "Sukurti darbalaukio piktogramą"; GroupDescription: "Additional icons:"

;Name: quicklaunchicon; Description: "Create a &Quick Launch icon"; GroupDescription: "Additional icons:"; Flags: unchecked
