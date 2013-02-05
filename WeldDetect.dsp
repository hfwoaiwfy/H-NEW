# Microsoft Developer Studio Project File - Name="WeldDetect" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WeldDetect - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WeldDetect.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WeldDetect.mak" CFG="WeldDetect - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WeldDetect - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WeldDetect - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WeldDetect - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ../../lib/Image.lib ../../lib/Amcl.lib cxcore.lib cv.lib ml.lib cvaux.lib highgui.lib cvcam.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "WeldDetect - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /I "..\..\include" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /i "..\..\include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ../../lib/Image.lib ../../lib/Amcl.lib cxcore.lib cv.lib ml.lib cvaux.lib highgui.lib cvcam.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/º¸·ì¸ú×Ù.exe" /pdbtype:sept /libpath:"..\..\lib"
# Begin Custom Build
OutDir=.\Debug
TargetName=º¸·ì¸ú×Ù
InputPath=.\Debug\º¸·ì¸ú×Ù.exe
SOURCE="$(InputPath)"

"$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(OutDir)\$(TargetName).exe ..\..\bin

# End Custom Build

!ENDIF 

# Begin Target

# Name "WeldDetect - Win32 Release"
# Name "WeldDetect - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CalibrationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\new\CDialogSK.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomButton.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PasswordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\new\SplashDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WeldDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\WeldDetect.rc
# End Source File
# Begin Source File

SOURCE=.\WeldDetectDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CalibrationDlg.h
# End Source File
# Begin Source File

SOURCE=.\new\CDialogSK.h
# End Source File
# Begin Source File

SOURCE=.\CommonFunction.h
# End Source File
# Begin Source File

SOURCE=.\CustomButton.h
# End Source File
# Begin Source File

SOURCE=.\HistoryDlg.h
# End Source File
# Begin Source File

SOURCE=..\motion\motion.h
# End Source File
# Begin Source File

SOURCE=.\ParameterDlg.h
# End Source File
# Begin Source File

SOURCE=.\PasswordDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\new\SplashDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WeldDetect.h
# End Source File
# Begin Source File

SOURCE=.\WeldDetectDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ACER.ICO
# End Source File
# Begin Source File

SOURCE=.\res\bitmap.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\WeldDetect.ico
# End Source File
# Begin Source File

SOURCE=.\res\WeldDetect.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
