// SuperMarket.h : main header file for the SUPERMARKET application
//

#if !defined(AFX_SUPERMARKET_H__E897AB24_9AE5_4307_90C6_7938C7F0F2CA__INCLUDED_)
#define AFX_SUPERMARKET_H__E897AB24_9AE5_4307_90C6_7938C7F0F2CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSuperMarketApp:
// See SuperMarket.cpp for the implementation of this class
//

class CSuperMarketApp : public CWinApp
{
public:
	CSuperMarketApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperMarketApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSuperMarketApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERMARKET_H__E897AB24_9AE5_4307_90C6_7938C7F0F2CA__INCLUDED_)
