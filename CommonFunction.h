#ifndef __COMMONFUNCTION_H__
#define __COMMONFUNCTION_H__
//"CommonFunction.h"

//////////////////////////////// Тобю /////////////////////////////////////////////

BOOL  My_WriteProfileString(const CString strSection, const CString strEntry, 
						 const CString strValue, CString  strIniPath);
int  My_WriteProfileDouble(const CString strSection, const CString strEntry, 
						const double dValue, CString  strIniPath);
int  My_WriteProfileInt(const CString strSection, const CString strEntry, 
					  const int nValue,	CString  strIniPath);

CString My_GetProfileString(const CString strSection, const CString strEntry, 
						 const CString strDefault,	CString  strIniPath);
double  My_GetProfileDouble(const CString strSection, const CString strEntry, 
					   const double dDefault, CString  strIniPath);
int  My_GetProfileInt(const CString strSection, const CString strEntry, 
				   const int nDefault,	CString  strIniPath);

CString GetFilePath();

//------------------------------- Тобю ------------------------------------------

#endif //__COMMONFUNCTION_H__