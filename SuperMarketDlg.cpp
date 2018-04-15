// SuperMarketDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "SuperMarketDlg.h"
#include "ManagerDlg.h"
#include "UserDlg.h"
#include "SomeThings.h"

extern CString g_name,g_id;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperMarketDlg dialog

CSuperMarketDlg::CSuperMarketDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperMarketDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuperMarketDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuperMarketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperMarketDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSuperMarketDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperMarketDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOG, OnLog)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperMarketDlg message handlers

BOOL CSuperMarketDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSuperMarketDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSuperMarketDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CSuperMarketDlg::OnLog() 
{
	// TODO: Add your control notification handler code here
	CRecordset rs;
	int nPower;
	CString con = "DSN=HF;UID=system;PWD=123456asdf";
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	CString pwd,name;
	GetDlgItemText(IDC_NAME,name);
	GetDlgItemText(IDC_PWD,pwd);
	CString sql;
	sql.Format("select * from hf_user where emp_id = '%s' and user_pwd ='%s'",name,pwd);
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		if(rs.IsEOF())
			AfxMessageBox("EMP_ID Or Pwd Error!");
		else
		{
			g_id = name;
			CDBVariant var;
			rs.GetFieldValue("POWER",var,SQL_C_SLONG);
			nPower = var.m_lVal;
			var.Clear();
			rs.GetFieldValue("NAME",var,SQL_C_CHAR);
			g_name = *var.m_pstring;
			if(nPower==1)
			{
				EndDialog(0);
				CManagerDlg manager;
				manager.DoModal();	
			}else
			{
				EndDialog(0);
				CUserDlg user;
				user.DoModal();
			}		
		}		
	}catch (CDBException *ex) {

		AfxMessageBox(ex->m_strError);
	}
	rs.Close();
 	m_db.Close();
}
void CSuperMarketDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	//ÍË³ö¶Ô»°¿ò
	CDialog::OnCancel();
}
void CSuperMarketDlg::OnCancel()
{
	
}	
void CSuperMarketDlg::OnOK()
{
	
}	

void CSuperMarketDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnCancel();
}
