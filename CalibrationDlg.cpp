#include "StdAfx.h"
#include "WeldDetect.h"
#include "CalibrationDlg.h"
#include "WeldDetectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg dialog


CCalibrationDlg::CCalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalibrationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalibrationDlg)
	m_nStaX = 0;
	m_nEndX = 0;
	m_nResolutionX = 0.0;
	m_nResolutionY = 0.0;
	m_nEndY = _T("");
	m_nStaY = _T("");
	//}}AFX_DATA_INIT
}


void CCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalibrationDlg)
	DDX_Text(pDX, IDC_STATIC_STARTX, m_nStaX);
	DDX_Text(pDX, IDC_STATIC_ENDX, m_nEndX);
	DDX_Text(pDX, IDC_STATIC_XRESOLUTION, m_nResolutionX);
	DDX_Text(pDX, IDC_STATIC_YRESOLUTION, m_nResolutionY);
	DDX_Text(pDX, IDC_STATIC_ENDY, m_nEndY);
	DDX_Text(pDX, IDC_STATIC_STARTY, m_nStaY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalibrationDlg, CDialog)
	//{{AFX_MSG_MAP(CCalibrationDlg)
	ON_BN_CLICKED(IDOK1, OnOk1)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATION, OnButtonCalibration)
	ON_BN_CLICKED(IDC_BUTTON_RECALI, OnButtonRecali)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg message handlers

void CCalibrationDlg::OnOk1() 
{
	// TODO: Add your control notification handler code here
//	UpdateData();
	CWeldDetectDlg* dlg = (CWeldDetectDlg*)(AfxGetApp()->GetMainWnd());
    dlg->m_bCalibration = false ;
	DestroyWindow();
}

void CCalibrationDlg::OnButtonCalibration() 
{
	// TODO: Add your control notification handler code here
    CWeldDetectDlg* dlg = (CWeldDetectDlg*)(AfxGetApp()->GetMainWnd());
    
	m_nStaX=dlg->m_caliStartX;
	m_nEndX=dlg->m_caliEndX;
	m_nStaY=dlg->m_caliStartY;
	m_nEndY=dlg->m_caliEndY;
 
	// um/pixel
	m_nResolutionX = (50*1000.0)/abs(m_nEndX-m_nStaX);//(5*10);
    m_nResolutionY =m_nResolutionX; //(50*1000.0)/(abs(m_nEndY-m_nStaY)*2);//(5*10);
	UpdateData(FALSE);
	dlg->m_resolutionX=m_nResolutionX;
	dlg->m_resolutionY=m_nResolutionY;

	
	CString str, strKey, strPassApp;
	strPassApp = "参数设置";
	
	strKey = "水平分辨率";
	str.Format("%f", m_nResolutionX);	
	WritePrivateProfileString(strPassApp, strKey, str, dlg->m_strFilePath);	
	
	strKey = "垂直分辨率";
	str.Format("%f", m_nResolutionY);	
	WritePrivateProfileString(strPassApp, strKey, str, dlg->m_strFilePath);	
	

}

void CCalibrationDlg::OnButtonRecali() 
{
	// TODO: Add your control notification handler code here
	CWeldDetectDlg* dlg = (CWeldDetectDlg*)(AfxGetApp()->GetMainWnd());
	dlg->m_nCalibration=0;
}
