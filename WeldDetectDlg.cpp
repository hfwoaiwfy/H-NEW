#include "StdAfx.h"
#include "WeldDetect.h"
#include "WeldDetectDlg.h"

#include <stdio.h>
#include <io.h>
#include <afxwin.h>
#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include "Mil.h"

//#include "..\..\include\motion.h"
#include "..\..\include\Image.h"
//#include "..\..\include\Amclmotion.h"
#include "..\..\include\Amcl.h"

#include "CalibrationDlg.h"
#include "ParameterDlg.h"
#include "HistoryDlg.h"
#include "CommonFunction.h"
#include "PasswordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//定义结构体，可快速访问图像的某个像素值
template<class T> class Image
{
private:
	IplImage* imgp;
public:
	Image(IplImage* img=0) {imgp=img;}
	~Image(){imgp=0;}
	void operator=(IplImage* img) {imgp=img;}
	inline T* operator[](const int rowIndx) {
		return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));}
};
typedef struct{
	unsigned char b,g,r;
} RgbPixel;
typedef struct{
	float b,g,r;
} RgbPixelFloat;
typedef Image<RgbPixel> RgbImage;
typedef Image<RgbPixelFloat> RgbImageFloat;
typedef Image<unsigned char> BwImage;
typedef Image<float> BwImageFloat;

static unsigned char CRC8_TAB[256]={    
    	0x00,0x07,0x0E,0x09,0x1C,0x1B,0x12,0x15,0x38,0x3F,0x36,0x31,0x24,0x23,0x2A,0x2D,  
		0x70,0x77,0x7E,0x79,0x6C,0x6B,0x62,0x65,0x48,0x4F,0x46,0x41,0x54,0x53,0x5A,0x5D,  
		0xE0,0xE7,0xEE,0xE9,0xFC,0xFB,0xF2,0xF5,0xD8,0xDF,0xD6,0xD1,0xC4,0xC3,0xCA,0xCD,  
		0x90,0x97,0x9E,0x99,0x8C,0x8B,0x82,0x85,0xA8,0xAF,0xA6,0xA1,0xB4,0xB3,0xBA,0xBD,  
		0xC7,0xC0,0xC9,0xCE,0xDB,0xDC,0xD5,0xD2,0xFF,0xF8,0xF1,0xF6,0xE3,0xE4,0xED,0xEA,  
		0xB7,0xB0,0xB9,0xBE,0xAB,0xAC,0xA5,0xA2,0x8F,0x88,0x81,0x86,0x93,0x94,0x9D,0x9A,  
		0x27,0x20,0x29,0x2E,0x3B,0x3C,0x35,0x32,0x1F,0x18,0x11,0x16,0x03,0x04,0x0D,0x0A,  
		0x57,0x50,0x59,0x5E,0x4B,0x4C,0x45,0x42,0x6F,0x68,0x61,0x66,0x73,0x74,0x7D,0x7A,  
		0x89,0x8E,0x87,0x80,0x95,0x92,0x9B,0x9C,0xB1,0xB6,0xBF,0xB8,0xAD,0xAA,0xA3,0xA4,  
		0xF9,0xFE,0xF7,0xF0,0xE5,0xE2,0xEB,0xEC,0xC1,0xC6,0xCF,0xC8,0xDD,0xDA,0xD3,0xD4,  
		0x69,0x6E,0x67,0x60,0x75,0x72,0x7B,0x7C,0x51,0x56,0x5F,0x58,0x4D,0x4A,0x43,0x44,  
		0x19,0x1E,0x17,0x10,0x05,0x02,0x0B,0x0C,0x21,0x26,0x2F,0x28,0x3D,0x3A,0x33,0x34,  
		0x4E,0x49,0x40,0x47,0x52,0x55,0x5C,0x5B,0x76,0x71,0x78,0x7F,0x6A,0x6D,0x64,0x63,  
		0x3E,0x39,0x30,0x37,0x22,0x25,0x2C,0x2B,0x06,0x01,0x08,0x0F,0x1A,0x1D,0x14,0x13,  
		0xAE,0xA9,0xA0,0xA7,0xB2,0xB5,0xBC,0xBB,0x96,0x91,0x98,0x9F,0x8A,0x8D,0x84,0x83,  
		0xDE,0xD9,0xD0,0xD7,0xC2,0xC5,0xCC,0xCB,0xE6,0xE1,0xE8,0xEF,0xFA,0xFD,0xF4,0xF3  
         }; 

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

IplImage* pImage = cvCreateImageHeader(cvSize(GRAB_WIDTH,GRAB_HEIGHT),8,1);
CvPoint2D32f lastoffset;

BYTE r0,r1,data0,data1,rr,fasongdata;
uchar temp[1]={0};
uchar lpBuffer[7]={0};       //接收有效数据
uchar lp0Buffer[9]={0};      //接收包含数据长度和校验的数据
uchar successrece=0;
unsigned char kaishi=0,letrece=0,xuhao=0,jieshoushujugeshu=0;
int Speed=0;
uchar Weldtype=1;    //初始化为环缝
uchar shoudong=0;
LONG DriverHandle;


int aax[6]={0};
int bby[6]={0};
int cct[6]={0};
uchar dir=2,diry=2;
uchar counter=0;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeldDetectDlg dialog

CWeldDetectDlg::CWeldDetectDlg(CWnd* pParent )
	: CDialog(CWeldDetectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWeldDetectDlg)
	m_UseKey = TRUE;
	m_bTempTest = FALSE;
	m_tempy = 0;
	m_nowx = 0;
	m_nowy = 0;
	m_UseG = FALSE;
	m_info = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWeldDetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWeldDetectDlg)
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_down);
	DDX_Control(pDX, IDC_BUTTON_END, m_end);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_left);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_right);
	DDX_Control(pDX, IDC_BUTTON_START, m_start);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_stop);
	DDX_Control(pDX, IDC_BUTTON_TEMP, m_temp);
	DDX_Control(pDX, IDC_BUTTON_UP, m_up);
	DDX_Check(pDX, IDC_CHECK_KEY, m_UseKey);
	DDX_Text(pDX, IDC_EDIT_TEMPX, m_tempx);
	DDX_Text(pDX, IDC_EDIT_TEMPY, m_tempy);
	DDX_Text(pDX, IDC_EDIT_NOWX, m_nowx);
	DDX_Text(pDX, IDC_EDIT_NOWY, m_nowy);
	DDX_Check(pDX, IDC_CHECK_G, m_UseG);
	DDX_Text(pDX, IDC_INFO, m_info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWeldDetectDlg, CDialog)
	//{{AFX_MSG_MAP(CWeldDetectDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEMP, OnButtonTemp)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_END, OnButtonEnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENUITEM_CALIBRATION, OnMenuitemCalibration)
	ON_COMMAND(ID_MENUITEM_PARAMETER, OnMenuitemParameter)
	ON_COMMAND(ID_MENUITEM_HISTORY, OnMenuitemHistory)
	ON_COMMAND(ID_MENUITEM_EXIT, OnMenuitemExit)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_CHECK_KEY, OnCheckKey)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_G, OnCheckG)
	ON_MESSAGE(WM_DO,jitouchuli)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeldDetectDlg message handlers

void GetData(unsigned char* imageData)          //回调函数                   
{
	cvSetData(pImage,imageData,sizeof(uchar)*GRAB_WIDTH);
}

long umCvtPulse(double um)
{
	long pulseNum;
	pulseNum = (long)(um/PULSE);
	return pulseNum;
}

double pulseCvtUm(long pulse)
{
	double um;
	um = double(pulse*PULSE);
	return um;
}

double pixelCvtUm(int pixel,double reso)
{
	return (pixel*reso);
}

int UmCvtPixel(double um, double reso)
{
	return (int)(um/reso);
}  

long PIDPro(uchar mark)
{
  long NUM;
  UINT NUMT;
  long SPID;
  static long SUMX=0;
  static long SUMY=0; 

  NUMT=cct[0]+cct[1]+cct[2]+cct[3]+cct[4];
  if (mark==0)
  {
	  NUM=aax[0]+aax[1]+aax[2]+aax[3]+aax[4];
	  SUMX=SUMX+NUM; 
	  SPID=Kp*(NUM*1.0/NUMT)+Ki*SUMX;
  }
  else
  {
      NUM=bby[0]+bby[1]+bby[2]+bby[3]+bby[4];
	  SUMY=SUMY+NUM;
	  SPID=Kp*(NUM*1.0/NUMT)+Ki*SUMY;
  }
  return SPID;
}


 BOOL SetMacConfig(long DriverHandle, WORD wAxis)
{
	ADM_MacConfig		stMacConfig;
	LONG				lReturnCode;

	//
	// Set machine parameter
	//
	stMacConfig.wPOLogic		= ADM_PO_NORMAL;// Normal logic of pulse output 
	stMacConfig.dfGearRatio		= 1;			// 1:1
	stMacConfig.dfPitch			= 4;			// 1 mm
	stMacConfig.dwPPR			= 51200;			// Pulses per round
	stMacConfig.wPulseMode		= ADM_PULSE_DIR;	// 2 pulse mode
	stMacConfig.dwMaxSpeed		= 468;			// 2000 RPM

	lReturnCode = ADM_SetMacConfig(
							DriverHandle, 
							wAxis,			// 0:X-Axis 1:Y-Axis 2:Z-Axis 3:U-Axis
							&stMacConfig
							);	
	if(lReturnCode != SUCCESS)
	{
        MessageBox(NULL,"SetMacConfig调用失败",NULL,0);
		return FALSE;
	}

	return TRUE;

}


 //------------------------------------------------------
// Set Motion I/O parameter
//------------------------------------------------------
BOOL SetMIOConfig(long DriverHandle, WORD wAxis)
{
	ADM_MIOConfig		stMIOConfig;
	LONG				lReturnCode;

	//
	// Set Motion I/O parameter
	//
	stMIOConfig.wHWLimitMode_N	= ADM_NO;		// Normal open	
	stMIOConfig.wHWLimitMode_P	= ADM_NO;		// Normal open	
	stMIOConfig.wSDMode_N		= ADM_NO;		// Normal open	
	stMIOConfig.wSDMode_P		= ADM_NO;		// Normal open	

	lReturnCode = ADM_SetMIOConfig(
							DriverHandle, 
							wAxis,			// 0:X-Axis 1:Y-Axis 2:Z-Axis 3:U-Axis
							&stMIOConfig
							);	
	if(lReturnCode != SUCCESS)
	{
			MessageBox(NULL,"SetMIOConfig调用失败",NULL,0);
			return FALSE;
	}
	return TRUE;

}

//------------------------------------------------------
// Set Point to Point Motion parameter
//------------------------------------------------------
BOOL SetPtPMotionConfig(long DriverHandle, WORD wAxis)
{
	ADM_PtPMotionConfig	stPtPMotionConfig;
	LONG				lReturnCode;


	//
	// Set unit (It can set to ADM_UNIT_PULSE, ADM_UNIT_MM or ADM_UNIT_INCH)
	//
	ADM_SetUnit(DriverHandle, ADM_UNIT_PULSE);


	//
	// Set Point to Point motion parameter
	//
	stPtPMotionConfig.wAccDecMode = ADM_T_T;	// Also can set it to S-Curve(ADM_AS_AS) 	
	stPtPMotionConfig.dfAccTime_L = 5;		// 100 ms
	stPtPMotionConfig.dfAccTime_S = 0;			// This parameter is for S-Curve(ADM_AS_AS)
	stPtPMotionConfig.dfDecTime_L = 5;		// 100 ms
	stPtPMotionConfig.dfDecTime_S = 0;			// This parameter is for S-Curve(ADM_AS_AS)
	stPtPMotionConfig.dfSV = 500;				// 800 pulse/sec
	stPtPMotionConfig.dfDV = 3000;				// 5000 pulse/sec

	lReturnCode = ADM_SetPtPMotionConfig(DriverHandle, wAxis, &stPtPMotionConfig);
	if(lReturnCode != SUCCESS)
	{
			MessageBox(NULL,"SetPtPMotionConfig调用失败",NULL,0);
			return FALSE;
	}

	return TRUE;
}
/**************************************************************************
* 函数名称： rece(void)
* 功能描述： 串口接收函数
* 输入参数： 空
* 输出参数： 空
* 返 回 值： 无
* 其它说明：
* 当前版本： V1.0
* 修改日期    版本号     修改人	     修改内容
* -----------------------------------------------
* 2002/08/01   V1.0	    XXXX	      XXXX
***************************************************************************/

void rece(void)
{
   if (temp[0]==0x30 || temp[0]==0x31 || letrece==1)
   {   
	   char i;
	   if ((letrece==0x01)&&(xuhao==0x00))
	   {
           lp0Buffer[xuhao]=temp[0];
		   jieshoushujugeshu=temp[0]+1;
		   xuhao++;
		   return;
	   }
	   switch (temp[0])
		{	
         case 0x30:
			     
				 if((letrece==0x00)&&(kaishi==0))
				 {
				   kaishi=0x01;	
				 }
				 else 
				 {
					if(letrece==0x01)
						{
						
						 lp0Buffer[xuhao]=temp[0];
						 xuhao=xuhao+1;

						}
					else
						{
							letrece=0x00;
							xuhao=0x00;
							kaishi=0x00;
             				lp0Buffer[0]=0x00;
							lp0Buffer[1]=0x00;
				
						}
				 }

		break;
		case 0x31:
		    	if((letrece==0x00)&&(kaishi==1))
				{
				kaishi=0x02;
				letrece=0x01;
				xuhao=0x00;
				}
			    else 
				{
		        	if(letrece==0x01)
					{
			    	lp0Buffer[xuhao]=temp[0];
			    	xuhao=xuhao+1;

					}
		        	else
					{
					letrece=0x00;
					xuhao=0x00;
					kaishi=0x00;
					}
				}
		   break;
       case 0x46:
	            if((xuhao<=jieshoushujugeshu)&&(kaishi==0x02))
				{
	            	if(xuhao<jieshoushujugeshu)
					{
		        	lp0Buffer[xuhao]=temp[0];
		        	xuhao=xuhao+1;
					}
		            else
			         kaishi=0x03;
				}
            	else
				{
		    	letrece=0x00;
		    	xuhao=0x00;
		    	kaishi=0x00;
				}	
           break;
    	case 0x47:
	        	if(((xuhao<jieshoushujugeshu)&&(kaishi==0x02))||((xuhao==jieshoushujugeshu)&&(kaishi==0x03)))
				{
			        if(kaishi==0x02)
					{
			     	lp0Buffer[xuhao]=temp[0];
			     	xuhao=xuhao+1;
					}
			        else
					{
						data1 = *(lp0Buffer+1);                 
						r1 = CRC8_TAB[data1];                 
						for (i = 2; i < jieshoushujugeshu-1; i++)
						{
							data1 = *(lp0Buffer + i);          
							r1 = CRC8_TAB[r1 ^ data1];                //r和data异或为表索引从表中取一字节>r
						}
                       data1 = *(lp0Buffer + jieshoushujugeshu-1); 
			        	if(r1 ^ data1)   //重发程序  。。。。。。。。。。。。。。。
						{
					   	 letrece=0x00;
						 xuhao=0x00;
						 kaishi=0x00;			
						}                   
			        	else      
						{
						  for(i=1;i<jieshoushujugeshu-1;i++)
						  {
							  lpBuffer[i-1]=lp0Buffer[i];
						  }
                          letrece=0x00;
						  xuhao=0x00;
						  kaishi=0x00;
						  successrece=1;		
						}          
					}
				}
	        	else
				{
		    	letrece=0x00;
		    	xuhao=0x00;
		    	kaishi=0x00;
				}


	    break;

    	default:
			if((kaishi==0x02)&&(xuhao<jieshoushujugeshu))
			{
				lp0Buffer[xuhao]=temp[0];
				xuhao=xuhao+1;
			}
			else
			{
				letrece=0x00;
				xuhao=0x00;
				kaishi=0x00;

			}
			break;
  }
}
}


/**************************************************************************
* 函数名称： OnInitDialog(void)
* 功能描述： 初始化函数 包括变量初始化 串口初始化 相机初始化
* 输入参数： 空
* 输出参数： 空
* 返 回 值： 无
* 其它说明：
* 当前版本： V1.0
* 修改日期    版本号     修改人	     修改内容
* -----------------------------------------------
* 2002/08/01   V1.0	    XXXX	      XXXX
***************************************************************************/
BOOL CWeldDetectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CvSize ImgSize;
	ImgSize.height = IMAGE_HEIGHT;
	ImgSize.width = IMAGE_WIDTH;
    m_image = cvCreateImage( ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS );
    m_imageResult = cvCreateImage( cvSize(GRAB_WIDTH,GRAB_HEIGHT), IPL_DEPTH_8U, IMAGE_CHANNELS );
	m_srcImage = cvCreateImage( ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS );

	m_bDrawCross = false;
	m_bDrawRect = false;
	m_bGrabFrame = false;

	m_nSetTemp = 0;
	m_tempImageFile = "D:\\tempImage.bmp";
	m_bCalibration = false;
	m_nCalibration = 0;
	m_caliEndY=0;
	m_caliStartY=0;
	m_caliEndX=0;
	m_caliStartX=0;
    m_tempx = 0;
	m_tempy = 0;
	m_nowx = 0;
	m_nowy = 0;
	UpdateData(false);

	 m_bAutoRun = true;
     m_bAutoRunx = true;
     m_bAutoRuny = true;
	 m_bAutoRunz = true;
	m_bStarting = false;

	GetDlgItem(IDC_STATIC_CONTINUEGRAB) ->GetClientRect( &m_sizeContinueGrab );
	// 求出图片控件的宽和高
	m_widthGrabControl = m_sizeContinueGrab.right - m_sizeContinueGrab.left;			
	m_heightGrabControl = m_sizeContinueGrab.bottom - m_sizeContinueGrab.top;

	m_strFilePath = "D:\\Configer.ini";

	if (_access(m_strFilePath,0)!=-1)                                  //判断是否有配置文件
	{
		CString str, strKey, strPassApp;                               //如果存在配置文件，读取配置文件
		strPassApp = "参数设置";
		
		strKey = "水平分辨率";
		m_resolutionX = My_GetProfileDouble(strPassApp, strKey, 0, m_strFilePath);

		strKey = "垂直分辨率";
		m_resolutionY = My_GetProfileDouble(strPassApp, strKey, 0, m_strFilePath);

		strKey = "水平扩展";
		m_roiWidthVariable = My_GetProfileDouble(strPassApp, strKey, 0, m_strFilePath);

		strKey = "垂直扩展";
		m_roiHightVariable = My_GetProfileDouble(strPassApp, strKey, 0, m_strFilePath);

		strKey = "匹配度";
		m_score = My_GetProfileDouble(strPassApp, strKey, 0, m_strFilePath);
	}
	
	else                                                              //如果不存在配置文件，则给相关变量一个初始值
	{
		m_roiHightVariable = 80;
		m_roiWidthVariable = 80;
		
		m_resolutionX = 75;
		m_resolutionY = 75;
	    m_score = 0.8;
	}
	m_start.m_State=bsdisable;
	m_end.m_State=bsdisable;
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);                //初始化界面时 开始和停止按钮变灰
	GetDlgItem(IDC_BUTTON_END)->EnableWindow(FALSE);
	
	
    hCom=CreateFile("COM2",GENERIC_READ|GENERIC_WRITE,               //打开串口1
		0,NULL,OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL);
	if (hCom==INVALID_HANDLE_VALUE)
	{
		::MessageBoxA(NULL,"打开串口2失败!",NULL,0);
		return FALSE;
	}
        
    else                                                              //如果打开成功 则配置相关参数
	{
		SetCommMask(hCom,EV_RXCHAR | EV_TXEMPTY);                    //设置事件掩模来监视指定通信端口上的事件
		SetupComm(hCom,8,8);                                   //设置输入输出缓冲区大小
		PurgeComm(hCom,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);  //函数清空缓冲区
		COMMTIMEOUTS Timeouts;                                        //设置超时时间
		DCB dcb;
		Timeouts.ReadIntervalTimeout=5;   
		
		Timeouts.ReadTotalTimeoutConstant=20;
		Timeouts.ReadTotalTimeoutMultiplier=50;
		Timeouts.WriteTotalTimeoutConstant=20;
		Timeouts.WriteTotalTimeoutMultiplier=50;
		SetCommTimeouts(hCom,&Timeouts);
		
		GetCommState(hCom,&dcb);                      
		dcb.BaudRate=115200;
		dcb.ByteSize=8;
		dcb.StopBits=ONESTOPBIT;
		dcb.Parity=NOPARITY;
		SetCommState(hCom,&dcb);
	}
   	CWaitCursor wait;
	m_ThreadWacth = CreateEvent(NULL,TRUE,FALSE,NULL);
	hComWacthThread = AfxBeginThread(WacthThread, this);
	hComWacthThread->m_bAutoDelete = false;
    hComWacthThread->ResumeThread();


	LONG lReturnCode = ADM_OpenDevice(0, ADM_PCI1243, &DriverHandle);
	if (lReturnCode != SUCCESS)
	{
		::MessageBoxA(NULL,"打开运动控制卡失败",NULL,0);
		return FALSE;
	}

	for (WORD wAxis=0;wAxis<2;wAxis++)
	{
		if (!SetMacConfig(DriverHandle,wAxis))
		{
			return FALSE;
		}
		if (!SetMIOConfig(DriverHandle,wAxis))
		{
			return FALSE;
		}
		if (!SetPtPMotionConfig(DriverHandle,wAxis))
		{
			return FALSE;
		}
	}
    m_info = _T("请设置模板!");
	 UpdateData(FALSE);
	bool f = VCamInit(GetDlgItem(IDC_STATIC_CONTINUEGRAB)->GetSafeHwnd(),(long)GetData);             //初始化相机
	if (!f)
	{
		::MessageBoxA(NULL,"相机初始化失败！",NULL,0);
		return FALSE;
	}
	VCamStartCapture(0);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWeldDetectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CWeldDetectDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
  else
	{
		CDialog::OnPaint();
	
		CDialog::UpdateWindow();
		ShowImage(m_image,IDC_STATIC_TEMPIMAGE);

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWeldDetectDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CWeldDetectDlg::ShowImage(IplImage *img, UINT ID)                                              // ID 是Picture Control控件的ID号
{
	
	CDC* pDC = GetDlgItem( ID ) ->GetDC();		
	HDC hDC = pDC ->GetSafeHdc();				
	
	CRect rect;
	GetDlgItem(ID) ->GetClientRect( &rect );
	int rw = rect.right - rect.left;			
	int rh = rect.bottom - rect.top;
	int iw = img->width;	
	int ih = img->height;
	int tx = (int)(rw - iw)/2;	
	int ty = (int)(rh - ih)/2;
	SetRect( rect, tx, ty, tx+iw, ty+ih );
	CvvImage cimg;
	cimg.CopyOf( img);
	cimg.DrawToHDC( hDC, &rect );	
	
	ReleaseDC( pDC );
}


void CWeldDetectDlg::ResizeImage(IplImage *img)
{  
	if (m_image)
	{
		cvZero(m_image);
	}
	int w = img->width;
	int h = img->height;
	int max = (w > h)? w: h;
	float scale = (float) ( (float) max / 256.0f );
	int nw = (int)( w/scale );
	int nh = (int)( h/scale );                                                                 
	int tlx = (nw > nh)? 0: (int)(256-nw)/2;                              // 为了将缩放后的图片存入 TheImage 的正中部位，需计算图片在 TheImage 左上角的期望坐标值
	int tly = (nw > nh)? (int)(256-nh)/2: 0;                                                             
	cvSetImageROI( m_image, cvRect( tlx, tly, nw, nh) );                  // 设置 TheImage 的 ROI 区域，用来存入图片 img
	cvResize( img, m_image );                                             // 对图片 img 进行缩放，并存入到 TheImage 中	
	cvResetImageROI( m_image );                                           // 重置 TheImage 的 ROI 准备读入下一幅图片
}

/**************************************************************************
*  CvPoint cvMatchTemplate()
*
*  功能:
*    模板匹配.
*
*  参数:
*    IplImage* src，源图像输入，8位3通道
*    IplImage* temp，模板输入，8位3通道
*    double &score，最佳匹配度返回
*
*  返回:
*    模板在源图像中左上角的位置
**************************************************************************/
CvPoint cvMatchTemplate(IplImage* src, IplImage* temp, double &score)
{
	IplImage* result = NULL;                                                                //定义存放结果图像变量指针    
	IplImage* srcGray = NULL;                                                               //定义存放源图像变量指针
	IplImage* tempGray = NULL;                                                              //定义存放模板图像变量指针

	int w,h;
	double min_val;
	double max_val;
	CvPoint min_loc;
	CvPoint max_loc;
//	CvRect rect;
	
	w = src->width - temp->width;                                                        
	h = src->height - temp->height;

	try
	{
		result = cvCreateImage(cvSize(w+1,h+1), IPL_DEPTH_32F, 1);                         //创建头并分配数据                
		srcGray = cvCreateImage(cvGetSize(src), 8, 1);                                   
		tempGray = cvCreateImage(cvGetSize(temp), 8, 1);

		cvCvtColor(src, srcGray, CV_BGR2GRAY);			                                   //将源图像转换成灰度图像存在srcGray
		cvCvtColor(temp, tempGray, CV_BGR2GRAY);                                           //将模板图像转换成灰度图像存在tempGray                                              //模板匹配
		cvMatchTemplate(srcGray,tempGray,result,CV_TM_CCORR_NORMED);                       //模板匹配
		cvMinMaxLoc(result,&min_val,&max_val,&min_loc,&max_loc,NULL);                      //查找数组和子数组的最小值和最大值指针
		score = max_val;                                                                   //匹配度
		cvReleaseImage(&srcGray);                                                          //释放头和图像数据
		cvReleaseImage(&tempGray);
		cvReleaseImage(&result);
		return max_loc;                                                                    //返回匹配度最大的位置
	}
	catch(CFileException)                                                        
	{  
		if (srcGray!=NULL)
		{
			cvReleaseImage(&srcGray);
		}
		if (tempGray!=NULL)
		{
			cvReleaseImage(&tempGray);
		}
		if (result!=NULL)
		{
			cvReleaseImage(&result);
		}
	}
}

/**************************************************************************
*  UINT WacthThread(LPVOID p)
*
*  功能:
*    监视串口
*
*  参数:
*    LPVOID p  线程指针
*   
*  返回:
*    
**************************************************************************/

UINT WacthThread(LPVOID p)
{
	CWeldDetectDlg *pDlg = (CWeldDetectDlg *)p;   
	CString str;
    DWORD dwEvtMask;
	SetCommMask(pDlg->hCom,EV_RXCHAR | EV_TXEMPTY);
	PurgeComm(pDlg->hCom,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
    OVERLAPPED ov_Read;
	COMSTAT comstat;
	DWORD dwLength;
    DWORD dwerror=0;
    DWORD dwByteread=0;
    BOOL freadsart;
	DWORD dwRes;
	memset(&ov_Read,0,sizeof(OVERLAPPED)); 
    ov_Read.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL); 
	while (WaitForSingleObject(pDlg->m_ThreadWacth,0) == WAIT_TIMEOUT)
	{  
		WaitCommEvent(pDlg->hCom,&dwEvtMask,&ov_Read);                          //等待串口2上我们利用SetCommMask ()函数设置的事件：
		if(dwEvtMask & EV_RXCHAR == EV_RXCHAR)                                   //如果串口2上发生了EV_RXCHAR事件，说明串口2收到数据                      
		{
			ClearCommError(pDlg->hCom,&dwerror,&comstat);
			dwLength=comstat.cbInQue;
			if(dwLength>0)
			{  
				freadsart = ReadFile(pDlg->hCom,temp,1,&dwByteread,&ov_Read);             
				if(freadsart == FALSE)
				{   
					if (GetLastError()==ERROR_IO_PENDING)   
					{   
						dwRes = WaitForSingleObject(ov_Read.hEvent,READ_TIMEOUT);
						switch(dwRes)
						{
						case WAIT_OBJECT_0:      
							if (!GetOverlappedResult(pDlg->hCom, &ov_Read, &dwByteread, FALSE)) 
							{
								MessageBox(NULL,"读取操作错误!",NULL,1);
							}
							else
							{
								rece();
								if (successrece==1)
								{
									if ((lpBuffer[3] & 0xf0)==0x00)
									{
										if ((lpBuffer[0]==0x10) && (pDlg->m_bStarting ==false) && (Speed!=0))  //启动焊接
										{
											if ((shoudong==0) && (pDlg->m_bAutoRunx==true)&& (pDlg->m_bAutoRuny==true)&& (pDlg->m_bAutoRunz==true))
											{
													pDlg->rerecord();
													PostMessage(pDlg->GetSafeHwnd(),IDC_BUTTON_START,0,0);
											}		
										}
										else if ((lpBuffer[0]==0x01) && (pDlg->m_bStarting ==true))
										{
											PostMessage(pDlg->GetSafeHwnd(),IDC_BUTTON_END,0,0);
										}
									}
									else if(pDlg->m_bStarting ==true)
									{
										PostMessage(pDlg->GetSafeHwnd(),IDC_BUTTON_END,0,0);
									}
								   
									Speed=lpBuffer[1]*256+lpBuffer[2]; 
									if((Speed==0) && (pDlg->m_bStarting ==true))
									  {
									    PostMessage(pDlg->GetSafeHwnd(),IDC_BUTTON_END,0,0);//pDlg->OnEnd();
									  }
									if ((lpBuffer[3] & 0x01)==0x00)
									{
										Weldtype=1;    //横缝  
									}
									else        
									{
										Weldtype=2;    //纵缝 
									}
									PostMessage(pDlg->GetSafeHwnd(),WM_DO,0,0);
								  successrece=0;
								}
							}
							break;
						case WAIT_TIMEOUT:
							MessageBox(NULL,"超时,读取操作错误!",NULL,1);
							break; 
						default:                                                                  // Error in the WaitForSingleObject; abort.
							MessageBox(NULL,"读取操作错误,其他!",NULL,1);                         // This indicates a problem with the OVERLAPPED structure's
							break;	                                                              // event handle.  
							                                                                      
						}
					}
					else
						MessageBox(NULL,"读取操作错误!",NULL,1);
				}
				else     
				{
					rece();
					if (successrece==1)
					{
						if ((lpBuffer[3] & 0xf0)==0x00)
						{
							if ((lpBuffer[0]==0x10) && (pDlg->m_bStarting ==false) && (Speed!=0))  //启动焊接
							{
                                if ((shoudong==0) && (pDlg->m_bAutoRunx==true)&& (pDlg->m_bAutoRuny==true)&& (pDlg->m_bAutoRunz==true))
                                {
								        pDlg->rerecord();
									    PostMessage(pDlg->GetSafeHwnd(),IDC_BUTTON_START,0,0);
                                }		
							}
							else if ((lpBuffer[0]==0x01) && (pDlg->m_bStarting ==true))
							{
						     PostMessage(pDlg->GetSafeHwnd(),IDC_BUTTON_END,0,0);
							}
						}
						else if(pDlg->m_bStarting ==true)
						{
						  PostMessage(pDlg->GetSafeHwnd(),IDC_BUTTON_END,0,0);
						}
					   
						Speed=lpBuffer[1]*256+lpBuffer[2]; 
					    if((Speed==0) && (pDlg->m_bStarting ==true))
						  {
							 PostMessage(pDlg->GetSafeHwnd(),IDC_BUTTON_END,0,0);
						  }
						if ((lpBuffer[3] & 0x01)==0x00)
						{
							Weldtype=1;    //横缝  
						}
						else        
						{
							Weldtype=2;    //纵缝 
						}
						PostMessage(pDlg->GetSafeHwnd(),WM_DO,0,0);
					successrece=0;
					}
				}
			}
		}
      Sleep(1);		
	}
	return 0L;
}




UINT TestThread(LPVOID p)
{
	CWeldDetectDlg *pDlg = (CWeldDetectDlg *)p;
	HWND hdlg=pDlg->GetSafeHwnd();
	int nCount = 1;
    uchar cnt=0;
	pDlg->m_bGrabFrame = true;
	bool bIsProcessed = true;
	CvPoint position;
	CvPoint2D32f offset;
	double score;
	CvRect rect;
	CString str;
	int64 begin_count;
	pDlg->m_tempImage = cvLoadImage(pDlg->m_tempImageFile,CV_LOAD_IMAGE_COLOR);
	IplImage* srcImage;
	int noMatchCnt = 0;
	int overcnt = 0;
    double speed;
	long offsetx;
    long offsety;
 
	OVERLAPPED ov_write={0};
	ov_write.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	while(WaitForSingleObject(pDlg->m_hTestThreadKillEvent,0) == WAIT_TIMEOUT)
	{
		begin_count = cvGetTickCount();		
		VCamSnapOneImage();	 	 		
     	//显示在左下角窗口
		cvZero(pDlg->m_imageResult);
		//cvCopy(pImage,pDlg->m_imageResult);
        cvCvtColor(pImage,pDlg->m_imageResult,CV_GRAY2BGR);
		srcImage = NULL;
			
		//保存感兴趣区域			
		cvSetImageROI(pDlg->m_imageResult,pDlg->m_drawRectROI);
		srcImage = cvCreateImage(cvSize(pDlg->m_drawRectROI.width,pDlg->m_drawRectROI.height),8,3);
		cvCopy(pDlg->m_imageResult,srcImage,NULL);
		cvResetImageROI(pDlg->m_imageResult);

		//进行模板匹配
		position = cvMatchTemplate(srcImage,pDlg->m_tempImage,score);
		cvReleaseImage(&srcImage);
       
        rect.x = position.x + pDlg->m_drawRectROI.x;
    	rect.y = position.y + pDlg->m_drawRectROI.y;
    	str.Format(_T("%d"),rect.x);		 
		pDlg->SetDlgItemText(IDC_EDIT_NOWX,str);
        
		str.Format(_T("%d"),rect.y);		 
		pDlg->SetDlgItemText(IDC_EDIT_NOWY,str);
		offset.x = (rect.x - pDlg->m_modelPosition.x);// * pDlg->m_resolutionX;
		offset.y = (rect.y - pDlg->m_modelPosition.y);// * pDlg->m_resolutionY;
		if (score <= pDlg->m_score)
		{
			noMatchCnt++;
	        ADM_StopMotion_M(DriverHandle, ADM_X_AXIS);
		    ADM_StopMotion_M(DriverHandle, ADM_Y_AXIS);
		    ADM_StopMotion_M(DriverHandle, ADM_Z_AXIS);
			if (noMatchCnt>80)
			{	
				PostMessage(hdlg,IDC_BUTTON_END,0,0);
                offset.x=0;
                offset.y=0;
				if (cnt==0)
				{
					cnt=1;
					MessageBox(NULL,"无法准确定位焊缝,匹配度太低，跟踪结束!",NULL,1); //输出提示信息
				 }
				return 1;
			}
			else
			{
                
			}			
		}
		else
		{
			noMatchCnt = 0;
		}

	   if (abs(offset.x) > 6 || abs(offset.y) > 6)
	    {
           //offset.x=0;
		  // offset.y=0;
           	ADM_StopMotion_M(DriverHandle,1);
            ADM_StopMotion_M(DriverHandle,0);
            ADM_StopMotion_M(DriverHandle,2);
			str.Format(_T("%0.2f"),offset.x);		 
		    pDlg->SetDlgItemText(IDC_STATIC_OFFSETX,str);
		    str.Format(_T("%0.2f"),offset.y);		 
		    pDlg->SetDlgItemText(IDC_STATIC_OFFSETY,str);
            overcnt++;
		  if (overcnt > 300)   //小车速度40cm/min,突变容限21mm  平均处理图象时间20ms
		  {   
			  IplImage* tmpImage = NULL;
			  cvZero(pDlg->m_imageResult);
			  cvCvtColor(pImage,pDlg->m_imageResult,CV_GRAY2BGR);
			  cvSetImageROI(pDlg->m_imageResult,pDlg->m_drawRectTemp);
			  tmpImage = cvCreateImage(cvSize(pDlg->m_drawRectTemp.width,pDlg->m_drawRectTemp.height),8,3);  //显示之后问题  加的      
			  cvCopy(pDlg->m_imageResult,tmpImage,NULL);
			  cvSaveImage(pDlg->m_tempImageFile,tmpImage);
			  pDlg->ResizeImage(tmpImage);			
			  pDlg->ShowImage(pDlg->m_image,IDC_STATIC_TEMPIMAGE);
			  pDlg->m_tempImage = cvLoadImage(pDlg->m_tempImageFile,CV_LOAD_IMAGE_COLOR);
			  pDlg->Invalidate(FALSE);
			  cvResetImageROI(pDlg->m_imageResult);
			  cvReleaseImage(&tmpImage);
              overcnt=0;
		  }
		  else
		  {
			  continue;
		  }
	    }
		else
		{
	      overcnt = 0;
		}
        
		
        
        if (pDlg->m_UseG)
        {
         offset.x=0;
        }
		str.Format(_T("%0.2f"),score);		 
		pDlg->SetDlgItemText(IDC_STATIC_SCORE,str);
		str.Format(_T("%0.2f"),offset.x);		 
		pDlg->SetDlgItemText(IDC_STATIC_OFFSETX,str);
		str.Format(_T("%0.2f"),offset.y);		 
		pDlg->SetDlgItemText(IDC_STATIC_OFFSETY,str);
		pDlg->SetDlgItemInt(IDC_STATIC_TIME, 
					(int)((cvGetTickCount() - begin_count)/cvGetTickFrequency()/1000));
		pDlg->GetDlgItem(IDC_STATIC_TIME)->GetWindowText(str);

		cct[counter]=atoi(str);
        aax[counter]=offset.x;
		bby[counter]=offset.y;
		counter++;
		if (counter==6)
		{
 			for (uchar i=0;i<5;i++)
			{
 				aax[i]=aax[i+1];
				bby[i]=bby[i+1];
 				cct[i]=cct[i+1];
			}
			counter=5;
			if (pDlg->m_bAutoRun)
			{   
				offsety=PIDPro(1);    //PID
				offsetx=PIDPro(0);    //PID
				
				if(offsety > 0)
				{  
					if (diry!=1)
					{   
						ADM_StopMotion_M(DriverHandle,1);	
						diry=1;
					}
					ADM_CMove(DriverHandle,1,0);
					ADM_ChangePtPDV(DriverHandle,1,offsety);
				}
				else if (offsety < 0)
				{
					if (diry!=0)
					{   
						ADM_StopMotion_M(DriverHandle,1);	
						diry=0;
					}
					ADM_CMove(DriverHandle,1,1);
					ADM_ChangePtPDV(DriverHandle,1,-offsety);
				}
				else
				{
					diry=2;
					ADM_StopMotion_M(DriverHandle,1);
				}
				
				if (Weldtype==1)             //横缝 
				{
					if(offsetx > 0)
					{
						if (dir!=1)
						{
						  ADM_StopMotion_M(DriverHandle,0);	
						  dir=1;  
						}
						ADM_CMove(DriverHandle,0,0);	 
						ADM_ChangePtPDV(DriverHandle,0,offsetx);
					}
					else if (offsetx < 0)
					{
						if (dir!=0)
						{
                          ADM_StopMotion_M(DriverHandle,0);	
						  dir=0;	  
						}
						ADM_CMove(DriverHandle,0,1);
						ADM_ChangePtPDV(DriverHandle,0,-offsetx);
					}
					else
					{
						dir=2;
						ADM_StopMotion_M(DriverHandle,0);
					}	
					
				}
				else if (Weldtype==2)      //纵缝 
				{
					if(offsetx > 0)
					{
						ADM_CMove(DriverHandle,2,0);
						ADM_ChangePtPDV(DriverHandle,2,offsetx);
					}
					else if (offsetx < 0)
					{
						ADM_CMove(DriverHandle,2,1);
						ADM_ChangePtPDV(DriverHandle,2,-offsetx);
					}
					else
					{
						ADM_StopMotion_M(DriverHandle,2);
					}	
				}
			}
			else
			{  	
				SetEvent(pDlg->m_hTestThreadKillEvent);  //停止线程
				continue;
			}
		}
		
        VClearDrawGraph();
		VDrawRect(rect.x,
			rect.y,
			rect.x + pDlg->m_tempImage->width,
			rect.y + pDlg->m_tempImage->height,
			M_RGB888(0,255,0));
		//画感兴趣区域
		VDrawRectROI(pDlg->m_drawRectROI.x,
			pDlg->m_drawRectROI.y,
			pDlg->m_drawRectROI.x+pDlg->m_drawRectROI.width,
			pDlg->m_drawRectROI.y+pDlg->m_drawRectROI.height,
			M_RGB888(255,128,0));


		Sleep(10);	

	}   
	return 0L;
}

void CWeldDetectDlg::OnButtonTemp() 
{
	VCamSnapOneImage();
	m_nSetTemp = 1;
	
}
void CWeldDetectDlg::OnButtonStart() 
{
	if (m_start.m_State==bsdisable)
	{
		MessageBox("请先设置好模板!","系统提示",MB_OK);
		successrece=0;
		PurgeComm(hCom,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
		return;
	}
    m_info=_T("跟踪启动中...");
	UpdateData(FALSE);
	CWaitCursor wait;
    m_hTestThreadKillEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    m_pTestThread = AfxBeginThread(TestThread, this);
    m_pTestThread->m_bAutoDelete = false;
    m_pTestThread->ResumeThread();
	m_nSetTemp = 0;
	m_bStarting = true;
	
	m_start.m_State=bsDown;
	m_temp.m_State=bsdisable;
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TEMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_END)->EnableWindow(TRUE);
	m_end.m_State=bsNormal;
	Invalidate(TRUE);
}

void CWeldDetectDlg::OnButtonEnd() 
{
	OnButtonStop();
	CWaitCursor wait;
    SetEvent(m_hTestThreadKillEvent); 
    m_temp.m_State=bsNormal;
	m_start.m_State=bsNormal;
	m_end.m_State=bsdisable;
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TEMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_END)->EnableWindow(FALSE);
    m_bStarting = false;
	m_info=_T("系统准备好...");
	UpdateData(FALSE);
	Invalidate(TRUE);
}

void CWeldDetectDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//图像上的坐标与鼠标按下得到的坐标位置不同
	if (/*(m_bCalibration==false) &&*/m_nSetTemp==1)
	{   
	    //ScreenToClient( &point); 
		CWnd*  pWnd = ChildWindowFromPoint(point); 
		UINT  nCtrlID = pWnd->GetDlgCtrlID(); 
		if (nCtrlID!=IDC_STATIC_CONTINUEGRAB)
		{
			return;
		}
		m_rect.left = point.x-m_sizeContinueGrab.left;
		m_rect.top = point.y-m_sizeContinueGrab.top;
	    m_bDrawRect = true;
	}

	if (m_bCalibration)
	{
		m_nCalibration++;
		if(m_nCalibration>4)
		{
			MessageBox("已经标记了四个点了！","系统提示",MB_ICONINFORMATION | MB_OK);
			return;
		}
		//m_bCalibration = true;
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CWeldDetectDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//设置模板，并显示在界面上
	if (m_bDrawRect )
	{  
		//ScreenToClient( &point); 
		CWnd*  pWnd = ChildWindowFromPoint(point); 
		UINT  nCtrlID = pWnd->GetDlgCtrlID(); 
		if (nCtrlID!=IDC_STATIC_CONTINUEGRAB)
		{
			return;
		}
		if ((point.x-m_sizeContinueGrab.left) < m_rect.left)
		{
			MessageBox("请重新设置模板!","系统提示",MB_OK);
			return;
		}
		if((point.y-m_sizeContinueGrab.top) < m_rect.top)
		{
			MessageBox("请重新设置模板!","系统提示",MB_OK);
			return;
		}
		m_rect.right = point.x-m_sizeContinueGrab.left; 
		m_rect.bottom = point.y-m_sizeContinueGrab.top;
		
        if(m_rect.right==m_rect.left)
			return;
		if(m_rect.bottom==m_rect.top)
			return;

		m_drawRectTemp.x = m_rect.left;
		m_drawRectTemp.y = m_rect.top;
		m_drawRectTemp.height = m_rect.Height();
		m_drawRectTemp.width = m_rect.Width();

		m_drawRectROI.x = m_rect.left-m_roiWidthVariable;
		m_drawRectROI.y = m_rect.top-m_roiHightVariable;
		m_drawRectROI.height = m_rect.Height()+2*m_roiHightVariable;
		m_drawRectROI.width = m_rect.Width()+2*m_roiWidthVariable;
        m_info=_T("系统准备好...");
		 UpdateData(FALSE);
	
		CRect rect;
	    GetDlgItem(IDC_STATIC_CONTINUEGRAB) ->GetClientRect( &rect );
		if (m_drawRectROI.x < rect.left)
		{
			m_drawRectROI.x = rect.left+1;
		}
		if (m_drawRectROI.y < rect.top)
		{
			m_drawRectROI.y = rect.top+1;
		}
		if (m_drawRectROI.x + m_drawRectROI.width > rect.right)
		{
			m_drawRectROI.width = rect.right - m_drawRectROI.x-2;
		}
		if (m_drawRectROI.y + m_drawRectROI.height > rect.bottom)
		{
			m_drawRectROI.height = rect.bottom - m_drawRectROI.y-2;
		}

		//清除原有绘制图形
		VClearDrawGraph();
		//画模板矩形
		VDrawRect(m_drawRectTemp.x,
			m_drawRectTemp.y,
			m_drawRectTemp.x+m_drawRectTemp.width,
			m_drawRectTemp.y+m_drawRectTemp.height,
			M_RGB888(255,128,0));
		//画感兴趣区域
		VDrawRectROI(m_drawRectROI.x,
			m_drawRectROI.y,
			m_drawRectROI.x+m_drawRectROI.width,
			m_drawRectROI.y+m_drawRectROI.height,
			M_RGB888(255,128,0));

		IplImage* tmpImage = NULL;

		//保存模板
		//cvCopy(pImage,m_imageResult);
		cvCvtColor(pImage,m_imageResult,CV_GRAY2BGR);
		cvSetImageROI(m_imageResult,m_drawRectTemp);
		    tmpImage = cvCreateImage(cvSize(m_drawRectTemp.width,m_drawRectTemp.height),8,3);  //显示滞后问题  加的      
		cvCopy(m_imageResult,tmpImage,NULL);
		cvSaveImage(m_tempImageFile,tmpImage);
	    ResizeImage(tmpImage);			
		ShowImage(m_image,IDC_STATIC_TEMPIMAGE);
		m_tempImage = cvLoadImage(m_tempImageFile,CV_LOAD_IMAGE_COLOR);
		Invalidate(FALSE);
		cvResetImageROI(m_imageResult);
		cvReleaseImage(&tmpImage);
		m_modelPosition.x = m_drawRectTemp.x;
		m_modelPosition.y = m_drawRectTemp.y;
       m_tempx=m_modelPosition.x;
       m_tempy=m_modelPosition.y;
	   UpdateData(false);
		m_bDrawRect = false;
	  m_nSetTemp = 0;
		m_start.m_State=bsNormal;
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	}

	if (m_bCalibration&&(m_nCalibration == 1))
	{
		m_caliStartX = point.x;
	}
	if (m_bCalibration&&(m_nCalibration == 2))
	{
		m_caliEndX = point.x;
	}
	if (m_bCalibration&&(m_nCalibration == 3))
	{
		m_caliStartY = point.y;
	}
	if (m_bCalibration&&(m_nCalibration == 4))
	{
		m_caliEndY = point.y;
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CWeldDetectDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDrawRect)
	{
		m_rect.right = point.x-m_sizeContinueGrab.left; //图像上的坐标与鼠标按下得到的坐标位置不同
		m_rect.bottom = point.y-m_sizeContinueGrab.top;
		
		//清除原有绘制图形
		VClearDrawGraph();
		VDrawRect(m_rect.left,m_rect.top,m_rect.right,m_rect.bottom,M_RGB888(255,128,0));
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CWeldDetectDlg::OnMenuitemCalibration() 
{
	// TODO: Add your command handler code here
	m_nSetTemp=0;
	CPasswordDlg pDialog = new CPasswordDlg();
	while (pDialog.DoModal() == IDOK)
	{
		if (pDialog.m_password==PASSWORD)
		{
			CCalibrationDlg* dlg = new CCalibrationDlg();
			
			dlg->m_nResolutionX=m_resolutionX;
			dlg->m_nResolutionY=m_resolutionY;
			
			dlg->Create(CCalibrationDlg::IDD,this);
			dlg->ShowWindow(SW_SHOW);
			m_bCalibration = true;
	        m_nCalibration=0;
			return;

		}
		else
		{
			pDialog.m_password = "";
			MessageBox("请重新输入口令！","系统提示",MB_OK);
		}
	}
}

void CWeldDetectDlg::OnMenuitemParameter() 
{
	// TODO: Add your command handler code here
	CPasswordDlg pDialog = new CPasswordDlg();
	while (pDialog.DoModal() == IDOK)
	{
		if (pDialog.m_password==PASSWORD)
		{
			CParameterDlg dlg;
			CString str, strKey, strPassApp;
			
			if (dlg.DoModal() != IDOK )return;
			
			m_score = dlg.m_dScore;
			m_roiWidthVariable = dlg.m_roiX;
			m_roiHightVariable = dlg.m_roiY;
			
			strPassApp = "参数设置";
			
			strKey = "水平扩展";
			str.Format("%d", m_roiWidthVariable);	
			WritePrivateProfileString(strPassApp, strKey, str, m_strFilePath);	
			strKey = "垂直扩展";
			str.Format("%d", m_roiHightVariable);	
			WritePrivateProfileString(strPassApp, strKey, str, m_strFilePath);
			
			strKey = "匹配度";
			str.Format("%0.2f", m_score);	
			WritePrivateProfileString(strPassApp, strKey, str, m_strFilePath);
	        delete dlg;

			return;
			
		}
		else
		{
			pDialog.m_password = "";
			MessageBox("请重新输入口令！","系统提示",MB_OK);
		}		
	}
}

void CWeldDetectDlg::OnMenuitemHistory() 
{
	// TODO: Add your command handler code here
	CHistoryDlg dlg;
	dlg.DoModal();
}


void CWeldDetectDlg::OnMenuitemExit() 
{
	CloseHandle(hCom);
	VCamStopCapture();
	ADM_CloseDevice(&DriverHandle);
//  VCamRelease();
//  cvReleaseImage(&pImage);
	OnCancel();   
}

/**************************************************************************
*  OnButtonUp()
*
*  功能:
*    手动移动电机向上运动
*
*  参数:
*
*  返回:
*    
**************************************************************************/
void CWeldDetectDlg::OnButtonUp() 
{
	if (m_bStarting)
	{
		m_bStarting=false;
		m_bAutoRun=false;
		m_start.m_State=bsNormal;
		m_end.m_State=bsdisable;
		shoudong=1;
		Invalidate(TRUE);
	}
	ADM_CMove(DriverHandle,1,1);
    ADM_ChangePtPDV(DriverHandle,1,JOGSPEED);

}

/**************************************************************************
*  OnButtonLeft()
*
*  功能:
*    手动移动电机向左运动
*
*  参数:
*
*  返回:
*    
**************************************************************************/
void CWeldDetectDlg::OnButtonLeft() 
{
  	if (m_bStarting)
	{
	  m_bStarting=false;
	  m_bAutoRun=false;
	  m_start.m_State=bsNormal;
	  m_end.m_State=bsdisable;
	  shoudong=1;
	  Invalidate(TRUE);
	}	       //遥控	
  	ADM_CMove(DriverHandle,0,0);
    ADM_ChangePtPDV(DriverHandle,0,JOGSPEED);
}

/**************************************************************************
*  OnButtonRight()
*
*  功能:
*    手动移动电机向右运动
*
*  参数:
*
*  返回:
*    
**************************************************************************/
void CWeldDetectDlg::OnButtonRight() 
{
	if (m_bStarting)
	{
		m_bStarting=false;
		m_bAutoRun=false;
		m_start.m_State=bsNormal;
		m_end.m_State=bsdisable;
		shoudong=1;
		Invalidate(TRUE);
	}
	ADM_CMove(DriverHandle,0,1);
    ADM_ChangePtPDV(DriverHandle,0,JOGSPEED);
}

/**************************************************************************
*  OnButtonDown()
*
*  功能:
*    手动移动电机向下运动
*
*  参数:
*
*  返回:
*    
**************************************************************************/
void CWeldDetectDlg::OnButtonDown() 
{
    if (m_bStarting)
	{
		m_bStarting=false;
		m_bAutoRun=false;
		m_start.m_State=bsNormal;
		m_end.m_State=bsdisable;
		shoudong=1;
		Invalidate(TRUE);
	}                                   //遥控
	ADM_CMove(DriverHandle,1,0);
    ADM_ChangePtPDV(DriverHandle,1,JOGSPEED);                                //第三个参数--方向  0--正向 1--负向
}

void CWeldDetectDlg::OnButtonStop() 
{
	CString str;
	ADM_StopMotion_S(DriverHandle,0);
    ADM_StopMotion_S(DriverHandle,1);
	if (!m_bAutoRun)
	{      
		shoudong=0;
		m_bAutoRun = true;   
		rerecord();
		OnButtonStart();	
		str.Format(_T("%.f"),0);		 
		SetDlgItemText(IDC_STATIC_OFFSETX,str);
		str.Format(_T("%.f"),0);		 
		SetDlgItemText(IDC_STATIC_OFFSETY,str);
	}
}

BOOL CWeldDetectDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( m_UseKey ) 
	{
		if ( pMsg->message == WM_KEYDOWN )
		{			
			switch(pMsg->wParam)
			{
			case VK_UP:
				if (m_nSetTemp == 1)                                            //移动摸板
				{
					m_drawRectTemp.y = m_drawRectTemp.y - 5;				
					m_drawRectROI.y = m_drawRectTemp.y-m_roiHightVariable;
					
				                                                             	//判断检测区域的范围
					if (m_drawRectROI.y < m_sizeContinueGrab.top)
					{
						m_drawRectROI.y = m_sizeContinueGrab.top+1;
					}				
					if (m_drawRectTemp.y < m_sizeContinueGrab.top)
					{
						m_drawRectTemp.y = m_sizeContinueGrab.top+1;
					}
					
					                                                           //清除原有绘制图形
					VClearDrawGraph();
				                                                               //画模板矩形
					VDrawRect(m_drawRectTemp.x,
						m_drawRectTemp.y,
						m_drawRectTemp.x+m_drawRectTemp.width,
						m_drawRectTemp.y+m_drawRectTemp.height,
						M_RGB888(255,128,0));
					//画感兴趣区域
					VDrawRectROI(m_drawRectROI.x,
						m_drawRectROI.y,
						m_drawRectROI.x+m_drawRectROI.width,
						m_drawRectROI.y+m_drawRectROI.height,
			         	M_RGB888(255,128,0));
				}
				else                                                           //移动电机
				{
				 if (m_bStarting)
				 {
					 m_bAutoRun=false;
					 m_bStarting=false;
					 //MotionJog(2,-1);
					 //StartMotion(DriverHandle,1,1);
					 //ChangeSpeed(DriverHandle,1,10000);
					  ADM_CMove(DriverHandle,1,1);
					  ADM_ChangePtPDV(DriverHandle,1,10000);
				 }
				                                                  //遥控
				}				
				pMsg->wParam = NULL;
				break;
			case VK_DOWN:
				if (m_nSetTemp==1)
				{
					m_drawRectTemp.y = m_drawRectTemp.y + 5;				
					m_drawRectROI.y = m_drawRectTemp.y-m_roiHightVariable;
					
					//判断检测区域的范围
					if (m_drawRectROI.y + m_drawRectROI.height > m_sizeContinueGrab.bottom)
					{
						m_drawRectROI.height = m_sizeContinueGrab.bottom - m_drawRectROI.y - 2;
					}
					if (m_drawRectTemp.y + m_drawRectTemp.height > m_sizeContinueGrab.bottom)
					{
						m_drawRectTemp.height = m_sizeContinueGrab.bottom - m_drawRectTemp.y - 2;
					}
					
					//清除原有绘制图形
					VClearDrawGraph();
					//画模板矩形
					VDrawRect(m_drawRectTemp.x,
						m_drawRectTemp.y,
						m_drawRectTemp.x+m_drawRectTemp.width,
						m_drawRectTemp.y+m_drawRectTemp.height,
						M_RGB888(255,128,0));
					//画感兴趣区域
					VDrawRectROI(m_drawRectROI.x,
						m_drawRectROI.y,
						m_drawRectROI.x+m_drawRectROI.width,
						m_drawRectROI.y+m_drawRectROI.height,
				        M_RGB888(255,128,0));
				}
				else
				{
					if (m_bStarting)
					{
						m_bAutoRun=false;
						m_bStarting=false;
						//MotionJog(2,1);
						//StartMotion(DriverHandle,1,0);
						//ChangeSpeed(DriverHandle,1,10000);
                        ADM_CMove(DriverHandle,1,0);
					    ADM_ChangePtPDV(DriverHandle,1,10000);
					}
				}
				
				pMsg->wParam = NULL;
				break;
			case VK_LEFT:
				if (m_nSetTemp==1)
				{
					m_drawRectTemp.x = m_drawRectTemp.x-5;
					m_drawRectROI.x = m_drawRectTemp.x-m_roiWidthVariable;
					
					//判断检测区域的范围
					if (m_drawRectTemp.x < m_sizeContinueGrab.left)
					{
						m_drawRectTemp.x = m_sizeContinueGrab.left+1;
					}
					
					if (m_drawRectROI.x < m_sizeContinueGrab.left)
					{
						m_drawRectROI.x = m_sizeContinueGrab.left+1;
					}
					
					//清除原有绘制图形
					VClearDrawGraph();
					//画模板矩形
					VDrawRect(m_drawRectTemp.x,
						m_drawRectTemp.y,
						m_drawRectTemp.x+m_drawRectTemp.width,
						m_drawRectTemp.y+m_drawRectTemp.height,
						M_RGB888(255,128,0));
					//画感兴趣区域
					VDrawRectROI(m_drawRectROI.x,
						m_drawRectROI.y,
						m_drawRectROI.x+m_drawRectROI.width,
						m_drawRectROI.y+m_drawRectROI.height,
				        M_RGB888(255,128,0));
				}
				else
				{
					if (m_bStarting)
					{
			 		m_bAutoRun=false;
					m_bStarting=false;
					//MotionJog(1,1);
					//StartMotion(DriverHandle,0,0);
					//ChangeSpeed(DriverHandle,0,10000);
					 ADM_CMove(DriverHandle,0,0);
					 ADM_ChangePtPDV(DriverHandle,0,10000);
					}
				}
				
				pMsg->wParam = NULL;
				break;
			case VK_RIGHT:
				if (m_nSetTemp==1)
				{
					m_drawRectTemp.x = m_drawRectTemp.x+5;
					m_drawRectROI.x = m_drawRectTemp.x-m_roiWidthVariable;
					
					//判断检测区域的范围
					if (m_drawRectTemp.x + m_drawRectTemp.width > m_sizeContinueGrab.right)
					{
						m_drawRectTemp.width = m_sizeContinueGrab.right - m_drawRectTemp.x - 2;
					}
					if (m_drawRectROI.x + m_drawRectROI.width > m_sizeContinueGrab.right)
					{
						m_drawRectROI.width = m_sizeContinueGrab.right - m_drawRectROI.x - 2;
					}
					
					//清除原有绘制图形
					VClearDrawGraph();
					//画模板矩形
					VDrawRect(m_drawRectTemp.x,
						m_drawRectTemp.y,
						m_drawRectTemp.x+m_drawRectTemp.width,
						m_drawRectTemp.y+m_drawRectTemp.height,
						M_RGB888(255,128,0));
					//画感兴趣区域
					VDrawRectROI(m_drawRectROI.x,
						m_drawRectROI.y,
						m_drawRectROI.x+m_drawRectROI.width,
						m_drawRectROI.y+m_drawRectROI.height,
				        M_RGB888(255,128,0));
				}
				else
				{
					if (m_bStarting)
					{
						m_bAutoRun=false;
						m_bStarting=false;
						//MotionJog(1,-1);
						//StartMotion(DriverHandle,0,1);
						//ChangeSpeed(DriverHandle,0,10000);
						ADM_CMove(DriverHandle,0,1);
					    ADM_ChangePtPDV(DriverHandle,0,10000);
					}
				
				}
				pMsg->wParam = NULL;
				break;

			case VK_F2:
				//结束
				
				OnButtonEnd();
				pMsg->wParam = NULL;
				break;

			default:
				break;
			}				
		}
		
		if  ( pMsg->message == WM_KEYUP )
		{
		
			switch(pMsg->wParam)
				{
				case VK_UP:
					if (!m_bAutoRun)
					{      
					//MotionStop(2);
					//StopMotion(DriverHandle,1,0);
					ADM_StopMotion_S(DriverHandle,1);
					m_bAutoRun = true;   
					IplImage* tmpImage = NULL;
					
					//保存模板
					//cvCopy(pImage,m_imageResult);
					cvZero(m_imageResult);
						 cvCvtColor(pImage,m_imageResult,CV_GRAY2BGR);
					cvSetImageROI(m_imageResult,m_drawRectTemp);
					tmpImage = cvCreateImage(cvSize(m_drawRectTemp.width,m_drawRectTemp.height),8,3);  //显示之后问题  加的      
					cvCopy(m_imageResult,tmpImage,NULL);
					cvSaveImage(m_tempImageFile,tmpImage);
					ResizeImage(tmpImage);			
					ShowImage(m_image,IDC_STATIC_TEMPIMAGE);
					m_tempImage = cvLoadImage(m_tempImageFile,CV_LOAD_IMAGE_COLOR);
					Invalidate(FALSE);
					cvResetImageROI(m_imageResult);
	             	cvReleaseImage(&tmpImage);
                    OnButtonStart();	  
					}
		           //遥控
				pMsg->wParam = NULL;
				break;
			case VK_DOWN:
				if (!m_bAutoRun)
				{ 
				    //MotionStop(2);
					//StopMotion(DriverHandle,1,0);
					ADM_StopMotion_S(DriverHandle,1);
					m_bAutoRun = true;
			    	IplImage* tmpImage = NULL;
					
					//保存模板
					//cvCopy(pImage,m_imageResult);
					cvZero(m_imageResult);	
						cvCvtColor(pImage,m_imageResult,CV_GRAY2BGR);
					cvSetImageROI(m_imageResult,m_drawRectTemp);
					tmpImage = cvCreateImage(cvSize(m_drawRectTemp.width,m_drawRectTemp.height),8,3);  //显示之后问题  加的      
					cvCopy(m_imageResult,tmpImage,NULL);
					cvSaveImage(m_tempImageFile,tmpImage);
					ResizeImage(tmpImage);			
					ShowImage(m_image,IDC_STATIC_TEMPIMAGE);
					m_tempImage = cvLoadImage(m_tempImageFile,CV_LOAD_IMAGE_COLOR);
					Invalidate(FALSE);
					cvResetImageROI(m_imageResult);
					cvReleaseImage(&tmpImage);
					OnButtonStart();
					//ResumeThread(m_pTestThread);
                   
				}
				pMsg->wParam = NULL;
				break;
			case VK_LEFT:
				if (!m_bAutoRun )
				{	
				    //MotionStop(1);
					//StopMotion(DriverHandle,0,0);
					ADM_StopMotion_S(DriverHandle,0);
					m_bAutoRun = true;
					IplImage* tmpImage = NULL;
					
					//保存模板
					//cvCopy(pImage,m_imageResult);
					cvZero(m_imageResult);	
						cvCvtColor(pImage,m_imageResult,CV_GRAY2BGR);
					cvSetImageROI(m_imageResult,m_drawRectTemp);
					tmpImage = cvCreateImage(cvSize(m_drawRectTemp.width,m_drawRectTemp.height),8,3);  //显示之后问题  加的      
					cvCopy(m_imageResult,tmpImage,NULL);
					cvSaveImage(m_tempImageFile,tmpImage);
					ResizeImage(tmpImage);			
					ShowImage(m_image,IDC_STATIC_TEMPIMAGE);
					m_tempImage = cvLoadImage(m_tempImageFile,CV_LOAD_IMAGE_COLOR);
					Invalidate(FALSE);
					cvResetImageROI(m_imageResult);
					cvReleaseImage(&tmpImage);
					OnButtonStart();
					//ResumeThread(m_pTestThread);
                   
				}
				pMsg->wParam = NULL;
				break;
			case VK_RIGHT:
				if (!m_bAutoRun )
				{
					//MotionStop(1);
					//StopMotion(DriverHandle,0,0);
					ADM_StopMotion_S(DriverHandle,0);
					m_bAutoRun = true;
					//MotionGetPosition(0,&m_endPosAxis0);
					
					
					IplImage* tmpImage = NULL;
					
					//保存模板
					//cvCopy(pImage,m_imageResult);
					cvZero(m_imageResult);
					cvCvtColor(pImage,m_imageResult,CV_GRAY2BGR);
					cvSetImageROI(m_imageResult,m_drawRectTemp);
					tmpImage = cvCreateImage(cvSize(m_drawRectTemp.width,m_drawRectTemp.height),8,3);  //显示之后问题  加的      
					cvCopy(m_imageResult,tmpImage,NULL);
					cvSaveImage(m_tempImageFile,tmpImage);
					ResizeImage(tmpImage);			
					ShowImage(m_image,IDC_STATIC_TEMPIMAGE);
					m_tempImage = cvLoadImage(m_tempImageFile,CV_LOAD_IMAGE_COLOR);
					Invalidate(FALSE);
					cvResetImageROI(m_imageResult);
					cvReleaseImage(&tmpImage);
					OnButtonStart();
					//ResumeThread(m_pTestThread);
            
				}
				pMsg->wParam = NULL;
				break;
			default:
				break;
			}	
		}
	

		if (pMsg->wParam == VK_F8 && pMsg->message == WM_KEYDOWN)			
		{
			//自动画框
			m_nSetTemp = 1;

			m_drawRectTemp.x = m_sizeContinueGrab.left + m_widthGrabControl/2 - WIDTH_TEMP/2;
			m_drawRectTemp.y = m_sizeContinueGrab.top + m_heightGrabControl/2 - HEIGHT_TEMP/2;
			m_drawRectTemp.height = HEIGHT_TEMP;
			m_drawRectTemp.width = WIDTH_TEMP;
			
			m_drawRectROI.x = m_drawRectTemp.x-m_roiWidthVariable;
			m_drawRectROI.y = m_drawRectTemp.y-m_roiHightVariable;
			m_drawRectROI.height = HEIGHT_TEMP+2*m_roiHightVariable;
			m_drawRectROI.width = WIDTH_TEMP+2*m_roiWidthVariable;
			
			//判断检测区域的范围
			if (m_drawRectROI.x < m_sizeContinueGrab.left)
			{
				m_drawRectROI.x = m_sizeContinueGrab.left+1;
			}
			if (m_drawRectROI.y < m_sizeContinueGrab.top)
			{
				m_drawRectROI.y = m_sizeContinueGrab.top+1;
			}
			if (m_drawRectROI.x + m_drawRectROI.width > m_sizeContinueGrab.right)
			{
				m_drawRectROI.width = m_sizeContinueGrab.right - m_drawRectROI.x - 2;
			}
			if (m_drawRectROI.y + m_drawRectROI.height > m_sizeContinueGrab.bottom)
			{
				m_drawRectROI.height = m_sizeContinueGrab.bottom - m_drawRectROI.y - 2;
			}
			
			//清除原有绘制图形
			VClearDrawGraph();
			//画模板矩形
			VDrawRect(m_drawRectTemp.x,
				m_drawRectTemp.y,
				m_drawRectTemp.x+m_drawRectTemp.width,
				m_drawRectTemp.y+m_drawRectTemp.height,
				M_RGB888(255,128,0));
			//画感兴趣区域
			VDrawRectROI(m_drawRectROI.x,
				m_drawRectROI.y,
				m_drawRectROI.x+m_drawRectROI.width,
				m_drawRectROI.y+m_drawRectROI.height,
				M_RGB888(255,128,0));
		
	        UpdateData(false);
			pMsg->wParam = NULL;
		}
		
	
		if (pMsg->wParam == VK_F3 && pMsg->message == WM_KEYDOWN )			
		{  
			if(m_bStarting)
				return 0L;
			OnButtonStart();
			Invalidate(TRUE);
			pMsg->wParam = NULL;
		}

		if (pMsg->wParam == VK_F4 && pMsg->message == WM_KEYDOWN )			
		{
			
			m_drawRectTemp.y = m_drawRectTemp.y - 5;
			m_drawRectTemp.height = m_drawRectTemp.height+2*5;
			
			m_drawRectROI.y = m_drawRectTemp.y-m_roiHightVariable;
			m_drawRectROI.height = m_drawRectTemp.height+2*m_roiHightVariable;
			
			//判断检测区域的范围
			if (m_drawRectROI.y < m_sizeContinueGrab.top)
			{
				m_drawRectROI.y = m_sizeContinueGrab.top+1;
			}
			if (m_drawRectROI.y + m_drawRectROI.height > m_sizeContinueGrab.bottom)
			{
				m_drawRectROI.height = m_sizeContinueGrab.bottom - m_drawRectROI.y - 2;
			}

			if (m_drawRectTemp.y < m_sizeContinueGrab.top)
			{
				m_drawRectTemp.y = m_sizeContinueGrab.top+1;
			}
			if (m_drawRectTemp.y + m_drawRectTemp.height > m_sizeContinueGrab.bottom)
			{
				m_drawRectTemp.height = m_sizeContinueGrab.bottom - m_drawRectTemp.y - 2;
			}
			
			//清除原有绘制图形
			VClearDrawGraph();
			//画模板矩形
			VDrawRect(m_drawRectTemp.x,
				m_drawRectTemp.y,
				m_drawRectTemp.x+m_drawRectTemp.width,
				m_drawRectTemp.y+m_drawRectTemp.height,
				M_RGB888(255,128,0));
			//画感兴趣区域
			VDrawRectROI(m_drawRectROI.x,
				m_drawRectROI.y,
				m_drawRectROI.x+m_drawRectROI.width,
				m_drawRectROI.y+m_drawRectROI.height,
				M_RGB888(255,128,0));
			pMsg->wParam = NULL;
		}

		if (pMsg->wParam == VK_F6 )			
		{
			
			m_drawRectTemp.x = m_drawRectTemp.x-5;
			m_drawRectTemp.width = m_drawRectTemp.width+2*5;
			
			m_drawRectROI.x = m_drawRectTemp.x-m_roiWidthVariable;
			m_drawRectROI.width = m_drawRectTemp.width+2*m_roiWidthVariable;
			
			//判断检测区域的范围
			if (m_drawRectTemp.x < m_sizeContinueGrab.left)
			{
				m_drawRectTemp.x = m_sizeContinueGrab.left+1;
			}
			if (m_drawRectTemp.x + m_drawRectTemp.width > m_sizeContinueGrab.right)
			{
				m_drawRectTemp.width = m_sizeContinueGrab.right - m_drawRectTemp.x - 2;
			}

			if (m_drawRectROI.x < m_sizeContinueGrab.left)
			{
				m_drawRectROI.x = m_sizeContinueGrab.left+1;
			}
			if (m_drawRectROI.x + m_drawRectROI.width > m_sizeContinueGrab.right)
			{
				m_drawRectROI.width = m_sizeContinueGrab.right - m_drawRectROI.x - 2;
			}
			
			//清除原有绘制图形
			VClearDrawGraph();
			//画模板矩形
			VDrawRect(m_drawRectTemp.x,
				m_drawRectTemp.y,
				m_drawRectTemp.x+m_drawRectTemp.width,
				m_drawRectTemp.y+m_drawRectTemp.height,
				M_RGB888(255,128,0));
			//画感兴趣区域
			VDrawRectROI(m_drawRectROI.x,
				m_drawRectROI.y,
				m_drawRectROI.x+m_drawRectROI.width,
				m_drawRectROI.y+m_drawRectROI.height,
				M_RGB888(255,128,0));

			pMsg->wParam = NULL;
		}

	
		if (pMsg->wParam == VK_F7 && pMsg->message == WM_KEYDOWN )			
		{  
			if(m_bStarting)
				return 0L;
		//	VCamStopCapture();
			VCamSnapOneImage();
	    //  VCamStartCapture(0);
			IplImage* tmpImage = NULL;
			
			//保存模板
			//cvCopy(pImage,m_imageResult);
			cvCvtColor(pImage,m_imageResult,CV_GRAY2BGR);
			cvSetImageROI(m_imageResult,m_drawRectTemp);
			tmpImage = cvCreateImage(cvSize(m_drawRectTemp.width,m_drawRectTemp.height),8,3);        
			cvCopy(m_imageResult,tmpImage,NULL);
			cvSaveImage(m_tempImageFile,tmpImage);
			ResizeImage(tmpImage);			
			ShowImage(m_image,IDC_STATIC_TEMPIMAGE);
			Invalidate(FALSE);
			cvResetImageROI(m_imageResult);
			cvReleaseImage(&tmpImage);
			m_modelPosition.x = m_drawRectTemp.x;
			m_modelPosition.y = m_drawRectTemp.y;
			m_tempx=m_modelPosition.x;
			m_tempy=m_modelPosition.y;
			UpdateData(false);
			m_start.m_State=bsNormal;
			GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			m_nSetTemp = 0;
			
			pMsg->wParam = NULL;
		}

		if (pMsg->wParam == VK_F9 && pMsg->message == WM_KEYDOWN )			
		{
			OnMenuitemExit();
			pMsg->wParam = NULL;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CWeldDetectDlg::OnCheckKey() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

HBRUSH CWeldDetectDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
   CFont myfont;
   myfont.CreateFont(
   45,                        // nHeight
   0,                         // nWidth
   0,                         // nEscapement
   0,                         // nOrientation
   800,//FW_NORMAL,                 // nWeight
   FALSE,                     // bItalic
   FALSE,                     // bUnderline
   0,                         // cStrikeOut
   ANSI_CHARSET,              // nCharSet
   OUT_DEFAULT_PRECIS,        // nOutPrecision
   CLIP_DEFAULT_PRECIS,       // nClipPrecision
   DEFAULT_QUALITY,           // nQuality
   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
   "Arial");                 // lpszFacename

    if(pWnd->GetDlgCtrlID()==IDC_EDIT_U)      //改变静态框文本字体
	{
		pDC->SelectObject(&myfont);
		pDC->SetTextColor(RGB(255,0,0));
	}	
    if(pWnd->GetDlgCtrlID()==IDC_EDIT_I)
	{
		pDC->SelectObject(&myfont);
		pDC->SetTextColor(RGB(255,0,0));
	}
	if(pWnd->GetDlgCtrlID()==IDC_EDIT_V)
	{
		pDC->SelectObject(&myfont);
		pDC->SetTextColor(RGB(255,0,0));
	}
	return hbr;
}

LRESULT CWeldDetectDlg::jitouchuli(WPARAM wparam,LPARAM lparam)
{
if (lpBuffer[4]==0x01)
   {
	  if (m_bStarting)
	  {
		m_bStarting=false;
		m_bAutoRun=false;
		m_bAutoRunx=false;
		m_start.m_State=bsNormal;
	    m_end.m_State=bsdisable;
		Invalidate(FALSE);
	  }	
	  ADM_CMove(DriverHandle,0,0);
      ADM_ChangePtPDV(DriverHandle,0,JOGSPEED); 
	}
   else if (lpBuffer[4]==0x02)
   {
	  if (m_bStarting)
	  {
		m_bStarting=false;
		m_bAutoRun=false;
		m_bAutoRunx=false;
		m_start.m_State=bsNormal;
		m_end.m_State=bsdisable;
		Invalidate(FALSE);
	  }	
	  ADM_CMove(DriverHandle,0,1);
      ADM_ChangePtPDV(DriverHandle,0,JOGSPEED); 
   } 
   else 
   {
	  ADM_StopMotion_M(DriverHandle,0);
	if (!m_bAutoRunx)
	{      
	
		m_bAutoRun = true; 
		m_bAutoRunx = true; 
	    rerecord();
		OnButtonStart();	
	}
   }

  if (lpBuffer[5]==0x01)
  {
     if (m_bStarting)
	  {
		m_bStarting=false;
		m_bAutoRun=false;
		m_bAutoRuny=false;
		m_start.m_State=bsNormal;
		m_end.m_State=bsdisable;
		Invalidate(FALSE);
	  }	
	  ADM_CMove(DriverHandle,1,0);
      ADM_ChangePtPDV(DriverHandle,1,JOGSPEED); 
  }
  else if (lpBuffer[5]==0x02)
  {
	 if (m_bStarting)
	  {
		m_bStarting=false;
		m_bAutoRun=false;
		m_bAutoRuny=false;
		m_start.m_State=bsNormal;
		m_end.m_State=bsdisable;
		Invalidate(FALSE);
	  }	
	  ADM_CMove(DriverHandle,1,1);
      ADM_ChangePtPDV(DriverHandle,1,JOGSPEED); 
  } 
 else 
 {
	 ADM_StopMotion_M(DriverHandle,1);
	if (!m_bAutoRuny)
	{      
		
		m_bAutoRun = true; 
		m_bAutoRuny = true; 
		rerecord();
		OnButtonStart();	  
	} 
 }
 
 if (lpBuffer[6]==0x01)
 {
	 if (m_bStarting)
	 {
		 m_bStarting=false;
		 m_bAutoRun=false;
		 m_bAutoRunz=false;
		 m_start.m_State=bsNormal;
		 m_end.m_State=bsdisable;
		Invalidate(FALSE);
	  }	
	 ADM_CMove(DriverHandle,2,0);
     ADM_ChangePtPDV(DriverHandle,2,JOGSPEED); 
 }
 else if (lpBuffer[6]==0x02)
 {
     if (m_bStarting)
	  {
		m_bStarting=false;
		m_bAutoRun=false;
		m_bAutoRunz=false;
		m_start.m_State=bsNormal;
		m_end.m_State=bsdisable;
		Invalidate(FALSE);
	  }	
	  ADM_CMove(DriverHandle,2,1);
      ADM_ChangePtPDV(DriverHandle,2,JOGSPEED); 
 } 
 else 
 {
	 ADM_StopMotion_M(DriverHandle,2);
	if (!m_bAutoRunz)
	{      
		
		m_bAutoRun = true;  
		m_bAutoRunz = true; 
	    rerecord();
		OnButtonStart();	  
	}
 }
 return 0;
}

void CWeldDetectDlg::OnCheckG() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CWeldDetectDlg::rerecord()
{
	if (m_start.m_State==bsdisable)
	{
		MessageBox("请先设置好模板!","系统提示",MB_OK);
		//successrece=0;
		return;
	}
	IplImage* tmpImage = NULL;
	cvZero(m_imageResult);
	cvCvtColor(pImage,m_imageResult,CV_GRAY2BGR);
	cvSetImageROI(m_imageResult,m_drawRectTemp);
	tmpImage = cvCreateImage(cvSize(m_drawRectTemp.width,m_drawRectTemp.height),8,3);  //显示之后问题  加的      
	cvCopy(m_imageResult,tmpImage,NULL);
	cvSaveImage(m_tempImageFile,tmpImage);
	ResizeImage(tmpImage);			
	ShowImage(m_image,IDC_STATIC_TEMPIMAGE);
	m_tempImage = cvLoadImage(m_tempImageFile,CV_LOAD_IMAGE_COLOR);
	Invalidate(FALSE);
	cvResetImageROI(m_imageResult);
	cvReleaseImage(&tmpImage);
}
