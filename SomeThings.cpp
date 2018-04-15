// SomeThings.cpp: implementation of the CSomeThings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperMarket.h"
#include "SomeThings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSomeThings::CSomeThings()
{

}

CSomeThings::~CSomeThings()
{

}

void CSomeThings::GetDataInfo(CString &DSN,CString &UID,CString &PWD)  //从文件中读取
{

}
bool CSomeThings::SetDataInfo(CString &DSN,CString &UID,CString &PWD)	//讲信息写到文件中
{
	return true;
}
void CSomeThings::InCode(CString &str)
{
	int i;
	for(i=0;i<str.GetLength();i++)
	{
		TCHAR j = str.GetAt(i);
		str.SetAt(i,j^33);
	}
	AfxMessageBox(str);
}

void CSomeThings::MyWrite(CString str,CString name)
{
	CFile file(name,CFile::modeCreate|CFile::modeWrite);
	file.Write(str,str.GetLength());
}
