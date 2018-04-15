// FeeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "FeeDlg.h"
#include "SomeThings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString print_str;
/////////////////////////////////////////////////////////////////////////////
// CFeeDlg dialog


CFeeDlg::CFeeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFeeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFeeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFeeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFeeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFeeDlg, CDialog)
	//{{AFX_MSG_MAP(CFeeDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_MY_EXIT, OnMyExit)
	ON_BN_CLICKED(IDC_MY_OK, OnMyOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFeeDlg message handlers

void CFeeDlg::OnCancel()
{
	
}	
void CFeeDlg::OnOK()
{
	
}
void CFeeDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(0);
}

BOOL CFeeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
	str.Format("%.2f",g_all_spend);
	SetDlgItemText(IDC_SHOULD_MONEY,str);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFeeDlg::OnMyExit() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

void CFeeDlg::OnMyOk() 
{
	// TODO: Add your control notification handler code here
	CSomeThings::MyWrite(print_str,"zhangdan.txt");
	Sleep(100);
	WinExec("notepad.exe zhangdan.txt",SW_SHOW);
	EndDialog(1);
}

BOOL CFeeDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYDOWN == pMsg-> message && 13 == pMsg-> wParam)
	{
		if (  GetDlgItem(IDC_FACT_MONEY) == GetFocus())
		{
			
			CString str;
			GetDlgItemText(IDC_FACT_MONEY,str);
			float fact = atof(str);
			float should_find = fact - g_all_spend;
			if(should_find<0)
			{
				AfxMessageBox("½ð¶î²»×ã£¡");
			}else
			{
				str.Format("%.2f",should_find);
				SetDlgItemText(IDC_SHOULD_FIND_MONEY,str);
			}
			return FALSE;
		}
		else
		{
			return   FALSE; 
		}
		
	}
	return CDialog::PreTranslateMessage(pMsg);
}
