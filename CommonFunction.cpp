#include "StdAfx.h"


#define  MAX_LEN   1000      

//////////////////////////////// ���� /////////////////////////////////////////////

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
	////����ͬWriteProfileString���ơ�
	////ֻ�轫int iValueת��CString strValue
	////ʹ�ú�����wchar_t * _itow( int value, wchar_t *string, int radix );
	
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	return My_WriteProfileString(strSection, strEntry, strValue, strIniPath);
} 


int  My_GetProfileInt(const CString strSection, const CString strEntry, 
				   const int nDefault,	CString  strIniPath)
{
	////����ͬGetProfileString���ơ�
	////ֻ�轫�õ���CString����ת����int��
	////ʹ�ú�����int _wtoi( const wchar_t *string );
	CString strDefault;
	int nResult;

	itoa(nDefault, strDefault.GetBuffer(100), 10);
	nResult = atoi(My_GetProfileString(strSection, strEntry, strDefault, strIniPath));

	return nResult; 
}  

BOOL  My_WriteProfileDouble(const CString strSection, const CString strEntry, 
						const double dValue, CString  strIniPath)
{
	////����ͬWriteProfileString���ơ�
	////ֻ�轫int iValueת��CString strValue
	////ʹ�ú�����wchar_t * _itow( int value, wchar_t *string, int radix );
	
	CString strValue;
	strValue.Format(_T("%f"),dValue);
	
	return My_WriteProfileString(strSection, strEntry, strValue, strIniPath);
} 

double My_GetProfileDouble(const CString strSection, const CString strEntry, 
					   const double dDefault, CString  strIniPath)
{
	////����ͬGetProfileString���ơ�
	////ֻ�轫�õ���CString����ת����int��
	////ʹ�ú�����int _wtoi( const wchar_t *string );

	CString strDefault;
	double dResult;

	strDefault.Format(_T("%f"), dDefault);

	char* temp;
	dResult = strtod(My_GetProfileString(strSection, strEntry, strDefault, strIniPath), &temp);	

	return dResult; 
}  


//��������������������������������<GetFilePath>������������������������������
//������ֵ : CString	��ִ���ļ���ȫ·��
//������˵�� : ȡ�ÿ�ִ���ļ���ȫ·��(�������ļ���)����һ��Ŀ¼
//��
//��������������������������������[GetFilePath]������������������������������
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







	

