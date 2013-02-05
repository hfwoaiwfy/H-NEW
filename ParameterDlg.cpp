#include "StdAfx.h"
#include "WeldDetect.h"
#include "ParameterDlg.h"
#include "WeldDetectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameterDlg dialog


CParameterDlg::CParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParameterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameterDlg)
	CWeldDetectDlg* dlg = (CWeldDetectDlg*)(AfxGetApp()->GetMainWnd());

	m_dScore = dlg->m_score;
	m_roiX = dlg->m_roiWidthVariable;
	m_roiY = dlg->m_roiHightVariable;
	//}}AFX_DATA_INIT
}

void CParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterDlg)
	DDX_Text(pDX, IDC_EDIT_SCORE, m_dScore);
	DDX_Text(pDX, IDC_EDIT_ROI_X, m_roiX);
	DDX_Text(pDX, IDC_EDIT_ROI_Y, m_roiY);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CParameterDlg, CDialog)
	//{{AFX_MSG_MAP(CParameterDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameterDlg message handlers

void CParameterDlg::OnButtonSaveparameter() 
{
	// TODO: Add your control notification handler code here
	//CWeldDetectDlg* dlg = (CWeldDetectDlg*)(AfxGetApp()->GetMainWnd());


}
