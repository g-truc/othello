# Microsoft Developer Studio Project File - Name="gtl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gtl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gtl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gtl.mak" CFG="gtl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gtl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gtl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gtl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /G6 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/gtl_vc6.lib"

!ELSEIF  "$(CFG)" == "gtl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/gtl_vc6.lib"

!ENDIF 

# Begin Target

# Name "gtl - Win32 Release"
# Name "gtl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\gtl_color.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_image_bmp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_image_raw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_image_tga.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\gtl_math.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\gl.h
# End Source File
# Begin Source File

SOURCE=..\..\include\glext.h
# End Source File
# Begin Source File

SOURCE=..\..\include\glu.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_angle2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_angle3.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_color.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_def.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_dll.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_font.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_image.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_image_bmp.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_image_raw.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_image_tga.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_math.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_mem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_rand.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_vector.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_vector2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gtl_vector3.h
# End Source File
# End Group
# End Target
# End Project
