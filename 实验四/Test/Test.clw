; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInputRectDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Test.h"
LastPage=0

ClassCount=6
Class1=CTestApp
Class2=CTestDoc
Class3=CTestView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=CInputRectDialog
Resource3=IDD_DIALOG_INPUT_RECT

[CLS:CTestApp]
Type=0
HeaderFile=Test.h
ImplementationFile=Test.cpp
Filter=N

[CLS:CTestDoc]
Type=0
HeaderFile=TestDoc.h
ImplementationFile=TestDoc.cpp
Filter=N

[CLS:CTestView]
Type=0
HeaderFile=TestView.h
ImplementationFile=TestView.cpp
Filter=C
LastObject=CTestView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Test.cpp
ImplementationFile=Test.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=IDM_DRAWPIC
Command3=IDM_LEFT
Command4=IDM_RIGHT
Command5=IDM_UP
Command6=IDM_DOWN
Command7=IDM_ZOOMIN
Command8=IDM_ZOOMOUT
Command9=IDM_CLOCKWISE
Command10=IDM_ANTICLOCKWISE
Command11=IDM_REFLECTX
Command12=IDM_REFLECTY
Command13=IDM_REFLECTORIGIN
Command14=IDM_SHEARXPOS
Command15=IDM_SHEARXNEG
Command16=IDM_SHEARYPOS
Command17=IDM_SHEARYNEG
Command18=IDM_RESTORE
Command19=ID_APP_ABOUT
CommandCount=19

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=IDM_DRAWPIC
Command3=IDM_LEFT
Command4=IDM_RIGHT
Command5=IDM_UP
Command6=IDM_DOWN
Command7=IDM_ZOOMIN
Command8=IDM_ZOOMOUT
Command9=IDM_ANTICLOCKWISE
Command10=IDM_CLOCKWISE
Command11=IDM_REFLECTX
Command12=IDM_REFLECTY
Command13=IDM_REFLECTORIGIN
Command14=IDM_SHEARXPOS
Command15=IDM_SHEARXNEG
Command16=IDM_SHEARYPOS
Command17=IDM_SHEARYNEG
Command18=IDM_RESTORE
Command19=ID_APP_ABOUT
CommandCount=19

[DLG:IDD_DIALOG_INPUT_RECT]
Type=1
Class=CInputRectDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_WIDTH,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_HEIGHT,edit,1350631552

[CLS:CInputRectDialog]
Type=0
HeaderFile=InputRectDialog.h
ImplementationFile=InputRectDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_WIDTH

