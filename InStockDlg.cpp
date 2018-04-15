// InStockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "InStockDlg.h"
#include "SomeThings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInStockDlg dialog


CInStockDlg::CInStockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInStockDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInStockDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nRow = -1;
	m_nCol = -1;
	in = 1;
}


void CInStockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInStockDlg)
	DDX_Control(pDX, IDC_EDIT_LIST, m_edit);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInStockDlg, CDialog)
	//{{AFX_MSG_MAP(CInStockDlg)
	ON_BN_CLICKED(IDC_AUTO_IN_STOCK, OnAutoInStock)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_EN_KILLFOCUS(IDC_EDIT_LIST, OnKillfocusEditList)
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInStockDlg message handlers

BOOL CInStockDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitView();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInStockDlg::InitView()
{
	LONG style = GetWindowLong(m_list.m_hWnd,GWL_STYLE);
	style &=~LVS_TYPEMASK;
	style |=LVS_REPORT;
	SetWindowLong(m_list.m_hWnd,GWL_STYLE,style);
	DWORD liststyle = m_list.GetExtendedStyle();
	liststyle |=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_list.SetExtendedStyle(liststyle);
	m_list.InsertColumn(0,"编号",LVCFMT_LEFT,50);
	m_list.InsertColumn(1,"商品编号",LVCFMT_LEFT,150);
	m_list.InsertColumn(2,"商品名称",LVCFMT_LEFT,150);
	m_list.InsertColumn(3,"价格",LVCFMT_LEFT,150);
	m_list.InsertColumn(4,"数量",LVCFMT_LEFT,150);
	m_edit.ShowWindow(SW_HIDE);
	SetDlgItemText(IDC_DAY,"15");
	SetDlgItemText(IDC_NEW_DAY,"15");
}

void CInStockDlg::OnAutoInStock() 
{
	// TODO: Add your control notification handler code here
	CString t;
	int day,nday;
	GetDlgItemText(IDC_NEW_DAY,t);
	day = atoi(t);
	GetDlgItemText(IDC_DAY,t);
	nday = atoi(t);
	in = (day/nday)+1;
	CreateInStock();
}

void CInStockDlg::CreateInStock()
{
	CString day;
	int iday;
	GetDlgItemText(IDC_DAY,day);
	if(day.IsEmpty())
		day = "15";
	GetBeforeDay(day);
	CString con,sql,tmp;
	CRecordset rs;
	rs.m_pDatabase = &m_db;
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	sql.Format("select GID,GNAME,GPRICE,COUNT(*) INNUM from all_goods_out_stock_view group by GID,GNAME,GPRICE order by GID");		
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
			rs.GetFieldValue("INNUM",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal*in);
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

void CInStockDlg::GetBeforeDay(CString &day)
{
	CTime re,t = CTime::GetCurrentTime();
	CTimeSpan sp(atoi(day),0,0,0);
	re = t-sp;
	day.Format("%04d%02d%02d",re.GetYear(),re.GetMonth(),re.GetDay());	
}


void CInStockDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;  
    if(pNMListCtrl->iItem != -1 && pNMListCtrl->iSubItem ==4)  
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

BOOL CInStockDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )   
    {     
        if(GetFocus()->GetDlgCtrlID() == IDC_EDIT_LIST)  
        {  
			m_list.SetFocus();
        }  
        return TRUE;  
    }
	return CDialog::PreTranslateMessage(pMsg);
}

void CInStockDlg::OnKillfocusEditList() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString tmp;
	m_edit.GetWindowText(tmp);
	m_list.SetItemText(m_nRow,m_nCol,tmp);
	m_edit.ShowWindow(SW_HIDE);
}

void CInStockDlg::ListToCString(CString &str)
{
	CString tmp;
	str.Format("%50s","进货报告\r\n\r\n");
	tmp.Format("%16s%16s%16s%16s%16s\r\n","编号","商品编号","商品名称","价格","数量");
	str+=tmp;
	int i,j,n=m_list.GetItemCount();
	for(i=0;i<n;i++)
	{
		for(j=0;j<m_list.GetHeaderCtrl()->GetItemCount();j++)
		{
			tmp.Format("%16s",m_list.GetItemText(i,j));
			str+=tmp;
		}
		str+="\r\n";
	}	
	
}

void CInStockDlg::OnPrint() 
{
	// TODO: Add your control notification handler code here
	CString str;
	ListToCString(str);
	CSomeThings::MyWrite(str,"Stock.txt");
	Sleep(100);
	WinExec("notepad.exe Stock.txt",SW_SHOW);
}
