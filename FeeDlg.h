#if !defined(AFX_FEEDLG_H__3DAB3C7C_7BD3_42D5_8E57_ED6FB0C446E6__INCLUDED_)
#define AFX_FEEDLG_H__3DAB3C7C_7BD3_42D5_8E57_ED6FB0C446E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FeeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFeeDlg dialog

class CFeeDlg : public CDialog
{
// Construction
public:
	CFeeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFeeDlg)
	enum { IDD = IDD_DIALOG_FEE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeeDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFeeDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnMyExit();
	afx_msg void OnMyOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEEDLG_H__3DAB3C7C_7BD3_42D5_8E57_ED6FB0C446E6__INCLUDED_)
