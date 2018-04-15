// SuperMarketDlg.h : header file
//

#if !defined(AFX_SUPERMARKETDLG_H__F61FF5A7_646F_4FF9_844F_66CD1A4FCE7B__INCLUDED_)
#define AFX_SUPERMARKETDLG_H__F61FF5A7_646F_4FF9_844F_66CD1A4FCE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSuperMarketDlg dialog

class CSuperMarketDlg : public CDialog
{
// Construction
public:
	CSuperMarketDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSuperMarketDlg)
	enum { IDD = IDD_SUPERMARKET_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperMarketDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSuperMarketDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLog();
	afx_msg void OnExit();
	virtual void OnOK();
	virtual void OnCancel();	
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDatabase m_db;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERMARKETDLG_H__F61FF5A7_646F_4FF9_844F_66CD1A4FCE7B__INCLUDED_)
