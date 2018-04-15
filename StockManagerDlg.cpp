// StockManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "StockManagerDlg.h"
#include "def.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockManagerDlg dialog


CStockManagerDlg::CStockManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockManagerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStockManagerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStockManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStockManagerDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStockManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CStockManagerDlg)
	ON_BN_CLICKED(IDC_IN_STOCK, OnInStock)
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	ON_BN_CLICKED(IDC_OUT_STOCK, OnOutStock)
	ON_BN_CLICKED(IDC_STOCK_SUN, OnStockSun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockManagerDlg message handlers

BOOL CStockManagerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitView();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStockManagerDlg::InitView()
{
	LONG style = GetWindowLong(m_list.m_hWnd,GWL_STYLE);
	style &=~LVS_TYPEMASK;
	style |=LVS_REPORT;
	SetWindowLong(m_list.m_hWnd,GWL_STYLE,style);
	DWORD liststyle = m_list.GetExtendedStyle();
	liststyle |=LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
	m_list.SetExtendedStyle(liststyle);
	((CButton*)GetDlgItem(IDC_STOCK_SUN))->SetCheck(TRUE);
	m_chose = ALLSTOCK;
	InitALL();
}

void CStockManagerDlg::OnInStock() 
{
	// TODO: Add your control notification handler code here
	m_chose = INSTOCK;
}

void CStockManagerDlg::ShowInStock()
{
	CString con,sql,tmp;
	CRecordset rs;
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	sql.Format("select * from all_goods_in_stock_view order by sid desc");
	rs.m_pDatabase = &m_db;
	
	try
	{
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			int n = m_list.GetItemCount();
			CDBVariant var;
			rs.GetFieldValue("SID",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal);
			m_list.InsertItem(n,tmp);
			var.Clear();
			rs.GetFieldValue("EMP_ID",var,SQL_C_CHAR);
			m_list.SetItemText(n,1,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("OPDATA",var,SQL_C_CHAR);
			m_list.SetItemText(n,2,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("AONLYID",var,SQL_C_CHAR);		
			m_list.SetItemText(n,3,*(var.m_pstring));
			var.Clear();
			rs.GetFieldValue("GID",var,SQL_C_CHAR);
			m_list.SetItemText(n,4,*(var.m_pstring));
			var.Clear();
			rs.GetFieldValue("GNAME",var,SQL_C_CHAR);
			m_list.SetItemText(n,5,*(var.m_pstring));
			var.Clear();
			rs.GetFieldValue("GPRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(n,6,tmp);
			var.Clear();
			rs.GetFieldValue("GDPRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(n,7,tmp);
			var.Clear();
			rs.MoveNext();
		}

	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	rs.Close();
	m_db.Close();
}

void CStockManagerDlg::OnShow() 
{
	// TODO: Add your control notification handler code here
	switch(m_chose) 
	{
	case INSTOCK:
		InitIInStock();	
		ShowInStock();
		break;
	case OUTSTOCK:
		InitOutStock();
		ShowOutStock();
		break;
	case ALLSTOCK:
		InitALL();
		ShowAll();
		break;
	}
}

void CStockManagerDlg::InitIInStock()
{
	while(m_list.DeleteItem(0)); 
	while(m_list.DeleteColumn(0));
	
	m_list.InsertColumn(0,"编号",LVCFMT_LEFT,50);
	m_list.InsertColumn(1,"员工号",LVCFMT_LEFT,60);
	m_list.InsertColumn(2,"操作日期",LVCFMT_LEFT,160);
	m_list.InsertColumn(3,"商品唯一编号",LVCFMT_LEFT,160);
	m_list.InsertColumn(4,"商品编号",LVCFMT_LEFT,100);
	m_list.InsertColumn(5,"商品名称",LVCFMT_LEFT,100);
	m_list.InsertColumn(6,"商品价格",LVCFMT_LEFT,100);
	m_list.InsertColumn(7,"商品优惠价格",LVCFMT_LEFT,100);
//	m_list.InsertColumn(8,"商品数量",LVCFMT_LEFT,80);
}

void CStockManagerDlg::OnOutStock() 
{
	// TODO: Add your control notification handler code here
	m_chose = OUTSTOCK;
}

void CStockManagerDlg::InitOutStock()
{
	while(m_list.DeleteItem(0)); 
	while(m_list.DeleteColumn(0));
	
	m_list.InsertColumn(0,"编号",LVCFMT_LEFT,50);
	m_list.InsertColumn(1,"员工号",LVCFMT_LEFT,60);
	m_list.InsertColumn(2,"操作日期",LVCFMT_LEFT,160);
	m_list.InsertColumn(3,"售出会员号",LVCFMT_LEFT,80);
	m_list.InsertColumn(4,"商品唯一编号",LVCFMT_LEFT,160);
	m_list.InsertColumn(5,"商品编号",LVCFMT_LEFT,100);
	m_list.InsertColumn(6,"商品名称",LVCFMT_LEFT,100);
	m_list.InsertColumn(7,"商品价格",LVCFMT_LEFT,100);
	m_list.InsertColumn(8,"商品优惠价格",LVCFMT_LEFT,100);
}

void CStockManagerDlg::OnStockSun() 
{
	// TODO: Add your control notification handler code here
	m_chose = ALLSTOCK;
}

void CStockManagerDlg::ShowOutStock()
{
		CString con,sql,tmp;
	CRecordset rs;
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	sql.Format("select * from all_goods_out_stock_view order by sid desc");
	rs.m_pDatabase = &m_db;
	
	try
	{
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			int n = m_list.GetItemCount();
			CDBVariant var;
			rs.GetFieldValue("SID",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal);
			m_list.InsertItem(n,tmp);
			var.Clear();
			rs.GetFieldValue("EMPID",var,SQL_C_CHAR);
			m_list.SetItemText(n,1,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("OPDATA",var,SQL_C_CHAR);
			m_list.SetItemText(n,2,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("MID",var,SQL_C_CHAR);
			m_list.SetItemText(n,3,*(var.m_pstring));
			var.Clear();
			rs.GetFieldValue("ONLYID",var,SQL_C_CHAR);		
			m_list.SetItemText(n,4,*(var.m_pstring));
			var.Clear();
			rs.GetFieldValue("GID",var,SQL_C_CHAR);
			m_list.SetItemText(n,5,*(var.m_pstring));
			var.Clear();
			rs.GetFieldValue("GNAME",var,SQL_C_CHAR);
			m_list.SetItemText(n,6,*(var.m_pstring));
			var.Clear();
			rs.GetFieldValue("GPRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(n,7,tmp);
			var.Clear();
			rs.GetFieldValue("GDPRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(n,8,tmp);
			var.Clear();
			rs.MoveNext();
		}

	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	rs.Close();
	m_db.Close();
}

void CStockManagerDlg::InitALL()
{
	while(m_list.DeleteItem(0)); 
	while(m_list.DeleteColumn(0));
	
	m_list.InsertColumn(0,"编号",LVCFMT_LEFT,50);
	m_list.InsertColumn(1,"商品编号",LVCFMT_LEFT,100);
	m_list.InsertColumn(2,"商品名称",LVCFMT_LEFT,100);
	m_list.InsertColumn(3,"商品价格",LVCFMT_LEFT,100);
	m_list.InsertColumn(4,"数量",LVCFMT_LEFT,100);

}

void CStockManagerDlg::ShowAll()
{
	CString con,sql,tmp;
	CRecordset rs;
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	sql.Format("select * from hf_goods order by GID");
	rs.m_pDatabase = &m_db;	
	try
	{
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			int n = m_list.GetItemCount();
			CDBVariant var;
			tmp.Format("%d",n+1);
			m_list.InsertItem(n,tmp);
			rs.GetFieldValue("GID",var,SQL_C_CHAR);
			m_list.SetItemText(n,1,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("GNAME",var,SQL_C_CHAR);
			m_list.SetItemText(n,2,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("GPRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(n,3,tmp);
			var.Clear();
			rs.GetFieldValue("GNUM",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal);
			m_list.SetItemText(n,4,tmp);
			var.Clear();
			rs.MoveNext();
		}

	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	rs.Close();
	m_db.Close();	
}


