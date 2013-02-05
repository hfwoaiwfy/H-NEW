#include "StdAfx.h"
#include "WeldDetect.h"
#include "WeldDetectDlg.h"

#include "..\..\include\motion.h"
#include "..\..\include\Image.h"
#include "new/SplashDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWeldDetectApp

BEGIN_MESSAGE_MAP(CWeldDetectApp, CWinApp)
	//{{AFX_MSG_MAP(CWeldDetectApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeldDetectApp construction

CWeldDetectApp::CWeldDetectApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWeldDetectApp object

CWeldDetectApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWeldDetectApp initialization

BOOL CWeldDetectApp::InitInstance()
{   

	CSplashDlg splash;
	
	splash.Create(IDD_SPLASH);
	splash.ShowWindow(SW_NORMAL);
	RECT rc;
	splash.GetWindowRect(&rc);
	/*该函数改变一个子窗口，弹出式窗口式顶层窗口的尺寸，位置和Z序。子窗口，弹出式窗口，
	及顶层窗口根据它们在屏幕上出现的顺序排序、顶层窗口设置的级别最高，并且被设置为Z序的第一个窗口。*/
	SetWindowPos(splash.GetSafeHwnd(), HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW);
	Sleep(500);//Splash Window的显示时间

	InitCommonControlsEx;
	//InitCommonControls(); 

	AfxEnableControlContainer();
    SetDialogBkColor(RGB(200,200,250));   //RGB(199,237,204)
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CWeldDetectDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		cvReleaseImage( &dlg.m_image );
		cvReleaseImage( &dlg.m_imageResult );
		//cvReleaseImage( &dlg.m_tempImage );
		cvReleaseImage( &dlg.m_srcImage);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
		cvReleaseImage( &dlg.m_image );
		cvReleaseImage( &dlg.m_imageResult );
		//cvReleaseImage( &dlg.m_tempImage );
		cvReleaseImage( &dlg.m_srcImage);
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
