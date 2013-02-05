#pragma once


// CTableButton

class CTableButton : public CButton
{
	DECLARE_DYNAMIC(CTableButton)

public:
	CTableButton(char chButton);
	virtual ~CTableButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	char m_chButtonID;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


