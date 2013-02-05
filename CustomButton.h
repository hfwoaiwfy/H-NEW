#if !defined(AFX_CUSTOMBUTTON_H__B4A0F915_B61E_4164_937C_9CD7024C66F5__INCLUDED_)
#define AFX_CUSTOMBUTTON_H__B4A0F915_B61E_4164_937C_9CD7024C66F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomButton window
//¶¨Òå°´Å¥×´Ì¬
enum ButtonState {bsNormal,bsHot,bsDown,bsdisable};
class CCustomButton : public CButton
{
// Construction
public:
	CCustomButton();
    int m_State;
   static int m_style;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMBUTTON_H__B4A0F915_B61E_4164_937C_9CD7024C66F5__INCLUDED_)
