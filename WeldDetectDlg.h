// WeldDetectDlg.h : header file
//

#if !defined(AFX_WELDDETECTDLG_H__975281DB_DA28_4F78_A192_CBAF907AE9CB__INCLUDED_)
#define AFX_WELDDETECTDLG_H__975281DB_DA28_4F78_A192_CBAF907AE9CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cv.h"
#include "highgui.h"

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256
#define IMAGE_CHANNELS 3
#define GRAB_WIDTH 768
#define GRAB_HEIGHT 576

#define WIDTH_TEMP 200
#define HEIGHT_TEMP 100

#define max_corners 400
#define PULSE 0.234375     //um/pulse    
#define PASSWORD    "111"    
#define READ_TIMEOUT 100 // milliseconds
#define NUMBER 9
#define OFFSETMAX 500
#define OFFSETMIN 90
#define JOGSPEED 45000
#define Kp 40000
#define Ki 10
#define Kd 5

#define WM_DO WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// CWeldDetectDlg dialog
UINT TestThread(void *p);
UINT WacthThread(void *PP);
#include "CustomButton.h"

class CWeldDetectDlg : public CDialog
{
// Construction
public:
	void rerecord();
	bool m_bAutoRunz;
	bool m_bAutoRuny;
	bool m_bAutoRunx;
	void move();
	
	bool m_bStarting;
	int m_heightGrabControl;
	int m_widthGrabControl;
	CRect m_sizeContinueGrab;
    
	
	bool m_bAutoRun;
	CButton* m_pCheck;
    
	//校正变量
	int m_nCalibration;
	bool m_bCalibration;
	int m_caliEndY;
	int m_caliStartY;
	int m_caliEndX;
	int m_caliStartX;
	
	IplImage* m_pImage;
	CString m_tempImageFile;
	CString m_strFilePath;
	double m_score;
	double m_resolutionY;
	double m_resolutionX;
	CvRect m_drawRectROI;
	CvRect m_drawRectTemp;         //绘制的矩形区域
	int m_roiHightVariable;
	int m_roiWidthVariable;
	IplImage* m_srcImage;
	int m_nSetTemp;
	CWeldDetectDlg(CWnd* pParent = NULL);	// standard constructor

	CWinThread* m_pTestThread;
	HANDLE m_hTestThreadKillEvent;
	CRect m_rect;               //矩形区域
	unsigned char* grabImageBuffer;
	bool m_bGrabFrame;
	CvPoint m_modelPosition;
	CvPoint m_centerCross;
	bool m_bDrawCross;
	bool m_bDrawRect;
	CvPoint m_endRect;          //矩形框结束坐标
	CvPoint m_startRect;        //矩形框开始坐标
	IplImage* m_tempImage;      //模板图像，用于模板匹配

	IplImage* m_imageResult;    //图像处理结果图像，原始尺寸
	IplImage* m_image;          //用于显示的缩放过的结果图像
	
    HANDLE hCom;
	HANDLE m_ThreadWacth;
    CWinThread* hComWacthThread;
    
	

	void ResizeImage(IplImage* img);
	void ShowImage( IplImage* img, UINT ID );

// Dialog Data
	//{{AFX_DATA(CWeldDetectDlg)
	enum { IDD = IDD_WELDDETECT_DIALOG };
	CCustomButton	m_down;
	CCustomButton	m_end;
	CCustomButton	m_left;
	CCustomButton	m_right;
	CCustomButton	m_start;
	CCustomButton	m_stop;
	CCustomButton	m_temp;
	CCustomButton	m_up;
	BOOL	m_UseKey;
	BOOL	m_bTempTest;
	int		m_tempx;
	int		m_tempy;
	int		m_nowx;
	int		m_nowy;
	BOOL	m_UseG;
	CString	m_info;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeldDetectDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    // Generated message map functions
	//{{AFX_MSG(CWeldDetectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonTemp();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonEnd();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMenuitemCalibration();
	afx_msg void OnMenuitemParameter();
	afx_msg void OnMenuitemHistory();
	afx_msg void OnMenuitemExit();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonRight();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonStop();
	afx_msg void OnCheckKey();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCheckG();
	afx_msg LRESULT jitouchuli(WPARAM wparam,LPARAM lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELDDETECTDLG_H__975281DB_DA28_4F78_A192_CBAF907AE9CB__INCLUDED_)
