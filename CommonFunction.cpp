#include "StdAfx.h"


#define  MAX_LEN   1000      

//////////////////////////////// 罗杨 /////////////////////////////////////////////

BOOL  My_WriteProfileString(const CString strSection, const CString strEntry, 
						 const CString strValue, CString  strIniPath)
{
	BOOL bValue;
	bValue = WritePrivateProfileString(strSection, strEntry, strValue, strIniPath);
	return bValue;
}

CString My_GetProfileString(const CString strSection, const CString strEntry, 
						 const CString strDefault,	CString  strIniPath)
{
	CString strValue;
	char szBuffer[MAX_LEN];

	GetPrivateProfileString(strSection, strEntry, strDefault, szBuffer, MAX_LEN, strIniPath);
	strValue.Format("%s", szBuffer);

	return strValue;
}

BOOL  My_WriteProfileInt(const CString strSection, const CString strEntry, 
					  const int nValue,	CString  strIniPath)
{
	////代码同WriteProfileString相似。
	////只需将int iValue转成CString strValue
	////使用函数：wchar_t * _itow( int value, wchar_t *string, int radix );
	
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	return My_WriteProfileString(strSection, strEntry, strValue, strIniPath);
} 


int  My_GetProfileInt(const CString strSection, const CString strEntry, 
				   const int nDefault,	CString  strIniPath)
{
	////代码同GetProfileString相似。
	////只需将得到的CString类型转换成int型
	////使用函数：int _wtoi( const wchar_t *string );
	CString strDefault;
	int nResult;

	itoa(nDefault, strDefault.GetBuffer(100), 10);
	nResult = atoi(My_GetProfileString(strSection, strEntry, strDefault, strIniPath));

	return nResult; 
}  

BOOL  My_WriteProfileDouble(const CString strSection, const CString strEntry, 
						const double dValue, CString  strIniPath)
{
	////代码同WriteProfileString相似。
	////只需将int iValue转成CString strValue
	////使用函数：wchar_t * _itow( int value, wchar_t *string, int radix );
	
	CString strValue;
	strValue.Format(_T("%f"),dValue);
	
	return My_WriteProfileString(strSection, strEntry, strValue, strIniPath);
} 

double My_GetProfileDouble(const CString strSection, const CString strEntry, 
					   const double dDefault, CString  strIniPath)
{
	////代码同GetProfileString相似。
	////只需将得到的CString类型转换成int型
	////使用函数：int _wtoi( const wchar_t *string );

	CString strDefault;
	double dResult;

	strDefault.Format(_T("%f"), dDefault);

	char* temp;
	dResult = strtod(My_GetProfileString(strSection, strEntry, strDefault, strIniPath), &temp);	

	return dResult; 
}  


//┏━━━━━━━━━━━━━━━<GetFilePath>━━━━━━━━━━━━━━━
//┃返回值 : CString	可执行文件的全路径
//┃函数说明 : 取得可执行文件的全路径(不包括文件名)的上一层目录
//┃
//┗━━━━━━━━━━━━━━━[GetFilePath]━━━━━━━━━━━━━━━
CString GetFilePath()
{
	TCHAR exeFullPath[100];
	GetModuleFileName(NULL, exeFullPath, 100);
	CString strPath;
	strPath = exeFullPath;
	
	int i = 0, nTemp = 0;

	for(i = 0; i <= strPath.GetLength(); i ++)
	{	
		if("\\" == strPath.Mid(i, 1))
			nTemp = i;
	}

	strPath = strPath.Left(nTemp);
	

	for(i = 0; i <= strPath.GetLength(); i ++)
	{	
		if("\\" == strPath.Mid(i, 1))
			nTemp = i;
	}

	strPath = strPath.Left(nTemp + 1);

	return strPath;
}







	

