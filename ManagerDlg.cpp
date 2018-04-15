// ManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "ManagerDlg.h"
#include "UserDlg.h"
#include "SuperMarketDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManagerDlg dialog


CManagerDlg::CManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManagerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManagerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManagerDlg)
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CManagerDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManagerDlg message handlers

BOOL CManagerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ModifyStyleEx(0, WS_EX_APPWINDOW, 0);
	SetTimer(0,1000,NULL);
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CManagerDlg::Init()
{	
	int h,w;
	CRect rect;
	GetClientRect(rect);
	SetDlgItemText(IDC_STATIC_EMP_ID,g_id);
	SetDlgItemText(IDC_STATIC_EMP_NAME,g_name);	
	TCITEM item;
	
	item.mask = TCIF_TEXT;
	item.pszText = "商品录入";
	m_tab.InsertItem(0,&item);
	item.pszText ="人员管理";
	m_tab.InsertItem (1,&item);
	item.pszText="销售管理";
	m_tab.InsertItem(2,&item);
	item.pszText="库存管理";
	m_tab.InsertItem(3,&item);
	item.pszText="进货管理";
	m_tab.InsertItem(4,&item);

	m_good.Create(IDD_GOOD_IN_DLG,&m_tab);
	m_manager.Create(IDD_USER_MANAGER_DLG,&m_tab);
	m_stock.Create(IDD_STOCK_MANAGER_DLG,&m_tab);
	m_sale.Create(IDD_SALE_MANAGER_DLG,&m_tab);
	m_instock.Create(IDD_IN_STOCK_DLG,&m_tab);

	h = rect.bottom-rect.top;
	w = rect.right - rect.left;
	m_good.SetWindowPos (NULL,10,40,w,h,SWP_SHOWWINDOW);
	m_manager.SetWindowPos (NULL,10,40,w,h,SWP_HIDEWINDOW);	
	m_stock.SetWindowPos (NULL,10,40,w,h,SWP_HIDEWINDOW);
	m_sale.SetWindowPos (NULL,10,40,w,h,SWP_HIDEWINDOW);
	m_instock.SetWindowPos(NULL,10,40,w,h,SWP_HIDEWINDOW);
	MyGetTime();
}

void CManagerDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	switch(m_tab.GetCurSel())
	{
	case 0:
		m_stock.ShowWindow(SW_HIDE);
		m_sale.ShowWindow(SW_HIDE);
		m_manager.ShowWindow(SW_HIDE);
		m_instock.ShowWindow(SW_HIDE);
		m_good.ShowWindow(SW_NORMAL);
		break;
	case 1:
		if(g_id.Compare("1001")==0)
		{
			m_stock.ShowWindow(SW_HIDE);
			m_sale.ShowWindow(SW_HIDE);
			m_good.ShowWindow(SW_HIDE);
			m_instock.ShowWindow(SW_HIDE);
			m_manager.ShowWindow(SW_NORMAL);
		}
		break;
	case 2:
		if(g_id.Compare("1001")==0)
		{
		m_stock.ShowWindow(SW_HIDE);
		m_manager.ShowWindow(SW_HIDE);
		m_good.ShowWindow(SW_HIDE);
		m_instock.ShowWindow(SW_HIDE);
		m_sale.ShowWindow(SW_NORMAL);	
		}
		break;
	case 3:
		if(g_id.Compare("1001")==0)
		{
			m_manager.ShowWindow(SW_HIDE);
			m_good.ShowWindow(SW_HIDE);
			m_sale.ShowWindow(SW_HIDE);
			m_instock.ShowWindow(SW_HIDE);
			m_stock.ShowWindow(SW_NORMAL);
		}
		break;
	case 4:
		if(g_id.Compare("1001")==0)
		{
			m_manager.ShowWindow(SW_HIDE);
			m_good.ShowWindow(SW_HIDE);
			m_sale.ShowWindow(SW_HIDE);
			m_stock.ShowWindow(SW_HIDE);
			m_instock.ShowWindow(SW_NORMAL);
		}
		break;
	}

	*pResult = 0;
}

void CManagerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	MyGetTime();
	CDialog::OnTimer(nIDEvent);
}

void CManagerDlg::MyGetTime()
{	
	CTime t =  CTime::GetCurrentTime();
	CString temp;
	temp.Format("%d年%d月%d日%d:%d:%d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	SetDlgItemText(IDC_STATIC_TIME,temp);
}

void CManagerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	int re  = ::MessageBox(NULL,"                  是否退出当前用户？","退出",MB_YESNOCANCEL);
	if(re == IDYES)
	{
		EndDialog(0);
		CSuperMarketDlg m_dlg;
		m_dlg.DoModal();
	}else if(IDNO)
	{
		EndDialog(0);
	}
}
