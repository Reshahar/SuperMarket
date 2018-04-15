#if !defined(AFX_INSTOCKDLG_H__26BC86D0_F372_42C3_9EB8_48177A8E9347__INCLUDED_)
#define AFX_INSTOCKDLG_H__26BC86D0_F372_42C3_9EB8_48177A8E9347__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InStockDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInStockDlg dialog

class CInStockDlg : public CDialog
{
// Construction
public:
	CInStockDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInStockDlg)
	enum { IDD = IDD_IN_STOCK_DLG };
	CEdit	m_edit;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInStockDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInStockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAutoInStock();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditList();
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int in;
	void ListToCString(CString &str);
	void GetBeforeDay(CString & day);
	void CreateInStock();
	void InitView();
	CDatabase m_db;
	int m_nRow,m_nCol;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTOCKDLG_H__26BC86D0_F372_42C3_9EB8_48177A8E9347__INCLUDED_)
