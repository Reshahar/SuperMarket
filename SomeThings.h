// SomeThings.h: interface for the CSomeThings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOMETHINGS_H__58A39120_F3FE_43F2_9D04_D0ADE2E964EF__INCLUDED_)
#define AFX_SOMETHINGS_H__58A39120_F3FE_43F2_9D04_D0ADE2E964EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSomeThings  
{
public:
	static void  MyWrite(CString str,CString name);
	CSomeThings();
	virtual ~CSomeThings();
	void static GetDataInfo(CString &DSN,CString &UID,CString &PWD);
	bool static SetDataInfo(CString &DSN,CString &UID,CString &PWD);
	void static InCode(CString &str);
};

#endif // !defined(AFX_SOMETHINGS_H__58A39120_F3FE_43F2_9D04_D0ADE2E964EF__INCLUDED_)
