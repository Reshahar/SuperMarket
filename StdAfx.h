// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CACD27CB_1854_4BC7_8320_A208229412E2__INCLUDED_)
#define AFX_STDAFX_H__CACD27CB_1854_4BC7_8320_A208229412E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <afxdb.h>
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "SkinPPWTL.h"
#pragma comment(lib,"SkinPPWTL.lib")

extern CString g_name,g_id;
extern float g_all_spend;
extern CString g_DSN,g_UID,g_PWD;
extern CString print_str;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CACD27CB_1854_4BC7_8320_A208229412E2__INCLUDED_)
