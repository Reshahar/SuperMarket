#if !defined(AFX_SALEMANAGERDLG_H__10AED169_BB55_4240_8D61_7D3CF28E8540__INCLUDED_)
#define AFX_SALEMANAGERDLG_H__10AED169_BB55_4240_8D61_7D3CF28E8540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaleManagerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaleManagerDlg dialog

class CSaleManagerDlg : public CDialog
{
// Construction
public:
	CSaleManagerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaleManagerDlg)
	enum { IDD = IDD_SALE_MANAGER_DLG };
	CEdit	m_edit;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaleManagerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaleManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAlter();
	afx_msg void OnShow();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditAlter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SaveAlter();
	int CountKeepLeaveDay(CString & day);
	void GetGoodInfo();
	void InitView();
	CDatabase m_db;
	int m_nRow;
	int m_nCol;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SALEMANAGERDLG_H__10AED169_BB55_4240_8D61_7D3CF28E8540__INCLUDED_)
