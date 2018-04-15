#if !defined(AFX_USERDLG_H__481A653F_D0C4_4CDB_84D5_B0D4299E13BA__INCLUDED_)
#define AFX_USERDLG_H__481A653F_D0C4_4CDB_84D5_B0D4299E13BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	void ReInit();
	int GetSaleNum();
	int GetSameRow(CString str);
	void DelOneRow(int idx);
	void MyGetTime();
	void InitVIew();
	void ListToCString(CString &str);
	CUserDlg(CWnd* pParent = NULL);   // standard constructor
	CDatabase m_db;
// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_USER_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	afx_msg void OnSale();
	virtual BOOL OnInitDialog();
	afx_msg void OnMemIn();
	afx_msg void OnGoodId();
	afx_msg void OnGoodName();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCan();
	afx_msg void OnClose();
	afx_msg void OnFee();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DelAllRow();
	void GiveSaleTime(CString &str);
	float m_discount;
	float m_all_spend;
	int m_good_num;
	int m_GoodChose;
	bool m_IsMember;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__481A653F_D0C4_4CDB_84D5_B0D4299E13BA__INCLUDED_)
