#include "StdAfx.h"
#include "WeldDetect.h"
#include "HistoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistoryDlg dialog


CHistoryDlg::CHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistoryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistoryDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistoryDlg, CDialog)
	//{{AFX_MSG_MAP(CHistoryDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryDlg message handlers
