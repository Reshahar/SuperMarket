// GoodInDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "GoodInDlg.h"
#include "def.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CString g_DSN,g_UID,g_PWD;

/////////////////////////////////////////////////////////////////////////////
// CGoodInDlg dialog


CGoodInDlg::CGoodInDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGoodInDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGoodInDlg)
	m_time = 0;
	m_new_time = 0;
	//}}AFX_DATA_INIT
	m_GoodChose = GOODID;
}


void CGoodInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGoodInDlg)
	DDX_Control(pDX, IDC_LIST_GOOD, m_list);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_OLD, m_time);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_NEW, m_new_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGoodInDlg, CDialog)
	//{{AFX_MSG_MAP(CGoodInDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_GOOD_IN, OnGoodIn)
	ON_BN_CLICKED(IDC_GOOD_NEW_IN, OnGoodNewIn)
	ON_BN_CLICKED(IDC_GOOD_ID, OnGoodId)
	ON_BN_CLICKED(IDC_GOOD_NAME, OnGoodName)
	ON_BN_CLICKED(IDC_GOOD_EXIT, OnGoodExit)
	ON_BN_CLICKED(IDC_GOOD_ALTER, OnGoodAlter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoodInDlg message handlers

void CGoodInDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

void CGoodInDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CGoodInDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//	CDialog::OnClose();
}

void CGoodInDlg::OnGoodIn() 
{
	// TODO: Add your control notification handler code here
	CString num_or_name,keeptime;
	CString con;
	CRecordset rs;	
	GetDlgItemText(IDC_GOOD_NUMBER,num_or_name);
	if(num_or_name.IsEmpty())
		return ;
	if(!CountKeepData(keeptime,false))
		return ;
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	CString sql;
	if(m_GoodChose==GOODID)
	{
		sql.Format("select * from hf_goods where GID = '%s'",num_or_name);
	}else
	{
		sql.Format("select * from hf_goods where GNAME = '%s'",num_or_name);
	}
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		if(rs.IsEOF())
		{
			AfxMessageBox("仓库不存在此商品，请选择录入新商品");
		}else
		{
			int nRow = m_list.GetItemCount();
			CString OnlyID,tmp,CSid;
			CreateOnlyID(OnlyID);
			m_list.InsertItem(nRow,OnlyID);
			CDBVariant var;
			rs.GetFieldValue("GID",var,SQL_C_CHAR);
			CSid = *var.m_pstring;
			m_list.SetItemText(nRow,1,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("GNAME",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,2,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("GPRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2lf",var.m_dblVal);
			m_list.SetItemText(nRow,3,tmp);
			var.Clear();
			m_list.SetItemText(nRow,4,keeptime);
			sql.Format("insert into hf_all_goods values('%s','%s','%s',1)",OnlyID,CSid,keeptime);
			m_db.ExecuteSQL(sql);
			sql.Format("update hf_goods set GNUM = GNUM + 1 where GID = '%s'",CSid);
			m_db.ExecuteSQL(sql);
			CreateOnlyID(tmp);
			sql.Format("insert into hf_instock(emp_id,aonlyid,gid,opdata) values('%s','%s','%s',%s)",g_id,OnlyID,CSid,tmp);
			m_db.ExecuteSQL(sql);
		}
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	rs.Close();
	m_db.Close();
}

void CGoodInDlg::InitView()
{
	LONG style = GetWindowLong(m_list.m_hWnd,GWL_STYLE);
	style &=~LVS_TYPEMASK;
	style |=LVS_REPORT;
	SetWindowLong(m_list.m_hWnd,GWL_STYLE,style);
	DWORD liststyle = m_list.GetExtendedStyle();
	liststyle |=LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(liststyle);
	m_list.InsertColumn(1,"唯一编号",LVCFMT_LEFT,175);
	m_list.InsertColumn(1,"商品编号",LVCFMT_LEFT,125);
	m_list.InsertColumn(2,"商品名称",LVCFMT_LEFT,125);
	m_list.InsertColumn(3,"价格",LVCFMT_LEFT,125);
	m_list.InsertColumn(4,"过期日期",LVCFMT_LEFT,125);
	((CButton*)GetDlgItem(IDC_GOOD_ID))->SetCheck(TRUE);
	m_time = CTime::GetCurrentTime();
	m_new_time = m_time;
	UpdateData(FALSE);
}

void CGoodInDlg::OnGoodNewIn() 
{
	// TODO: Add your control notification handler code here
	CString OnlyId;
	CString newId;
	CString newName;
	CString tmp,keepdata;
	float   newPrice;
	GetDlgItemText(IDC_NEW_GOOD_ID,newId);
	GetDlgItemText(IDC_NEW_GOOD_NAME,newName);
	GetDlgItemText(IDC_NEW_GOOD_PRICE,tmp);
	if(newId.IsEmpty()||newName.IsEmpty()||tmp.IsEmpty()||!CountKeepData(keepdata,true))
	{
		AfxMessageBox("录入信息不完整!");
		return ;
	}
	newPrice = atof(tmp);
	CreateOnlyID(OnlyId);
	CRecordset rs;
	CString sql,con;
	sql.Format("select * from hf_goods where GID = '%s'",newId);
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		if(!rs.IsEOF())
		{
			AfxMessageBox("此商品编号已存在！请选择修改编号录入或录入已存在商品");
			rs.Close();
			m_db.Close();
			return;
		}
		rs.Close();
		sql.Format("insert into hf_goods values('%s','%s','%.2f',1,'%.2f')",newId,newName,newPrice,newPrice);
		m_db.ExecuteSQL(sql);
		int nRow = m_list.GetItemCount();
		m_list.InsertItem(nRow,OnlyId);
		m_list.SetItemText(nRow,1,newId);
		m_list.SetItemText(nRow,2,newName);
		m_list.SetItemText(nRow,3,tmp);
		m_list.SetItemText(nRow,4,keepdata);
		sql.Format("insert into hf_all_goods values('%s','%s','%s',1)",OnlyId,newId,keepdata);
		m_db.ExecuteSQL(sql);
		CreateOnlyID(tmp);
		sql.Format("insert into hf_instock(emp_id,aonlyid,gid,opdata) values('%s','%s','%s',%s)",g_id,OnlyId,newId,tmp);
		m_db.ExecuteSQL(sql);
		SetDlgItemText(IDC_GOOD_NUMBER,newId);
		CString str;
		GetDlgItemText(IDC_NEW_GOOD_SHELF_LIFE,str);
		SetDlgItemText(IDC_KEEP_DAY,str);
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	m_db.Close();
}

BOOL CGoodInDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitView();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGoodInDlg::OnGoodId() 
{
	// TODO: Add your control notification handler code here
	m_GoodChose = GOODID;
}

void CGoodInDlg::OnGoodName() 
{
	// TODO: Add your control notification handler code here
	m_GoodChose = GOODNAME;
}

void CGoodInDlg::CreateOnlyID(CString &OnlyId)
{
	CTime t = CTime::GetCurrentTime();
	SYSTEMTIME time;
	GetLocalTime(&time);
	OnlyId.Format("%d%02d%02d%02d%02d%02d%03d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond(),time.wMilliseconds);
}

void CGoodInDlg::OnGoodExit() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_GOOD_ID))->SetCheck(TRUE);
	while(m_list.DeleteItem(0));
	SetDlgItemText(IDC_GOOD_NUMBER,"");
	SetDlgItemText(IDC_NEW_GOOD_ID,"");
	SetDlgItemText(IDC_NEW_GOOD_NAME,"");
	SetDlgItemText(IDC_NEW_GOOD_PRICE,"");
	SetDlgItemText(IDC_KEEP_DAY,"");
	SetDlgItemText(IDC_NEW_GOOD_SHELF_LIFE,"");
	m_time = CTime::GetCurrentTime();
	m_new_time = m_time;
	UpdateData(FALSE);
	
}

void CGoodInDlg::OnGoodAlter() 
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
				GoBack(j);
			}
		}
	}
}

void CGoodInDlg::GoBack(int idx)
{
	CString gonlyid = m_list.GetItemText(idx,0);
	CString gid = m_list.GetItemText(idx,1);
	CString tmp;
	CString con;
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	CRecordset rs;
	CString sql;
	sql.Format("delete from hf_all_goods where AONLYID = '%s'",gonlyid);
	try
	{
		m_db.ExecuteSQL(sql);
		rs.m_pDatabase = &m_db;
		sql.Format("select * from hf_goods where GID = '%s'",gid);
		rs.Open(CRecordset::dynaset,sql);
		if(!rs.IsEOF())
		{
			CDBVariant var;
			int num; 
			rs.GetFieldValue("GNUM",var,SQL_C_SLONG);
			num = var.m_lVal;
			if(num==1)
			{
				sql.Format("delete from hf_goods where GID = '%s'",gid);
			}else
			{
				sql.Format("update hf_goods set GNUM = GNUM - 1 where GID = '%s'",gid);
			}
			m_db.ExecuteSQL(sql);
		}
		rs.Close();	

	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	m_db.Close();
	m_list.DeleteItem(idx);
}

bool CGoodInDlg::CountKeepData(CString &str,bool isNew)
{
	UpdateData();
	CTime t;
	CString Day;	
	if(isNew)
	{
		GetDlgItemText(IDC_NEW_GOOD_SHELF_LIFE,Day);
		if(Day.IsEmpty())
		{
			return false;
		}
		CTimeSpan sp(atoi(Day),0,0,0);
		t = m_new_time+sp;
	}
	else
	{
		GetDlgItemText(IDC_KEEP_DAY,Day);
		if(Day.IsEmpty())
		{
			AfxMessageBox("没有选择保质天数!");
			return false;
		}
		CTimeSpan sp(atoi(Day),0,0,0);
		t = m_time+sp;	
	}
	str.Format("%04d%02d%02d",t.GetYear(),t.GetMonth(),t.GetDay());	
	return true;
}
