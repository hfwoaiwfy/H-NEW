#include "StdAfx.h"
#include "../WeldDetect.h"
#include "SplashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashDlg dialog


CSplashDlg::CSplashDlg(CWnd* pParent /*=NULL*/)
	: CDialogSK(CSplashDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplashDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSplashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplashDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplashDlg, CDialogSK)
	//{{AFX_MSG_MAP(CSplashDlg)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashDlg message handlers


BOOL CSplashDlg::OnInitDialog() 
{
	CDialogSK::OnInitDialog();
	
	// TODO: Add extra initialization here
    SetBitmap(IDB_COVER);           // set background bitmap
    SetStyle(LO_RESIZE);                 // resize dialog to the size of the bitmap
    SetTransparentColor(RGB(255, 255, 255)); // set green as the transparent color
		
	SetTimer(1, 500, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSplashDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CDialogSK::OnOK();
		
	CDialog::OnTimer(nIDEvent);
}

void CSplashDlg::OnPaint() 
{	
	// TODO: Add your message handler code here
	
	CDialogSK::OnPaint(); 
}

void CSplashDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	CDialogSK::OnOK();
	
	CDialogSK::OnLButtonDown(nFlags, point);
}
