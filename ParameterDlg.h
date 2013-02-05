#if !defined(AFX_PARAMETERDLG_H__805062DD_519D_46E9_945C_5800C2EF7A56__INCLUDED_)
#define AFX_PARAMETERDLG_H__805062DD_519D_46E9_945C_5800C2EF7A56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParameterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParameterDlg dialog

class CParameterDlg : public CDialog
{
// Construction
public:
	CParameterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParameterDlg)
	enum { IDD = IDD_DIALOG_PARAMETER };
	double	m_dScore;
	int		m_roiX;
	int		m_roiY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParameterDlg)
	afx_msg void OnButtonSaveparameter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETERDLG_H__805062DD_519D_46E9_945C_5800C2EF7A56__INCLUDED_)
