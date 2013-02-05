#include "StdAfx.h"
#include "WeldDetect.h"
#include "CustomButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomButton
int CCustomButton::m_style=1;
CCustomButton::CCustomButton()
{
	m_State=bsNormal;
}

CCustomButton::~CCustomButton()
{
	m_State=bsNormal;
}


BEGIN_MESSAGE_MAP(CCustomButton, CButton)
	//{{AFX_MSG_MAP(CCustomButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomButton message handlers

void CCustomButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_State=bsDown;
	InvalidateRect(NULL,TRUE);
	//CButton::OnLButtonDown(nFlags, point);
}

void CCustomButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

/*	if (m_State!=bsNormal)
	{
        m_State=bsNormal;
		ReleaseCapture();
		InvalidateRect(NULL,TRUE);
	}
     */
     ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,GetDlgCtrlID(),(LPARAM)m_hWnd);
	//CButton::OnLButtonUp(nFlags, point);
}

void CCustomButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HRGN hRgn = CreateRectRgn(0,0,0,0);
	GetWindowRgn(hRgn);
	BOOL ret=PtInRegion(hRgn,point.x,point.y);// 确定点是否在指定区域内  zai 返回非零
	if (ret)
	{
		if (m_State==bsDown)
		{
			return;
		}
		if (m_State!=bsHot)
		{
			m_State=bsHot;
			InvalidateRect(NULL,TRUE);
			SetCapture();
		}
	}
	else
	{
	 m_State=bsNormal;
	 InvalidateRect(NULL,TRUE);
	 ReleaseCapture();
	}
	DeleteObject(hRgn);
	CButton::OnMouseMove(nFlags, point);
}

void CCustomButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	m_State=bsNormal;
	InvalidateRect(NULL,TRUE);
	// TODO: Add your message handler code here
	
}

void CCustomButton::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
    CWnd* pWnd = this;
	CString Text;
	CRect RC;
	CFont font;
	CFont *pOldFont;
	CBrush Brush;
	CBrush *pOldBrush;
	CPoint PT(2,2);
	dc.SetBkMode(TRANSPARENT);
	font.CreateFont(25,0,0,0,FW_HEAVY,0,0,0,ANSI_CHARSET,\
		 OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,\
		 VARIABLE_PITCH|FF_SWISS,"MS Sans Serif");
	pOldFont=dc.SelectObject(&font);
    if (m_State==bsNormal)
    {
     if (m_style==2)
     {
		 CBitmap bmp;
		 bmp.LoadBitmap(IDB_BITMAP1);
		 Brush.CreatePatternBrush(&bmp);
     }
	 else
		 Brush.CreateSolidBrush(RGB(64,140,64)); //RGB(100,150,150)
	    dc.SetTextColor(RGB(250,250,250));
    }
	else if (m_State==bsDown)
	{
		Brush.CreateSolidBrush(RGB(240,2,2));    //RGB(160,160,160)
		dc.SetTextColor(RGB(50,50,250));
	}
	else if (m_State==bsHot)
	{
		Brush.CreateSolidBrush(RGB(200,200,200));
		dc.SetTextColor(RGB(80,80,80));
	}
	else if (m_State==bsdisable)
	{
		Brush.CreateSolidBrush(RGB(190,190,190));
		dc.SetTextColor(RGB(100,100,100));
	}
	pOldBrush=dc.SelectObject(&Brush);
	pWnd->GetClientRect(&RC);
	dc.RoundRect(&RC,PT);
	HRGN hRgn=CreateRectRgn(RC.left,RC.top,RC.right,RC.bottom);
	pWnd->SetWindowRgn(hRgn,TRUE);
	DeleteObject(hRgn);

	pWnd->GetWindowText(Text);
	dc.DrawText(Text,&RC,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	font.DeleteObject();
	Brush.DeleteObject();
	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldBrush);
}

void CCustomButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	OnPaint();		
}
