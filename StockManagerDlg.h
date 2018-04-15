#if !defined(AFX_STOCKMANAGERDLG_H__E2876714_9249_4B00_8480_1D4B18E2E1D1__INCLUDED_)
#define AFX_STOCKMANAGERDLG_H__E2876714_9249_4B00_8480_1D4B18E2E1D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StockManagerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStockManagerDlg dialog

class CStockManagerDlg : public CDialog
{
// Construction
public:
	CStockManagerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStockManagerDlg)
	enum { IDD = IDD_STOCK_MANAGER_DLG };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStockManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnInStock();
	afx_msg void OnShow();
	afx_msg void OnOutStock();
	afx_msg void OnStockSun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowAll();
	void InitALL();
	void ShowOutStock();
	void InitOutStock();
	void InitIInStock();
	void ShowInStock();
	void InitView();
	CDatabase m_db;
	int m_chose;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKMANAGERDLG_H__E2876714_9249_4B00_8480_1D4B18E2E1D1__INCLUDED_)
