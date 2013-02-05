#if !defined(AFX_HISTORYDLG_H__56B6AC97_853F_409A_8B59_E97ECF631956__INCLUDED_)
#define AFX_HISTORYDLG_H__56B6AC97_853F_409A_8B59_E97ECF631956__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistoryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistoryDlg dialog

class CHistoryDlg : public CDialog
{
// Construction
public:
	CHistoryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHistoryDlg)
	enum { IDD = IDD_DIALOG_HISTORY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHistoryDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYDLG_H__56B6AC97_853F_409A_8B59_E97ECF631956__INCLUDED_)
