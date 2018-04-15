#if !defined(AFX_MANAGERDLG_H__D77DBD9E_8BBE_4ECD_A923_5EF388CAB354__INCLUDED_)
#define AFX_MANAGERDLG_H__D77DBD9E_8BBE_4ECD_A923_5EF388CAB354__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManagerDlg.h : header file
//
#include "GoodInDlg.h"
#include "UserManagerDlg.h"
#include "SaleManagerDlg.h"
#include "StockManagerDlg.h"
#include "InStockDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CManagerDlg dialog

class CManagerDlg : public CDialog
{
// Construction
public:
	CManagerDlg(CWnd* pParent = NULL);   // standard constructor
private:
	void MyGetTime();
	void Init();
	CUserManagerDlg		m_manager;
	CGoodInDlg			m_good;
	CStockManagerDlg	m_stock;
	CSaleManagerDlg		m_sale;
	CInStockDlg			m_instock;

// Dialog Data
	//{{AFX_DATA(CManagerDlg)
	enum { IDD = IDD_MANAGER_DLALOG };
	CTabCtrl	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGERDLG_H__D77DBD9E_8BBE_4ECD_A923_5EF388CAB354__INCLUDED_)
