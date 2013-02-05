// TableButton.cpp : 实现文件
//

#include "stdafx.h"
#include "WeldDetectDlg.h"
#include "TableButton.h"
#include ".\tablebutton.h"


// CTableButton

IMPLEMENT_DYNAMIC(CTableButton, CButton)
CTableButton::CTableButton(char chButtonID)
: m_chButtonID(chButtonID)
{
}

CTableButton::~CTableButton()
{
}


BEGIN_MESSAGE_MAP(CTableButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CTableButton 消息处理程序


void CTableButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (( m_chButtonID == 'U') || 
		( m_chButtonID == 'D') || 
		( m_chButtonID == 'L') || 
		( m_chButtonID == 'R'))
	{
		CInspectionDlg* dlg = ((CInspectionDlg*)(GetOwner()->GetOwner()));
		int lJogSpeed;

		if ( dlg->m_scanPage )
		{
			lJogSpeed = (int)(( MAX_TABLE_SPEED / 100 ) * (101 - dlg->m_scanPage.m_sliTableSpeed.GetPos()) / dlg->GetTransportPixelSize());

			switch( m_chButtonID )
			{
			case 'U':
				PcbieTransportJogY( lJogSpeed );
				break;
			case 'D':
				PcbieTransportJogY( -lJogSpeed );
				break;
			case 'L':
				PcbieTransportJogX( -lJogSpeed );
				break;
			case 'R':
				PcbieTransportJogX( lJogSpeed );
				break;
			default:
				break;
			}
		}
		CButton::OnLButtonDown(nFlags, point);
		return;
	}
	if (( m_chButtonID == 'T') || 
		( m_chButtonID == 'B'))
	{
		/* 面阵相机部分 */
		int lJogSpeed;
		CVRCameraPositionPage* dlgVR = (CVRCameraPositionPage*)GetOwner();
		switch( m_chButtonID )
		{
			case 'T':
				dlgVR->UpdateData( TRUE );
				lJogSpeed = MAX_VRCAMERA_SPEED * ( dlgVR->m_sliJogSpeed.GetRangeMax() - dlgVR->m_sliJogSpeed.GetPos() );
				PcbieTransportJogVR( -lJogSpeed );
				break;
			case 'B':
				dlgVR->UpdateData( TRUE );
				lJogSpeed = MAX_VRCAMERA_SPEED * ( dlgVR->m_sliJogSpeed.GetRangeMax() - dlgVR->m_sliJogSpeed.GetPos() );
				PcbieTransportJogVR( lJogSpeed );
				break;
			default:
				break;
		}
		CButton::OnLButtonDown(nFlags, point);
		return;
	}
}

void CTableButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch( m_chButtonID )
	{
	case 'U':
		PcbieTransportJogY( 0 );
        break;
	case 'D':
		PcbieTransportJogY( 0 );
        break;
	case 'L':
		PcbieTransportJogX( 0 );
        break;
	case 'R':
		PcbieTransportJogX( 0 );
        break;
	case 'T':// 面阵相机部分
		PcbieTransportJogVR( 0 );
		break;
	case 'B':
		PcbieTransportJogVR( 0 );
		break;
	default:
		break;
	}
	CButton::OnLButtonUp(nFlags, point);
}