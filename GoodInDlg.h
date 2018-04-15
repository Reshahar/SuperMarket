#if !defined(AFX_GOODINDLG_H__F52AEB92_F620_47D8_80F1_9EE721A30C4F__INCLUDED_)
#define AFX_GOODINDLG_H__F52AEB92_F620_47D8_80F1_9EE721A30C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GoodInDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGoodInDlg dialog

class CGoodInDlg : public CDialog
{
// Construction
public:
	void GoBack(int idx);
	CGoodInDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGoodInDlg)
	enum { IDD = IDD_GOOD_IN_DLG };
	CListCtrl	m_list;
	CTime	m_time;
	CTime	m_new_time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoodInDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGoodInDlg)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnGoodIn();
	afx_msg void OnGoodNewIn();
	virtual BOOL OnInitDialog();
	afx_msg void OnGoodId();
	afx_msg void OnGoodName();
	afx_msg void OnGoodExit();
	afx_msg void OnGoodAlter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool CountKeepData(CString &str,bool isnNew);
	void CreateOnlyID(CString &OnlyId);
	CDatabase m_db;
	void InitView();
	int m_GoodChose;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOODINDLG_H__F52AEB92_F620_47D8_80F1_9EE721A30C4F__INCLUDED_)
