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
Source: "kdchart.dll";  DestDir: "{app}"
Source: "QtCore4.dll";  DestDir: "{app}"
Source: "QtGui4.dll";   DestDir: "{app}"
Source: "QtSql4.dll";   DestDir: "{app}"
Source: "QtSvg4.dll";   DestDir: "{app}"
Source: "QtTest4.dll";  DestDir: "{app}"
Source: "RSys.exe";     DestDir: "{app}"
Source: "plugins\sqldrivers\qsqlite4.dll";  DestDir: "{app}\plugins\sqldrivers"
Source: "plugins\sqldrivers\qsqlpsql4.dll"; DestDir: "{app}\plugins\sqldrivers"

[Icons]
Name: "{group}\RSys"; Filename: "{app}\RSys.exe"
