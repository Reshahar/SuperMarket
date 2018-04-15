#if !defined(AFX_USERMANAGERDLG_H__EE18E6E1_0844_428C_BE5F_05AFDE0BC0F0__INCLUDED_)
#define AFX_USERMANAGERDLG_H__EE18E6E1_0844_428C_BE5F_05AFDE0BC0F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserManagerDlg.h : header file
//
#include "EditListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CUserManagerDlg dialog

class CUserManagerDlg : public CDialog
{
// Construction
public:
	CUserManagerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserManagerDlg)
	enum { IDD = IDD_USER_MANAGER_DLG };
	CEdit	m_edit;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserManagerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserManagerDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnUser();
	afx_msg void OnMember();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditList();
	afx_msg void OnFindData();
	afx_msg void OnAdd();
	afx_msg void OnAlter();
	afx_msg void OnDel();
	afx_msg void OnDelete();
	afx_msg void OnInsert();
	afx_msg void OnFirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InsertFirm();
	void AlterFirm();
	void ShowFrim();
	void InitFirm();
	void InsertUser();
	void InsertMember();
	void AlterMember();
	void alterUser();
	void InitMember();
	void ShowMember();
	void DelOneRow(int idx,CString sql);
	CDatabase m_db;
	void ShowUser();
	void InitUser();
	void InitView();
	int m_IDChose;
	int m_nRow;
	int m_nCol;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERMANAGERDLG_H__EE18E6E1_0844_428C_BE5F_05AFDE0BC0F0__INCLUDED_)
