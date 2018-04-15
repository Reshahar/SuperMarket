// SaleManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "SaleManagerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaleManagerDlg dialog
int flag = -1;

CSaleManagerDlg::CSaleManagerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSaleManagerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaleManagerDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nRow = -1;
	m_nCol = -1;
}


void CSaleManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaleManagerDlg)
	DDX_Control(pDX, IDC_EDIT_ALTER, m_edit);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaleManagerDlg, CDialog)
//{{AFX_MSG_MAP(CSaleManagerDlg)
ON_BN_CLICKED(IDC_ALTER, OnAlter)
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_EN_KILLFOCUS(IDC_EDIT_ALTER, OnKillfocusEditAlter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaleManagerDlg message handlers

BOOL CSaleManagerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitView();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSaleManagerDlg::InitView()
{
	LONG style = GetWindowLong(m_list.m_hWnd,GWL_STYLE);
	style &=~LVS_TYPEMASK;
	style |=LVS_REPORT;
	SetWindowLong(m_list.m_hWnd,GWL_STYLE,style);
	DWORD liststyle = m_list.GetExtendedStyle();
	liststyle |=LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
	m_list.SetExtendedStyle(liststyle);
	m_list.InsertColumn(0,"商品唯一编号",LVCFMT_LEFT,175);
	m_list.InsertColumn(1,"商品编号",LVCFMT_LEFT,175);
	m_list.InsertColumn(2,"商品名称",LVCFMT_LEFT,100);
	m_list.InsertColumn(3,"商品价格",LVCFMT_LEFT,100);
	m_list.InsertColumn(4,"优惠价格",LVCFMT_LEFT,100);
	m_list.InsertColumn(5,"距过期天数",LVCFMT_LEFT,100);
	m_list.InsertColumn(6,"商品状态",LVCFMT_LEFT,100);
	m_edit.ShowWindow(SW_HIDE);

}

void CSaleManagerDlg::OnAlter() 
{
	// TODO: Add your control notification handler code here
	if(flag!=1)
	{
		SaveAlter();
		flag = 1;
	}

}

void CSaleManagerDlg::GetGoodInfo()
{
	CRecordset rs;
	int nPower;
	CString con,tmp;
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD);
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	CString sql;
	sql.Format("select * from all_goods_view");
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			int nRow = m_list.GetItemCount();
			CDBVariant var;
			rs.GetFieldValue("AONLYID",var,SQL_C_CHAR);
			m_list.InsertItem(nRow,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("AGID",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,1,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("GNAME",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,2,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("GPRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(nRow,3,tmp);
			var.Clear();
			rs.GetFieldValue("GDPRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(nRow,4,tmp);
			var.Clear();
			rs.GetFieldValue("ALASTDATA",var,SQL_C_CHAR);
			tmp.Format("%d",CountKeepLeaveDay(*var.m_pstring));
			m_list.SetItemText(nRow,5,tmp);
			var.Clear();
			rs.GetFieldValue("GSTATE",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal);
			m_list.SetItemText(nRow,6,tmp);
			var.Clear();
			rs.MoveNext();
		}		
	}catch (CDBException *ex) {
		
		AfxMessageBox(ex->m_strError);
	}
	rs.Close();
	m_db.Close();
}

void CSaleManagerDlg::OnShow() 
{
	// TODO: Add your control notification handler code here
	GetGoodInfo();
	flag = 0;
}

void CSaleManagerDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;  
    if(pNMListCtrl->iItem != -1)  
    {  
        CRect rect,dlgRect;  
   
        int width = m_list.GetColumnWidth(pNMListCtrl->iSubItem);  
        m_list.GetSubItemRect(pNMListCtrl->iItem,pNMListCtrl->iSubItem,LVIR_BOUNDS,rect);   
        m_nRow = pNMListCtrl->iItem;  
        m_nCol = pNMListCtrl->iSubItem;  
        m_list.GetWindowRect(&dlgRect);  
        //调整与父窗口对应   
        ScreenToClient(&dlgRect);  
        int height = rect.Height();  
        rect.top += (dlgRect.top+1);  
        rect.left += (dlgRect.left+1);  
        rect.bottom = rect.top+height+2;  
        rect.right = rect.left+width+2;  
        m_edit.MoveWindow(&rect);
		m_edit.SetWindowText(m_list.GetItemText(m_nRow,m_nCol));
        m_edit.ShowWindow(SW_SHOW);  
        m_edit.SetFocus(); 
		m_edit.SetSel(-1);
    }      	
	*pResult = 0;
}

BOOL CSaleManagerDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )   
    {     
        if(GetFocus()->GetDlgCtrlID() == IDC_EDIT_ALTER)  
        {  
			m_list.SetFocus();
        }  
        return TRUE;  
    }
	return CDialog::PreTranslateMessage(pMsg);
}

void CSaleManagerDlg::OnKillfocusEditAlter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString tmp;
	m_edit.GetWindowText(tmp);
	m_list.SetItemText(m_nRow,m_nCol,tmp);
	m_edit.ShowWindow(SW_HIDE);
}

int CSaleManagerDlg::CountKeepLeaveDay(CString &day)
{
	CString tmpYear,TmpMonth,TmpDay;
	CTime tm = CTime::GetCurrentTime();
	tmpYear = day.Mid(0,4);
	TmpMonth = day.Mid(4,2);
	TmpDay = day.Mid(6,2);
	CTime t(atoi(tmpYear),atoi(TmpMonth),atoi(TmpDay),0,0,0);
	CTimeSpan sp = t-tm;
	return sp.GetDays();
}

void CSaleManagerDlg::SaveAlter()
{
	CString  con,sql,tmp,ONLYID,GID,GNAME,GPRICE,GDPRICE,GSTATS;
	int state;
	float price,dprice;
	int i,count = m_list.GetItemCount();
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	for(i=0;i<count;i++)
	{
		ONLYID = m_list.GetItemText(i,0);
		GID = m_list.GetItemText(i,1);
		GNAME = m_list.GetItemText(i,2);
		GPRICE = m_list.GetItemText(i,3);
		price = atof(GPRICE);
		GDPRICE = m_list.GetItemText(i,4);
		dprice = atof(GDPRICE);
		GSTATS = m_list.GetItemText(i,6);
		state = atoi(GSTATS);
		try
		{	sql.Format("update hf_goods set GNAME ='%s',GDPRICE = %.2f where GID='%s'",GNAME,dprice,GID);
			m_db.ExecuteSQL(sql);
			sql.Format("update hf_all_goods set GSTATE = %d where AONLYID = '%s'",state,ONLYID);
			m_db.ExecuteSQL(sql);
		}catch (CDBException *ex)
		{
			AfxMessageBox(ex->m_strError);
		}
	}
	AfxMessageBox("修改成功！");
	m_db.Close();
}
