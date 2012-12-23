;/******************************************************\
;*	Othello-GL : b3.00				*
;*	Copyright (c) 2003, G-Truc Creation, Code GBA.	*
;********************************************************
;*	G-Truc Creation, www.g-truc.fr.st		*
;*	Code GBA, www.codegba.fr.st			*
;********************************************************
;*	Ce programme est un programme libre, vous	*
;*	pouvez	le distribuer et/ou le modifier suivant	*
;*	les termes de la GNU General Public Licence.	*
;********************************************************
;*	othello-gl.nsi, 02/04/2003			*
;*	par Groove, groove@g-truc.fr.st			*
;\******************************************************/

!define MUI_PRODUCT "Othello GL"
!define MUI_VERSION "Beta 3.00"

!include "MUI.nsh"

;--------------------------------
;Configuration

	OutFile "othello-gl-b3.00.exe"
	SetCompressor bzip2

	InstType "Full (Othello-GL + Manual + Source)"
	InstType "Normal (Othello-GL + Manual)"
	InstType "Lite (Othello-GL only)"

	ShowInstDetails show
	ShowUninstDetails show
	SetDateSave on

	InstallDir "$PROGRAMFILES\${MUI_PRODUCT}"
	InstallDirRegKey HKCU "Software\${MUI_PRODUCT}" ""

	!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
	!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\${MUI_PRODUCT}" 
	!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"

	!define TEMP $R0

;--------------------------------
;Modern UI Configuration

	!define MUI_NAME "Othello GL"
	!define MUI_ICON "othello-gl.ico"
	!define MUI_UNICON "othello-gl.ico"
;	!define MUI_CHECKBITMAP "othello_gl.bmp"
;	!define MUI_FONT "Verdana"
;	!define MUI_FONTSIZE "8"
;	!define MUI_FONT_HEADER "Courrier new"
;	!define MUI_FONTSIZE_HEADER "12"
;	!define MUI_FONTSTYLE_TITLE 10 "/UNDERLINE" "/STRIKE"
;	!define MUI_INSTALLCOLORS "00FF00" "FF0000"
	!define MUI_HEADERBITMAP "header.bmp"
;		!define MUI_HEADERBITMAP_RIGHT
	!define MUI_SPECIALBITMAP "othello_gl.bmp"
	!define MUI_BGCOLOR "0xFFFFFF"

	!define MUI_WELCOMEPAGE
	!define MUI_LICENSE_PAGE
	!define MUI_COMPONENTSPAGE
		!define MUI_COMPONENTSPAGE_SMALLDESC
 	!define MUI_DIRECTORYPAGE
	!define MUI_STARTMENUPAGE
	!define MUI_FINISHPAGE
		!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\doc\readme.txt"
		!define MUI_FINISHPAGE_NOREBOOTSUPPORT
	!define MUI_ABORTWARNING

	!define MUI_UNINSTALLER
	!define MUI_UNCONFIRMPAGE
  
;--------------------------------
;Languages

	!define MUI_TEXT_WELCOME_INFO_TEXT "This wizard will guide you through the installation of ${MUI_PRODUCT}, an OpenGL Othello game for 1 or 2 players.\r\n\r\n\r\n"
	
	!insertmacro MUI_LANGUAGE "English"
	!insertmacro MUI_LANGUAGE "French"
	!insertmacro MUI_LANGUAGE "German"
	!insertmacro MUI_LANGUAGE "Spanish"

  
;--------------------------------
;Reserve Files

	!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
	!insertmacro MUI_RESERVEFILE_SPECIALINI
	!insertmacro MUI_RESERVEFILE_SPECIALBITMAP

;--------------------------------
;Language Strings

	LangString DESC_PROGRAM ${LANG_ENGLISH} "This must be check to use Othello GL."
	LangString DESC_PROGRAM ${LANG_FRENCH} "Ce groupe est necessaire si vous souhaitez jouer à Othello."
	LangString DESC_PROGRAM ${LANG_GERMAN} "This must be check to use Othello GL."
	LangString DESC_PROGRAM ${LANG_SPANISH} "This must be check to use Othello GL."

	LangString DESC_MANUAL ${LANG_ENGLISH} "Some informations about Othello GL"
	LangString DESC_MANUAL ${LANG_FRENCH} "Quelques informations sur le jeu."
	LangString DESC_MANUAL ${LANG_GERMAN} "Some informations about Othello GL"
	LangString DESC_MANUAL ${LANG_SPANISH} "Some informations about Othello GL"

	LangString DESC_CODE ${LANG_ENGLISH} "C++ Source code to GCC 2.95, GCC 3.2, VC6, VC7; UML conception and NSIS installer script."
	LangString DESC_CODE ${LANG_FRENCH} "Code C++ pour GCC 2.95, GCC 3.2, VC6, VC7; Conception UML, le script NSIS v2b3."
	LangString DESC_CODE ${LANG_GERMAN} "C++ Source code to GCC 2.95, GCC 3.2, VC6, VC7; UML conception and NSIS installer script."
	LangString DESC_CODE ${LANG_SPANISH} "C++ Source code to GCC 2.95, GCC 3.2, VC6, VC7; UML conception and NSIS installer script."


	LangString DESC_README ${LANG_ENGLISH} "$INSTDIR\doc\readme.txt"
	LangString DESC_README ${LANG_FRENCH} "$INSTDIR\doc\lisezmoi.txt"
	LangString DESC_README ${LANG_GERMAN} "$INSTDIR\doc\readme.txt"
	LangString DESC_README ${LANG_SPANISH} "$INSTDIR\doc\readme.txt"

;--------------------------------
;Data
  
;	LicenseData License.txt

;--------------------------------
;Installer Sections

Section "Othello" Program
SectionIn 1 2 3 RO
	SetOutPath $INSTDIR
	File file\*.exe
	File file\*.ico
	File file\*.dll
	SetOutPath $INSTDIR\data
	File file\data\*.*

	StrCmp $LANGUAGE ${LANG_ENGLISH} 0 +2
	File traduc\en\text.txt
	StrCmp $LANGUAGE ${LANG_FRENCH} 0 +2
	File traduc\fr\text.txt
	StrCmp $LANGUAGE ${LANG_GERMAN} 0 +2
	File traduc\sp\text.txt
	StrCmp $LANGUAGE ${LANG_SPANISH} 0 +2
	File traduc\de\text.txt

	SetOutPath $INSTDIR\doc
	File file\doc\*.*
	SetOutPath $INSTDIR\font
	File file\font\*.*
	SetOutPath $INSTDIR\image
	File file\image\*.*
	WriteUninstaller "$INSTDIR\Uninstall.exe"
	
	WriteRegStr HKCU "Software\${MUI_PRODUCT}" "" $INSTDIR

	!insertmacro MUI_STARTMENU_WRITE_BEGIN
		SetOutPath $INSTDIR
			CreateDirectory "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}"
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Othello-GL-window.lnk" "$INSTDIR\othello-gl.exe" "-0" "$INSTDIR\othello-gl.ico" 0
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Othello-GL-0640.lnk" "$INSTDIR\othello-gl.exe" "-1" "$INSTDIR\othello-gl.ico" 0
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Othello-GL-0800.lnk" "$INSTDIR\othello-gl.exe" "-2" "$INSTDIR\othello-gl.ico" 0
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Othello-GL-1024.lnk" "$INSTDIR\othello-gl.exe" "-3" "$INSTDIR\othello-gl.ico" 0
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Othello-GL-1280.lnk" "$INSTDIR\othello-gl.exe" "-4" "$INSTDIR\othello-gl.ico" 0
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Othello-GL-1600.lnk" "$INSTDIR\othello-gl.exe" "-5" "$INSTDIR\othello-gl.ico" 0
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Uninstall.lnk" "$INSTDIR\uninstall.exe"
		SetOutPath $INSTDIR\manuel
			CreateDirectory "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Documentation"
			StrCmp $LANGUAGE ${LANG_ENGLISH} 0 +2
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Documentation\readme.txt.lnk" "$INSTDIR\doc\readme.txt" "" "$INSTDIR\othello-gl.ico" 0
			StrCmp $LANGUAGE ${LANG_FRENCH} 0 +2
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Documentation\lisezmoi.txt.lnk" "$INSTDIR\doc\lisezmoi.txt" "" "$INSTDIR\othello-gl.ico" 0
			StrCmp $LANGUAGE ${LANG_GERMAN} 0 +2
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Documentation\readme.txt.lnk" "$INSTDIR\doc\readme.txt" "" "$INSTDIR\othello-gl.ico" 0
			StrCmp $LANGUAGE ${LANG_SPANISH} 0 +2
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Documentation\readme.txt.lnk" "$INSTDIR\doc\readme.txt" "" "$INSTDIR\othello-gl.ico" 0
			CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Documentation\manuel.lnk" "$INSTDIR\manuel\index.html" "" "$INSTDIR\othello-gl.ico" 0
			WriteINIStr "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Documentation\othello-gl.sourceforge.net.url" "InternetShortcut" "URL" "http://othello-gl.sourceforge.net/"
			WriteRegStr HKCU "Software\${MUI_PRODUCT}" "Start Menu Folder" "${MUI_STARTMENUPAGE_VARIABLE}"
	!insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section "Manuel" Manual
SectionIn 1 2
	StrCmp $LANGUAGE ${LANG_ENGLISH} 0 +1
	SetOutPath $INSTDIR\manuel
	File file\manual\*.*
	SetOutPath $INSTDIR\manuel\page
	File file\manual\page\*.*
	SetOutPath $INSTDIR\manuel\page\image
	File file\manual\page\image\*.*
	SetOutPath $INSTDIR\manuel\page\script
	File file\manual\page\script\*.*

	StrCmp $LANGUAGE ${LANG_FRENCH} 0 +1
	SetOutPath $INSTDIR\manuel
	File file\manuel\*.*
	SetOutPath $INSTDIR\manuel\page
	File file\manuel\page\*.*
	SetOutPath $INSTDIR\manuel\page\image
	File file\manuel\page\image\*.*
	SetOutPath $INSTDIR\manuel\page\script
	File file\manuel\page\script\*.*

	StrCmp $LANGUAGE ${LANG_GERMAN} 0 +1
	SetOutPath $INSTDIR\manuel
	File file\manual\*.*
	SetOutPath $INSTDIR\manuel\page
	File file\manual\page\*.*
	SetOutPath $INSTDIR\manuel\page\image
	File file\manual\page\image\*.*
	SetOutPath $INSTDIR\manuel\page\script
	File file\manual\page\script\*.*

	StrCmp $LANGUAGE ${LANG_SPANISH} 0 +1
	SetOutPath $INSTDIR\manuel
	File file\manual\*.*
	SetOutPath $INSTDIR\manuel\page
	File file\manual\page\*.*
	SetOutPath $INSTDIR\manuel\page\image
	File file\manual\page\image\*.*
	SetOutPath $INSTDIR\manuel\page\script
	File file\manual\page\script\*.*

SectionEnd

Section "Source" Code
SectionIn 1
	SetOutPath $INSTDIR\source\conception
	File file\source\conception\*.*
	SetOutPath $INSTDIR\source\conception\class
	File file\source\conception\class\*.*
	SetOutPath $INSTDIR\source\conception\sequence
	File file\source\conception\sequence\*.*
	SetOutPath $INSTDIR\source\conception\appel
	File file\source\conception\appel\*.*

	SetOutPath $INSTDIR\source\installer
	File file\source\installer\*.*

	SetOutPath $INSTDIR\source\code\file_gcc
	File file\source\code\file_gcc\*.*
	SetOutPath $INSTDIR\source\code\file_gcc\obj
	File file\source\code\file_gcc\obj\*.*
	SetOutPath $INSTDIR\source\code\file_vc6
	File file\source\code\file_vc6\*.*
	SetOutPath $INSTDIR\source\code\file_vc6\icon
	File file\source\code\file_vc6\icon\*.*
	SetOutPath $INSTDIR\source\code\file_vc7
	File file\source\code\file_vc7\*.*
	SetOutPath $INSTDIR\source\code\file_vc7\icon
	File file\source\code\file_vc7\icon\*.*
	SetOutPath $INSTDIR\source\code\header
	File file\source\code\header\*.*
	SetOutPath $INSTDIR\source\code\source
	File file\source\code\source\*.*
	SetOutPath $INSTDIR\source\installer
	File file\source\installer\*.*
	;Source de GTL
	SetOutPath $INSTDIR\source\code\gtl\data
	File file\source\code\gtl\data\*.*
	SetOutPath $INSTDIR\source\code\gtl\doc
	File file\source\code\gtl\doc\*.*
	SetOutPath $INSTDIR\source\code\gtl\include
	File file\source\code\gtl\include\*.*
	SetOutPath $INSTDIR\source\code\gtl\lib
	File file\source\code\gtl\lib\*.*
	SetOutPath $INSTDIR\source\code\gtl\projet\gcc3.2
	File file\source\code\gtl\projet\gcc3.2\*.*
	SetOutPath $INSTDIR\source\code\gtl\projet\vc6
	File file\source\code\gtl\projet\vc6\*.*
	SetOutPath $INSTDIR\source\code\gtl\projet\vc7
	File file\source\code\gtl\projet\vc7\*.*
	SetOutPath $INSTDIR\source\code\gtl\src
	File file\source\code\gtl\src\*.*
	SetOutPath $INSTDIR\source\code\gtl\test\gtl_font
	File file\source\code\gtl\test\gtl_font\*.*
	SetOutPath $INSTDIR\source\code\gtl\test\gtl_font\obj
	SetOutPath $INSTDIR\source\code\gtl\test\gtl_image
	File file\source\code\gtl\test\gtl_image\*.*
	SetOutPath $INSTDIR\source\code\gtl\test\gtl_image\obj
	SetOutPath $INSTDIR\source\code\gtl\test\gtl_rand
	File file\source\code\gtl\test\gtl_rand\*.*
	SetOutPath $INSTDIR\source\code\gtl\test\gtl_rand\obj
	SetOutPath $INSTDIR\source\code\gtl\test\gtl_vector
	File file\source\code\gtl\test\gtl_vector\*.*
	SetOutPath $INSTDIR\source\code\gtl\test\gtl_vector\obj
SectionEnd

	!insertmacro MUI_SECTIONS_FINISHHEADER

;--------------------------------
;Functions

Function .onInit

	!insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd

;--------------------------------
;Descriptions

	!insertmacro MUI_FUNCTIONS_DESCRIPTION_BEGIN
		!insertmacro MUI_DESCRIPTION_TEXT ${Program} $(DESC_PROGRAM)
		!insertmacro MUI_DESCRIPTION_TEXT ${Manual} $(DESC_MANUAL)
		!insertmacro MUI_DESCRIPTION_TEXT ${Code} $(DESC_CODE)
	!insertmacro MUI_FUNCTIONS_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section "Uninstall"
  Delete "$INSTDIR\data\*.*"
  RMDir "$INSTDIR\data"
  Delete "$INSTDIR\doc\*.*"
  RMDir "$INSTDIR\doc"
  Delete "$INSTDIR\font\*.*"
  RMDir "$INSTDIR\font"
  Delete "$INSTDIR\image\*.*"
  RMDir "$INSTDIR\image"
  Delete "$INSTDIR\manuel\page\image\*.*"
  RMDir "$INSTDIR\manuel\page\image"
  Delete "$INSTDIR\manuel\page\script\*.*"
  RMDir "$INSTDIR\manuel\page\script"
  Delete "$INSTDIR\manuel\page\*.*"
  RMDir "$INSTDIR\manuel\page"
  Delete "$INSTDIR\manuel\*.*"
  RMDir "$INSTDIR\manuel"

  Delete "$INSTDIR\source\code\file_gcc\obj\*.*"
  RMDir "$INSTDIR\source\code\file_gcc\obj"
  Delete "$INSTDIR\source\code\file_gcc\*.*"
  RMDir "$INSTDIR\source\code\file_gcc"
  Delete "$INSTDIR\source\code\file_vc6\icon\*.*"
  RMDir "$INSTDIR\source\code\file_vc6\icon"
  Delete "$INSTDIR\source\code\file_vc6\*.*"
  RMDir "$INSTDIR\source\code\file_vc6"
  Delete "$INSTDIR\source\code\file_vc7\icon\*.*"
  RMDir "$INSTDIR\source\code\file_vc7\icon"
  Delete "$INSTDIR\source\code\file_vc7\*.*"
  RMDir "$INSTDIR\source\code\file_vc7"
  Delete "$INSTDIR\source\code\gtl\data\*.*"
  RMDir "$INSTDIR\source\code\gtl\data"
  Delete "$INSTDIR\source\code\gtl\doc\*.*"
  RMDir "$INSTDIR\source\code\gtl\doc"
  Delete "$INSTDIR\source\code\gtl\include\*.*"
  RMDir "$INSTDIR\source\code\gtl\include"
  Delete "$INSTDIR\source\code\gtl\lib\*.*"
  RMDir "$INSTDIR\source\code\gtl\lib"
  Delete "$INSTDIR\source\code\gtl\projet\gcc3.2\*.*"
  RMDir "$INSTDIR\source\code\gtl\projet\gcc3.2"
  Delete "$INSTDIR\source\code\gtl\projet\vc6\*.*"
  RMDir "$INSTDIR\source\code\gtl\projet\vc6"
  Delete "$INSTDIR\source\code\gtl\projet\vc7\*.*"
  RMDir "$INSTDIR\source\code\gtl\projet\vc7"
  RMDir "$INSTDIR\source\code\gtl\projet"
  Delete "$INSTDIR\source\code\gtl\src\*.*"
  RMDir "$INSTDIR\source\code\gtl\src"
  Delete "$INSTDIR\source\code\gtl\test\gtl_font\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_font"
  Delete "$INSTDIR\source\code\gtl\test\gtl_font\obj\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_font\obj"
  Delete "$INSTDIR\source\code\gtl\test\gtl_font\release\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_font\release"
  Delete "$INSTDIR\source\code\gtl\test\gtl_font\debug\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_font\debug"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_font"
  Delete "$INSTDIR\source\code\gtl\test\gtl_image\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_image"
  Delete "$INSTDIR\source\code\gtl\test\gtl_image\obj\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_image\obj"
  Delete "$INSTDIR\source\code\gtl\test\gtl_image\release\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_image\release"
  Delete "$INSTDIR\source\code\gtl\test\gtl_image\debug\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_image\debug"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_image"
  Delete "$INSTDIR\source\code\gtl\test\gtl_rand\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_rand"
  Delete "$INSTDIR\source\code\gtl\test\gtl_rand\obj\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_rand\obj"
  Delete "$INSTDIR\source\code\gtl\test\gtl_rand\release\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_rand\release"
  Delete "$INSTDIR\source\code\gtl\test\gtl_rand\debug\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_rand\debug"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_rand"
  Delete "$INSTDIR\source\code\gtl\test\gtl_vector\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_vector"
  Delete "$INSTDIR\source\code\gtl\test\gtl_vector\obj\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_vector\obj"
  Delete "$INSTDIR\source\code\gtl\test\gtl_vector\release\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_vector\release"
  Delete "$INSTDIR\source\code\gtl\test\gtl_vector\debug\*.*"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_vector\debug"
  RMDir "$INSTDIR\source\code\gtl\test\gtl_vector"
  RMDir "$INSTDIR\source\code\gtl\test"
  RMDir "$INSTDIR\source\code\gtl"
  Delete "$INSTDIR\source\code\header\*.*"
  RMDir "$INSTDIR\source\code\header"
  Delete "$INSTDIR\source\code\source\*.*"
  RMDir "$INSTDIR\source\code\source"
  RMDir "$INSTDIR\source\code"
  Delete "$INSTDIR\source\conception\class\*.*"
  RMDir "$INSTDIR\source\conception\class"
  Delete "$INSTDIR\source\conception\sequence\*.*"
  RMDir "$INSTDIR\source\conception\sequence"
  Delete "$INSTDIR\source\conception\appel\*.*"
  RMDir "$INSTDIR\source\conception\appel"
  Delete "$INSTDIR\source\conception\*.*"
  RMDir "$INSTDIR\source\conception"
  Delete "$INSTDIR\source\installer\*.*"
  RMDir "$INSTDIR\source\installer"
  RMDir "$INSTDIR\source"

  Delete "$INSTDIR\*.*"
  RMDir "$INSTDIR"

	ReadRegStr ${TEMP} "${MUI_STARTMENUPAGE_REGISTRY_ROOT}" "${MUI_STARTMENUPAGE_REGISTRY_KEY}" "${MUI_STARTMENUPAGE_REGISTRY_VALUENAME}"
  
	StrCmp ${TEMP} "" noshortcuts
  
	Delete "$SMPROGRAMS\${TEMP}\Documentation\*.*"
	RMDir "$SMPROGRAMS\${TEMP}\Documentation"

	Delete "$SMPROGRAMS\${TEMP}\*.*"
	RMDir "$SMPROGRAMS\${TEMP}"
    
	noshortcuts:

	RMDir "$INSTDIR"

	DeleteRegKey /ifempty HKCU "Software\${MUI_PRODUCT}"

	!insertmacro MUI_UNFINISHHEADER

SectionEnd


