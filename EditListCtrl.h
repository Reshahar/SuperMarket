 #if !defined(AFX_EDITLISTCTRL_H__4C831265_E131_46BD_9068_E240AEA76349__INCLUDED_)
#define AFX_EDITLISTCTRL_H__4C831265_E131_46BD_9068_E240AEA76349__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl window

class CEditListCtrl : public CListCtrl
{
// Construction
public:
	CEditListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditListCtrl)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetEditColomn(int col,BOOL edit);
	virtual ~CEditListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditListCtrl)
	afx_msg void OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CEdit * m_edit;//指向编辑框，初值为NULL
	BOOL * m_isedit;//允许进行编辑的列，初值为NULL
	int m_item;//当前编辑的行号，初值为-1
	int m_subitem;//当前编辑的列号，初值为-1
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLISTCTRL_H__4C831265_E131_46BD_9068_E240AEA76349__INCLUDED_)
