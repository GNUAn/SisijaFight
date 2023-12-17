; SisijaFight Installer Script

!include "MUI2.nsh"

; Basic information
Name "SisijaFight"
OutFile "SisijaFightInstaller.exe"
InstallDir "$PROGRAMFILES\SisijaFight2"
ShowInstDetails show
ShowUnInstDetails show

; Pages
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Languages
!insertmacro MUI_LANGUAGE "English"

Section "Install SisijaFight" SecInstall
    SetOutPath $INSTDIR
    File "Sisija.zip"
    ; Assuming Sisija.zip contains SisijaFight.exe
    ; Extract Sisija.zip here
    nsisunz::Unzip "$INSTDIR\Sisija.zip" "$INSTDIR"
    Delete "$INSTDIR\Sisija.zip"
    ; Create a shortcut in the Start Menu
    CreateDirectory "$SMPROGRAMS\SisijaFight"
    CreateShortCut "$SMPROGRAMS\SisijaFight\SisijaFight.lnk" "$INSTDIR\SisijaFight.exe"
    ; Register the program (optional, adjust as needed)
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SisijaFight" "DisplayName" "SisijaFight"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SisijaFight" "UninstallString" '"$INSTDIR\Uninstall.exe"'
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\SisijaFight.exe"
    Delete "$SMPROGRAMS\SisijaFight\SisijaFight.lnk"
    RMDir "$SMPROGRAMS\SisijaFight"
    RMDir /r "$INSTDIR"
    ; Remove the registry entry
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SisijaFight"
SectionEnd
