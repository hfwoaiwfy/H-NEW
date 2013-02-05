; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWeldDetectDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "welddetect.h"
LastPage=0

ClassCount=8
Class1=CCalibrationDlg
Class2=CCustomButton
Class3=CHistoryDlg
Class4=CParameterDlg
Class5=CPasswordDlg
Class6=CWeldDetectApp
Class7=CAboutDlg
Class8=CWeldDetectDlg

ResourceCount=8
Resource1=IDD_DIALOG_CALIBRATION
Resource2=IDD_DIALOG_PARAMETER
Resource3=IDD_DIALOG_HISTORY
Resource4=IDD_SPLASH
Resource5=IDD_DIALOG_LOGIN
Resource6=IDD_WELDDETECT_DIALOG
Resource7=IDD_ABOUTBOX
Resource8=IDR_MENU1

[CLS:CCalibrationDlg]
Type=0
BaseClass=CDialog
HeaderFile=CalibrationDlg.h
ImplementationFile=CalibrationDlg.cpp

[CLS:CCustomButton]
Type=0
BaseClass=CButton
HeaderFile=CustomButton.h
ImplementationFile=CustomButton.cpp

[CLS:CHistoryDlg]
Type=0
BaseClass=CDialog
HeaderFile=HistoryDlg.h
ImplementationFile=HistoryDlg.cpp

[CLS:CParameterDlg]
Type=0
BaseClass=CDialog
HeaderFile=ParameterDlg.h
ImplementationFile=ParameterDlg.cpp

[CLS:CPasswordDlg]
Type=0
BaseClass=CDialog
HeaderFile=PasswordDlg.h
ImplementationFile=PasswordDlg.cpp

[CLS:CWeldDetectApp]
Type=0
BaseClass=CWinApp
HeaderFile=WeldDetect.h
ImplementationFile=WeldDetect.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=WeldDetectDlg.cpp
ImplementationFile=WeldDetectDlg.cpp

[CLS:CWeldDetectDlg]
Type=0
BaseClass=CDialog
HeaderFile=WeldDetectDlg.h
ImplementationFile=WeldDetectDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_INFO

[DLG:IDD_DIALOG_CALIBRATION]
Type=1
Class=CCalibrationDlg
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDOK1,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_BUTTON_RECALI,button,1342242816
Control13=IDC_BUTTON_CALIBRATION,button,1342242816
Control14=IDC_STATIC_STARTX,edit,1350633600
Control15=IDC_STATIC_ENDX,edit,1350633600
Control16=IDC_STATIC_STARTY,edit,1350633600
Control17=IDC_STATIC_ENDY,edit,1350633600
Control18=IDC_STATIC_XRESOLUTION,edit,1350633600
Control19=IDC_STATIC_YRESOLUTION,edit,1350633600
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_HISTORY]
Type=1
Class=CHistoryDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_PARAMETER]
Type=1
Class=CParameterDlg
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_SCORE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_ROI_X,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_ROI_Y,edit,1350631552
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_LOGIN]
Type=1
Class=CPasswordDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_PASSWORD,edit,1350631584

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WELDDETECT_DIALOG]
Type=1
Class=CWeldDetectDlg
ControlCount=34
Control1=IDC_BUTTON_STOP,button,1342242816
Control2=IDC_BUTTON_RIGHT,button,1342242816
Control3=IDC_STATIC_CONTINUEGRAB,static,1342181383
Control4=IDC_STATIC_TEMPIMAGE,static,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_BUTTON_TEMP,button,1342242816
Control7=IDC_BUTTON_START,button,1342242816
Control8=IDC_BUTTON_END,button,1342242816
Control9=IDC_BUTTON_UP,button,1342242816
Control10=IDC_BUTTON_LEFT,button,1342242816
Control11=IDC_BUTTON_DOWN,button,1342242816
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC_OFFSETX,static,1342312448
Control16=IDC_STATIC_OFFSETY,static,1342312448
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC_SCORE,static,1342312448
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC_TIME,static,1342312448
Control23=IDC_STATIC,static,1342308352
Control24=IDC_CHECK_KEY,button,1342259203
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_EDIT_TEMPX,edit,1350633600
Control30=IDC_EDIT_TEMPY,edit,1350633600
Control31=IDC_EDIT_NOWX,edit,1350633600
Control32=IDC_EDIT_NOWY,edit,1350633600
Control33=IDC_CHECK_G,button,1342259203
Control34=IDC_INFO,static,1342312448

[DLG:IDD_SPLASH]
Type=1
Class=?
ControlCount=0

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENUITEM_CALIBRATION
Command2=ID_MENUITEM_PARAMETER
Command3=ID_MENUITEM_HISTORY
Command4=ID_MENUITEM_EXIT
CommandCount=4

