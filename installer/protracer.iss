#define APPNAME="protracer"
#define APPVERS="1"
#define LOGO="logo-trans.png"

[Setup]
AppId={{8EA21DB7-BAD9-4BEC-AC14-289D2B6523A4}
AppName={#APPNAME}
AppVersion={#APPVERS}
AppVerName={#APPNAME} {#APPVERS}
OutputBaseFileName={#APPNAME}-{#APPVERS}-setup
DefaultDirName={pf}\{#APPNAME} {#APPVERS}
DefaultGroupName={#APPNAME}
;PrivilegesRequired=admin
AppCopyright=Copyright © 2008 - 2011 Marcus Lundblad
AppPublisher=Marcus Lundblad
AppPublisherURL=https://github.com/mlundblad/protracer
OutputDir=.
LicenseFile=..\LICENCE
RestartIfNeededByRun=false
UsePreviousUserInfo=false
ChangesAssociations=true
WizardImageFile=installer-image.bmp
Compression=lzma/ultra
SolidCompression=yes
;AlwaysRestart=yes

[Languages]
Name: english; MessagesFile: compiler:Default.isl
Name: Italiano; MessagesFile: compiler:Italian-14-5.1.11.isl
Name: Danish; MessagesFile: compiler:Danish-4-5.1.11.isl
Name: Basque; MessagesFile: compiler:Basque-1-5.1.11.isl
Name: Catalan; MessagesFile: compiler:Catalan-4-5.1.11.isl
Name: Czech; MessagesFile: compiler:Czech-5-5.1.11.isl
Name: Dutch; MessagesFile: compiler:Dutch-8-5.1.11.isl
Name: Finnish; MessagesFile: compiler:Finnish-5.1.11.isl
Name: French; MessagesFile: compiler:French-15-5.1.11.isl
Name: German; MessagesFile: compiler:German-2-5.1.11.isl
Name: Hebrew; MessagesFile: compiler:Hebrew-3-5.1.11.isl
Name: Hungarian; MessagesFile: compiler:Hungarian-5.1.11.isl
Name: Norwegian; MessagesFile: compiler:Norwegian-5.1.11.isl
Name: Polish; MessagesFile: compiler:Polish-8-5.1.11.isl
Name: PortugueseBrazilian; MessagesFile: compiler:BrazilianPortuguese-16-5.1.11.isl
Name: PortugueseStandard; MessagesFile: compiler:PortugueseStd-1-5.1.11.isl
Name: Russian; MessagesFile: compiler:Russian-19-5.1.11.isl
Name: Slovak; MessagesFile: compiler:Slovak-6-5.1.11.isl
Name: Slovenian; MessagesFile: compiler:Slovenian-3-5.1.11.isl
Name: SpanishStandard; MessagesFile: compiler:SpanishStd-5-5.1.11.isl
Name: NorwegianNynorsk; MessagesFile: compiler:NorwegianNynorsk-1-4.0.5.isl
Name: Greek; MessagesFile: compiler:Greek-4-5.1.11.isl
Name: Afrikaans; MessagesFile: compiler:Afrikaans-1-5.1.11.isl
Name: Albanian; MessagesFile: compiler:Albanian-2-5.1.11.isl
Name: Arabic; MessagesFile: compiler:Arabic-4-5.1.11.isl
Name: Belarus; MessagesFile: compiler:Belarus-5.1.11.isl
Name: Lithuanian; MessagesFile: compiler:Lithuanian-4-5.1.11.isl
Name: Valencian; MessagesFile: compiler:Valencian-1-5.1.11.isl
Name: Ukrainian; MessagesFile: compiler:Ukrainian-6-5.1.11.isl
Name: Turkish; MessagesFile: compiler:Turkish-3-5.1.11.isl
Name: Serbian; MessagesFile: compiler:Serbian-5-5.1.11.isl
Name: Romanian; MessagesFile: compiler:Romanian-6-5.1.11.isl
Name: Latvian; MessagesFile: compiler:Latvian-1-5.1.11.isl
Name: Icelandic; MessagesFile: compiler:Icelandic-1-5.1.11.isl
Name: Galician; MessagesFile: compiler:Galician-2-5.1.11.isl
Name: Estonian; MessagesFile: compiler:Estonian-2-5.1.0.isl
Name: Swedish; MessagesFile: compiler:Swedish-10-5.1.12.isl
Name: Bosnian; MessagesFile: compiler:Bosnian-1-5.1.0.isl
Name: Bulgarian; MessagesFile: compiler:Bulgarian-5.1.11.isl
Name: ChineseSimplified; MessagesFile: compiler:ChineseSimp-12-5.1.11.isl
Name: ChineseTraditional; MessagesFile: compiler:ChineseTrad-2-5.1.11.isl
Name: Croatian; MessagesFile: compiler:Croatian-5-5.1.11.isl
Name: Esperanto; MessagesFile: compiler:Esperanto-1-5.1.11.isl
Name: Farsi; MessagesFile: compiler:Farsi-1-5.1.0.isl
Name: Indonesian; MessagesFile: compiler:Indonesian-5.1.11.isl
Name: Japanese; MessagesFile: compiler:Japanese-5-5.1.11.isl
Name: Korean; MessagesFile: compiler:Korean-5-5.1.11.isl
Name: Macedonian; MessagesFile: compiler:Macedonian-2-5.1.11.isl
Name: Luxemburgish; MessagesFile: compiler:Luxemburgish-1-5.1.11.isl
Name: Malay; MessagesFile: compiler:Malaysian-2-5.1.0.isl

[Files]
Source: website.url; DestDir: {app}
Source: ..\ChangeLog.txt; DestDir: {app}
Source: ..\src\{#APPNAME}.exe; DestDir: {app}; Flags: ignoreversion

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked
Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked

[Icons]
Name: {group}\{#APPNAME}; Filename: {app}\{#APPNAME}.exe; IconFilename: {app}\icon.ico; IconIndex: 0; WorkingDir: {app}\
Name: {group}\{cm:VisitHomepage}; Filename: {app}\website.url; IconFilename: {app}\icon.ico; IconIndex: 0
Name: {group}\{cm:UninstallProgram,{#APPNAME}}; Filename: {uninstallexe}; IconFilename: {app}\icon.ico; IconIndex: 0; WorkingDir: {app}\
Name: {commondesktop}\{#APPNAME} {#APPVERS}; Filename: {app}\{#APPNAME}.exe; Tasks: desktopicon; IconFilename: {app}\icon.ico; IconIndex: 0; WorkingDir: {app}\

[Run]
Filename: {app}\{#APPNAME}.exe; Description: {cm:LaunchProgram,{#APPNAME}}; Flags: nowait postinstall skipifsilent unchecked

[CustomMessages]
VisitHomepage=Visit the Homepage
