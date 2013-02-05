#if !defined(AFX_CALIBRATIONDLG_H__A473E8E3_94B6_404C_90D7_E548F2AADA13__INCLUDED_)
#define AFX_CALIBRATIONDLG_H__A473E8E3_94B6_404C_90D7_E548F2AADA13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalibrationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg dialog

class CCalibrationDlg : public CDialog
{
// Construction
public:

	CCalibrationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalibrationDlg)
	enum { IDD = IDD_DIALOG_CALIBRATION };
    int		m_nStaX;
	int		m_nEndX;
	double	m_nResolutionX;
	double	m_nResolutionY;
	CString	m_nEndY;
	CString	m_nStaY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalibrationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalibrationDlg)
	afx_msg void OnOk1();
	afx_msg void OnButtonCalibration();
	afx_msg void OnButtonRecali();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIBRATIONDLG_H__A473E8E3_94B6_404C_90D7_E548F2AADA13__INCLUDED_)
