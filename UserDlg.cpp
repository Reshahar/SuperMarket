// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "UserDlg.h"
#include "SuperMarketDlg.h"
#include "FeeDlg.h"
#include "def.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_name,g_id;
extern float g_all_spend;
extern CString print_str;


/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog


CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
: CDialog(CUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDlg)
	//}}AFX_DATA_INIT
	m_IsMember  = false;
	m_GoodChose = GOODID;
	m_good_num  = 0;
	m_all_spend = 0;
	m_discount  = 1;
}


void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDC_COMMODITY, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
//{{AFX_MSG_MAP(CUserDlg)
ON_BN_CLICKED(IDC_SALE, OnSale)
ON_BN_CLICKED(IDC_MEM_IN, OnMemIn)
ON_BN_CLICKED(IDC_GOOD_ID, OnGoodId)
ON_BN_CLICKED(IDC_GOOD_NAME, OnGoodName)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_CAN, OnCan)
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_FEE, OnFee)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers

void CUserDlg::OnSale() 
{
	// TODO: Add your control notification handler code here
	CString num,t;
	CString gid;
	float price;
	int state;
	CString sqll;
	GetDlgItemText(IDC_GOOD_NUM,num);
	m_good_num = GetDlgItemInt(IDC_GOOD_COUNT);
	if(num.IsEmpty())
		return ;
	CRecordset rs;
	CRecordset rsa(&m_db);
	CString con = "DSN=HF;UID=system;PWD=123456asdf";
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}	
	CString sql;
	if(m_GoodChose==GOODID)
	{
		sql.Format("select * from hf_goods where GID = '%s'",num);
	}else
	{
		sql.Format("select * from hf_goods where GNAME = '%s'",num);
	}
	CString tmp;
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		if(!rs.IsEOF())
		{
			if(m_IsMember)
			{
				m_discount = 0.95;
			}
			int nRow = m_list.GetItemCount();
			CDBVariant var;
			int gnum; 
			rs.GetFieldValue("GNUM",var,SQL_C_SLONG);
			gnum = var.m_lVal;
			var.Clear();
			rs.GetFieldValue("GID",var,SQL_C_CHAR);
			gid = *(var.m_pstring);
			sqll.Format("select * from hf_all_goods where AGID = '%s' and rownum < %d order by ALASTDATA desc",gid);
			var.Clear();
			rsa.Open(CRecordset::dynaset,sqll);
			rsa.GetFieldValue("GSTATE",var,SQL_C_SLONG);
			state = var.m_lVal;
			rsa.Close();
			if(state!=0)//销售状态
			{
				if(gnum-m_good_num>=0)
				{
					int idx = GetSameRow(gid);
					if(idx==-1)
					{	
						m_list.InsertItem(nRow,gid);
						var.Clear();
						rs.GetFieldValue("GNAME",var,SQL_C_CHAR);
						m_list.SetItemText(nRow,1,*(var.m_pstring));
						var.Clear();
						rs.GetFieldValue("GPRICE",var,SQL_C_DOUBLE);
						price = var.m_dblVal;
						tmp.Format("%.2f",var.m_dblVal);
						var.Clear();
						m_list.SetItemText(nRow,2,tmp);	
						rs.GetFieldValue("GDPRICE",var,SQL_C_DOUBLE);
						if(state==2)
						{
							m_all_spend = m_all_spend +var.m_dblVal;
							tmp.Format("%.2f",var.m_dblVal);
						}else
						{
							m_all_spend = m_all_spend +price*m_discount;
							tmp.Format("%.2f",price*m_discount);
						}			
						m_list.SetItemText(nRow,3,tmp);
						tmp.Format("%.2f",m_all_spend);
						SetDlgItemText(IDC_STATIC_ALL_SPEND,tmp);
						tmp.Format("%d",m_good_num);
						m_list.SetItemText(nRow,4,tmp);
						
					}else
					{
						tmp = m_list.GetItemText(idx,2);
						float fprice = atof(tmp);
						m_all_spend = m_all_spend + fprice * m_good_num;
						tmp.Format("%.2f",m_all_spend);
						SetDlgItemText(IDC_STATIC_ALL_SPEND,tmp);
						tmp = m_list.GetItemText(idx,4);
						int nNum = atoi(tmp);
						tmp.Format("%d",nNum+m_good_num);
						m_list.SetItemText(idx,4,tmp);
					}			
					sql.Format("update hf_goods set GNUM = GNUM - '%d' where GID = '%s'",m_good_num,gid);
					m_db.ExecuteSQL(sql);
					int i;
					rs.Close();
					sql.Format("select * from hf_all_goods where AGID = '%s' and rownum < %d order by ALASTDATA desc",gid,m_good_num+1);
					rs.Open(CRecordset::dynaset,sql);
					CString sq;
					while(!rs.IsEOF())
					{
						var.Clear();
						rs.GetFieldValue("AONLYID",var,SQL_C_CHAR);
						GiveSaleTime(tmp);
						GetDlgItemText(IDC_MEM_NUM_IN,t);
						if(m_IsMember)
							sq.Format("insert into hf_salelist(EMPID,ONLYID,OPDATA,GID,MID) values('%s','%s','%s','%s','%s')",g_id,*(var.m_pstring),tmp,gid,t);
						else
							sq.Format("insert into hf_salelist(EMPID,ONLYID,OPDATA,GID) values('%s','%s','%s','%s')",g_id,*(var.m_pstring),tmp,gid);
						m_db.ExecuteSQL(sq);
						sq.Format("delete from hf_all_goods where AONLYID = '%s'",*(var.m_pstring));
						m_db.ExecuteSQL(sq);
						rs.MoveNext();
					}
				}else
				{
					AfxMessageBox("商品不够了！");
				}
			}else
			{
				AfxMessageBox("商品禁止销售！");
			}
			
		}else
		{
			AfxMessageBox("没有这个商品！");
		}
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	SetDlgItemInt(IDC_GOOD_COUNT,1);
	rsa.Close();
	rs.Close();
	m_db.Close();
}

BOOL CUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW, 0);
	// TODO: Add extra initialization here
	InitVIew();
	SetTimer(0,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUserDlg::InitVIew()
{
	LONG style = GetWindowLong(m_list.m_hWnd,GWL_STYLE);
	style &=~LVS_TYPEMASK;
	style |=LVS_REPORT;
	SetWindowLong(m_list.m_hWnd,GWL_STYLE,style);
	DWORD liststyle = m_list.GetExtendedStyle();
	liststyle |=LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(liststyle);
	m_list.InsertColumn(0,"商品编号",LVCFMT_LEFT,150);
	m_list.InsertColumn(1,"商品名称",LVCFMT_LEFT,150);
	m_list.InsertColumn(2,"价格",LVCFMT_LEFT,150);
	m_list.InsertColumn(3,"优惠价格",LVCFMT_LEFT,150);
	m_list.InsertColumn(4,"数量",LVCFMT_LEFT,150);
	
	ReInit();
	MyGetTime();
}

void CUserDlg::OnMemIn() 
{
	// TODO: Add your control notification handler code here
	CString num;
	GetDlgItemText(IDC_MEM_NUM_IN,num);
	if(num.IsEmpty())
		return ;
	CRecordset rs;
	CString con = "DSN=HF;UID=system;PWD=123456asdf";
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	CString sql;
	sql.Format("select * from hf_member where mid = '%s'",num);
	int i = 0;
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		if(rs.IsEOF())
		{
			AfxMessageBox("没有此会员！");
		}else
		{
			CDBVariant var;
			rs.GetFieldValue("MID",var,SQL_C_CHAR);
			SetDlgItemText(IDC_STATIC_MEM_ID,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("MNAME",var,SQL_C_CHAR);
			SetDlgItemText(IDC_STATIC_MEM_NAME,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("MEMBERDATA",var,SQL_C_CHAR);
			SetDlgItemText(IDC_STATIC_MEM_DATA,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("MALLSPEND",var,SQL_C_CHAR);
			SetDlgItemText(IDC_STATIC_MEM_SPEND,*var.m_pstring);
			m_IsMember = true;
			((CEdit*)GetDlgItem(IDC_MEM_NUM_IN))->SetReadOnly();
		}					
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	rs.Close();
	m_db.Close();
}

void CUserDlg::OnGoodId() 
{
	// TODO: Add your control notification handler code here
	m_GoodChose = GOODID;
}

void CUserDlg::OnGoodName() 
{
	// TODO: Add your control notification handler code here
	m_GoodChose = GOODNAME;
}

void CUserDlg::MyGetTime()
{
	CTime t =  CTime::GetCurrentTime();
	CString temp;
	temp.Format("%d年%d月%d日%d:%d:%d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	SetDlgItemText(IDC_STATIC_TIME,temp);
}

void CUserDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	MyGetTime();
	CDialog::OnTimer(nIDEvent);
}

void CUserDlg::OnCan() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int i,j,n = m_list.GetSelectedCount();
	for(i=0;i<n;i++)
	{
		for(j=0; j<m_list.GetItemCount(); j++)
		{
			if( m_list.GetItemState(j, LVIS_SELECTED) == LVIS_SELECTED)
			{
				DelOneRow(j);
			}
		}
	}
}

void CUserDlg::DelOneRow(int idx)
{
	CString gid = m_list.GetItemText(idx,0);
	CString gnum = m_list.GetItemText(idx,4);
	CString gprice = m_list.GetItemText(idx,3);
	int num = _ttoi(gnum),i;
	float fprice = atof(gprice);
	CString tmp;
	CRecordset rs;
	CString con = "DSN=HF;UID=system;PWD=123456asdf";
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	CString sql;
	sql.Format("update hf_goods set GNUM = GNUM + '%d' where GID = '%s'",num,gid);
	try
	{
		m_db.ExecuteSQL(sql);	
		rs.m_pDatabase = &m_db;
		sql.Format("select sid from hf_salelist where GID='%s' and rownum < %d order by opdata ",gid,num+1);	
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			CDBVariant var;
			rs.GetFieldValue("SID",var,SQL_C_CHAR);
			sql.Format("delete from hf_salelist where SID='%s'",*var.m_pstring);
			m_db.ExecuteSQL(sql);
			rs.MoveNext();
		}	
		m_all_spend = m_all_spend - fprice * num;
		tmp.Format("%.2f",m_all_spend);
		SetDlgItemText(IDC_STATIC_ALL_SPEND,tmp);
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	rs.Close();
	m_db.Close();
	m_list.DeleteItem(idx);
}

void CUserDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	int re  = ::MessageBox(NULL,"                  是否退出当前用户？","退出",MB_YESNOCANCEL);
	if(re == IDYES)
	{
		DelAllRow();
		EndDialog(0);
		CSuperMarketDlg m_dlg;
		m_dlg.DoModal();
	}else if(IDNO)
	{
		DelAllRow();
		EndDialog(0);
	}
	
}

int CUserDlg::GetSameRow(CString str) 
{
	int i,tmp = -1;
	for(i=0;i<m_list.GetItemCount();i++)
	{
		if(m_list.GetItemText(i,0).Compare(str)==0)
		{
			tmp = i;
		}
	}
	return tmp;
}

void CUserDlg::OnFee() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_STATIC_ALL_SPEND,str);
	g_all_spend = atof(str);
	CFeeDlg FeeDlg;
	ListToCString(print_str);
	int re = FeeDlg.DoModal();
	if(re==1)//dueding
	{
		CString memid;
		GetDlgItemText(IDC_STATIC_MEM_ID,memid);
		CString all_spend;
		GetDlgItemText(IDC_STATIC_ALL_SPEND,all_spend);
		float fall = atof(all_spend);
		int sale_num = GetSaleNum();
		CString con = "DSN=HF;UID=system;PWD=123456asdf";
		if(!m_db.OpenEx(con,0))
		{
			AfxMessageBox("ON");
		}
		CString sqlmem,sqluser_sale,sqluser_num;
		sqlmem.Format("update hf_member set MALLSPEND = MALLSPEND + '%.2f' where MID = '%s'",fall,memid);
		sqluser_sale.Format("update hf_user set SALE_NUM = SALE_NUM + '%.2f' where EMP_ID = '%s'",fall,g_id);
		sqluser_num.Format("update hf_user set SALE_AMOUNT = SALE_AMOUNT + '%d' where EMP_ID = '%s'",sale_num,g_id);
		try
		{
			if(m_IsMember)
				m_db.ExecuteSQL(sqlmem);
			m_db.ExecuteSQL(sqluser_sale);
			m_db.ExecuteSQL(sqluser_num);
		}catch (CDBException *ex)
		{
			AfxMessageBox(ex->m_strError);
		}
		m_db.Close();
	}
	m_all_spend = 0;
	while(m_list.DeleteItem(0));
	ReInit();
	if(m_IsMember)
	{
		((CEdit*)GetDlgItem(IDC_MEM_NUM_IN))->SetReadOnly(FALSE);
		m_IsMember = false;
	}
}

int CUserDlg::GetSaleNum()
{
	int i,re = 0,j;
	CString tmp;
	for(i=0;i<m_list.GetItemCount();i++)
	{
		tmp = m_list.GetItemText(i,3);
		j = _ttoi(tmp);
		re+=j;
	}
	return re;
}

void CUserDlg::ReInit()
{
	CString tmp,nu="               ";
	SetDlgItemText(IDC_STATIC_EMP_ID,g_id);
	SetDlgItemText(IDC_STATIC_EMP_NAME,g_name);
	((CButton*)GetDlgItem(IDC_GOOD_NAME))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_GOOD_ID))->SetCheck(TRUE);
	SetDlgItemInt(IDC_GOOD_COUNT,1);
	tmp.Format("%.2f",m_all_spend);
	SetDlgItemText(IDC_STATIC_ALL_SPEND,tmp);
	SetDlgItemText(IDC_MEM_NUM_IN,"");
	SetDlgItemText(IDC_STATIC_MEM_ID,nu);
	SetDlgItemText(IDC_STATIC_MEM_NAME,nu);
	SetDlgItemText(IDC_STATIC_MEM_DATA,nu);
	SetDlgItemText(IDC_STATIC_MEM_SPEND,nu);
	
}


void CUserDlg::GiveSaleTime(CString &str)
{
	CTime t = CTime::GetCurrentTime();
	SYSTEMTIME time;
	GetLocalTime(&time);
	str.Format("%d%02d%02d%02d%02d%02d%03d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond(),time.wMilliseconds);
}

void CUserDlg::DelAllRow()
{
	int n = m_list.GetItemCount();
	int i;
	for(i=0;i<n;i++)
	{
		DelOneRow(0);	
	}
}
void CUserDlg::ListToCString(CString &str)
{
	CString tmp,time,mem;
	GetDlgItemText(IDC_MEM_NUM_IN,mem);
	GiveSaleTime(time);
	str.Format("%50s","账单\r\n\r\n");
	tmp.Format("员工号:%16s  会员号：%16s  时间:%16s\r\n",g_id,mem,time);
	str+=tmp;
	tmp.Format("%8s%16s%16s%16s%16s%16s\r\n","编号","商品编号","商品名称","价格","优惠价格","数量");
	str+=tmp;
	int i,j,n=m_list.GetItemCount();
	for(i=0;i<n;i++)
	{
		tmp.Format("%8d",i+1);
		str+=tmp;
		for(j=0;j<m_list.GetHeaderCtrl()->GetItemCount();j++)
		{
			tmp.Format("%16s",m_list.GetItemText(i,j));
			str+=tmp;
		}
		str+="\r\n";
	}
	tmp.Format("总金额：%d",g_all_spend);
	str+=tmp;
}