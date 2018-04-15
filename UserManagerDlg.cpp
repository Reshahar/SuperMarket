// UserManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarket.h"
#include "UserManagerDlg.h"
#include "def.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserManagerDlg dialog

int nlastChose = -1;
int nChose = -1;
CUserManagerDlg::CUserManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManagerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserManagerDlg)
	//}}AFX_DATA_INIT
	m_IDChose=IDUSER;
	m_nRow = -1;
	m_nCol = -1;
}


void CUserManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserManagerDlg)
	DDX_Control(pDX, IDC_EDIT_LIST, m_edit);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CUserManagerDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_USER, OnUser)
	ON_BN_CLICKED(IDC_MEMBER, OnMember)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_EN_KILLFOCUS(IDC_EDIT_LIST, OnKillfocusEditList)
	ON_BN_CLICKED(IDC_FIND_DATA, OnFindData)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_ALTER, OnAlter)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_FIRM, OnFirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManagerDlg message handlers

void CUserManagerDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CUserManagerDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void CUserManagerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(0);
}

void CUserManagerDlg::OnUser() 
{
	// TODO: Add your control notification handler code here
	m_IDChose = IDUSER;
}

void CUserManagerDlg::OnMember() 
{
	// TODO: Add your control notification handler code here
	m_IDChose = IDMEMBER;

}

void CUserManagerDlg::InitView()
{
	LONG style = GetWindowLong(m_list.m_hWnd,GWL_STYLE);
	style &=~LVS_TYPEMASK;
	style |=LVS_REPORT;
	SetWindowLong(m_list.m_hWnd,GWL_STYLE,style);
	DWORD liststyle = m_list.GetExtendedStyle();
	liststyle |=LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
	m_list.SetExtendedStyle(liststyle);
	m_edit.ShowWindow(SW_HIDE);
	((CButton*)GetDlgItem(IDC_USER))->SetCheck(TRUE);
	InitUser();
}

void CUserManagerDlg::InitUser()
{
	while(m_list.DeleteItem(0)); 
	while(m_list.DeleteColumn(0));
	
	m_list.InsertColumn(0,"员工号",LVCFMT_LEFT,125);
	m_list.InsertColumn(1,"姓名",LVCFMT_LEFT,125);
	m_list.InsertColumn(2,"工资",LVCFMT_LEFT,125);
	m_list.InsertColumn(3,"销售总数",LVCFMT_LEFT,125);
	m_list.InsertColumn(4,"销售金额",LVCFMT_LEFT,125);
	m_list.InsertColumn(5,"权限",LVCFMT_LEFT,125);
}

BOOL CUserManagerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitView();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserManagerDlg::ShowUser()
{
	CRecordset rs;
	int salary,sale_num;
	float all_sale;
	CString  con,sql,tmp;
	sql.Format("select * from hf_user");
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			int nRow = m_list.GetItemCount();
			CDBVariant var;
			rs.GetFieldValue("EMP_ID",var,SQL_C_CHAR);
			m_list.InsertItem(nRow,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("NAME",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,1,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("SALARY",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(nRow,2,tmp);
			var.Clear();
			rs.GetFieldValue("SALE_AMOUNT",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal);
			m_list.SetItemText(nRow,3,tmp);
			var.Clear();
			rs.GetFieldValue("SALE_NUM",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_lVal);
			m_list.SetItemText(nRow,4,tmp);
			var.Clear();
			rs.GetFieldValue("POWER",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal);
			m_list.SetItemText(nRow,5,tmp);
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

void CUserManagerDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;  
    int x = 10;
	switch(m_IDChose)
	{
	case IDUSER:
		x = 6;
		break;
	case IDMEMBER:
		x = 5;
		break;
	case IDFIRM:
		x = 4;
		break;
	}
		
	if(pNMListCtrl->iItem != -1 && pNMListCtrl->iSubItem < x)  
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

BOOL CUserManagerDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )   
    {     
        if( GetFocus()->GetDlgCtrlID() == IDC_EDIT_LIST)  
        {  
			m_list.SetFocus();
        }  
        return TRUE;  
    }
	return CDialog::PreTranslateMessage(pMsg);
}

void CUserManagerDlg::OnKillfocusEditList() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString tmp;
	m_edit.GetWindowText(tmp);
	m_list.SetItemText(m_nRow,m_nCol,tmp);
	m_edit.ShowWindow(SW_HIDE);
}

void CUserManagerDlg::OnFindData() 
{
	// TODO: Add your control notification handler code here
	if(nlastChose!=m_IDChose)
	{
		switch(m_IDChose) {
		case IDUSER:
			InitUser();
			ShowUser();
			break;
		case IDMEMBER:
			InitMember();
			ShowMember();
			break;
		case IDFIRM:
			InitFirm();
			ShowFrim();
			break;
		}
		nlastChose = m_IDChose;
	}
	
}

void CUserManagerDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	int n = m_list.GetItemCount();
	m_list.InsertItem(n,"");
}

void CUserManagerDlg::OnAlter() 
{
	// TODO: Add your control notification handler code here
	if(nChose!=m_IDChose)
	{
		switch(m_IDChose) {
		case IDUSER:
			alterUser();
			break;
		case IDMEMBER:
			AlterMember();
			break;
		case IDFIRM:
			AlterFirm();
			break;
		}
		nChose = m_IDChose;
	}
}

void CUserManagerDlg::OnDel() 
{
	// TODO: Add your control notification handler code here
	CString str,sql,id;
	int i,j,n = m_list.GetSelectedCount();
	for(i=0;i<n;i++)
	{
		for(j=0; j<m_list.GetItemCount(); j++)
		{
			if( m_list.GetItemState(j, LVIS_SELECTED) == LVIS_SELECTED)
			{
				id = m_list.GetItemText(j,0);
				switch(m_IDChose) 
				{
				case IDUSER:
					sql.Format("delete from hf_user where emp_id = '%s'",id);
					break;
				case IDMEMBER:
					sql.Format("delete from hf_member where MID = '%s'",id);
					break;
				case IDFIRM:
					sql.Format("delete from hf_firm where FID = '%s'",id);
					break;
				}
				DelOneRow(j,sql);
			}
		}
	}	
}

void CUserManagerDlg::DelOneRow(int idx,CString sql)
{
	CString tmp;
	CString con;
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD);
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	try
	{
		m_db.ExecuteSQL(sql);
		
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);
	}
	m_db.Close();
	m_list.DeleteItem(idx);
}

void CUserManagerDlg::ShowMember()
{
	CRecordset rs;
	int salary,sale_num;
	float all_sale;
	CString  con,sql,tmp;
	sql.Format("select * from hf_member");
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			int nRow = m_list.GetItemCount();
			CDBVariant var;
			rs.GetFieldValue("MID",var,SQL_C_CHAR);
			m_list.InsertItem(nRow,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("MNAME",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,1,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("MEMBERDATA",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal);
			m_list.SetItemText(nRow,2,tmp);
			var.Clear();
			rs.GetFieldValue("MALLSPEND",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(nRow,3,tmp);
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

void CUserManagerDlg::InitMember()
{	
	while(m_list.DeleteItem(0));
	while(m_list.DeleteColumn(0));
	
	m_list.InsertColumn(0,"会员号",LVCFMT_LEFT,150);
	m_list.InsertColumn(1,"姓名",LVCFMT_LEFT,150);
	m_list.InsertColumn(2,"会员剩余天数",LVCFMT_LEFT,150);
	m_list.InsertColumn(3,"总消费金额",LVCFMT_LEFT,150);

}

void CUserManagerDlg::alterUser()
{
	CString  con,sql,tmp,EMP_ID,gNAME,gSALARY,gSALE_AMOUNT,POWER,SALE_NUM;
	int power,sale_amount;
	float salary,salenum;
	int i,count = m_list.GetItemCount();
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	for(i=0;i<count;i++)
	{
		EMP_ID = m_list.GetItemText(i,0);
		gNAME = m_list.GetItemText(i,1);
		gSALARY = m_list.GetItemText(i,2);
		salary = atof(gSALARY);
		gSALE_AMOUNT = m_list.GetItemText(i,3);
		sale_amount = atoi(gSALE_AMOUNT);
		SALE_NUM = m_list.GetItemText(i,4);
		salenum = atof(SALE_NUM);
		POWER = m_list.GetItemText(i,5);
		power = atoi(POWER);
		sql.Format("update hf_user set NAME='%s',SALARY=%.2f,SALE_AMOUNT=%d,SALE_NUM=%.2f,POWER=%d where emp_id= '%s'",gNAME,salary,sale_amount,salenum,power,EMP_ID);		
		try
		{
			m_db.ExecuteSQL(sql);
			AfxMessageBox("修改成功！");
		}catch (CDBException *ex)
		{
			AfxMessageBox(ex->m_strError);
		}
	}
	m_db.Close();
}

void CUserManagerDlg::AlterMember()
{
	CString  con,sql,tmp,MID,MNAME,MEMDATA,MALLSPEND;
	int memdata;
	float allspend;
	int i,count = m_list.GetItemCount();
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	for(i=0;i<count;i++)
	{
		MID = m_list.GetItemText(i,0);
		MNAME = m_list.GetItemText(i,1);
		MEMDATA = m_list.GetItemText(i,2);
		MALLSPEND = m_list.GetItemText(i,3);
		allspend  = atof(MALLSPEND);
		memdata = atoi(MEMDATA);
		sql.Format("update hf_member set MNAME='%s',MEMBERDATA=%d,MALLSPEND=%.2f where MID= '%s'",MNAME,memdata,allspend,MID);		
		try
		{
			m_db.ExecuteSQL(sql);
			AfxMessageBox("修改成功！");
		}catch (CDBException *ex)
		{
			AfxMessageBox(ex->m_strError);
		}
	}
	m_db.Close();
}

void CUserManagerDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	int i,n = m_list.GetItemCount()-1;
	int col =  m_list.GetHeaderCtrl()->GetItemCount();;	
	CString tmp;
	for(i=0;i<col;i++)
	{
		tmp  = m_list.GetItemText(n,i);
		if(!tmp.IsEmpty())
		{
			return ;
		}
	}
	m_list.DeleteItem(n);

}


void CUserManagerDlg::OnInsert() 
{
	// TODO: Add your control notification handler code here
	if(nChose!=m_IDChose)
	{
		switch(m_IDChose)
		{
		case IDUSER:
			InsertUser();
			break;
		case IDMEMBER:
			InsertMember();
			break;
		case IDFIRM:
			InsertFirm();
			break;
		}
		nChose = m_IDChose;
	}
}

void CUserManagerDlg::InsertMember()
{
	CString  con,sql,tmp,MID,MNAME,MEMDATA;
	int memdata;
	int i,n = m_list.GetItemCount()-1;
	MID = m_list.GetItemText(n,0);
	for(i=0;i<n;i++)
	{
		tmp = m_list.GetItemText(i,0);
		if(tmp.Compare(MID)==0)
		{
			AfxMessageBox("编号重复!");
			return;
		}
	}
	MNAME = m_list.GetItemText(n,1);
	MEMDATA = m_list.GetItemText(n,2);
	memdata = atoi(MEMDATA);
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	sql.Format("insert into  hf_member values('%s','%s',%d,0)",MID,MNAME,memdata);		
	try
	{
		m_db.ExecuteSQL(sql);
		AfxMessageBox("添加成功！");
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);

	}
	m_db.Close();
}

void CUserManagerDlg::InsertUser()
{
	CString  con,sql,tmp,EMP_ID,gNAME,gSALARY,gSALE_AMOUNT,POWER,SALE_NUM;
	int memdata;
	int power,sale_amount;
	float salary,salenum;
	int i,n = m_list.GetItemCount()-1;
	EMP_ID = m_list.GetItemText(n,0);
	for(i=0;i<n;i++)
	{
		tmp = m_list.GetItemText(i,0);
		if(tmp.Compare(EMP_ID)==0)
		{
			AfxMessageBox("编号重复!");
			return;
		}
	}	
	gNAME = m_list.GetItemText(i,1);
	gSALARY = m_list.GetItemText(i,2);
	salary = atof(gSALARY);
	POWER = m_list.GetItemText(i,5);
	power = atoi(POWER);
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	sql.Format("insert into  hf_user(EMP_ID,NAME,SALARY,SALE_AMOUNT,SALE_NUM,POWER) values('%s','%s',%.2f,0,0,%d)",EMP_ID,gNAME,gSALARY,power);		
	try
	{
		m_db.ExecuteSQL(sql);
		AfxMessageBox("添加成功！");
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);

	}
	m_db.Close();
}

void CUserManagerDlg::OnFirm() 
{
	// TODO: Add your control notification handler code here
	m_IDChose = IDFIRM;
}

void CUserManagerDlg::InitFirm()
{
	while(m_list.DeleteItem(0));
	while(m_list.DeleteColumn(0));
	
	m_list.InsertColumn(0,"供应商号",LVCFMT_LEFT,100);
	m_list.InsertColumn(1,"供应商名",LVCFMT_LEFT,100);
	m_list.InsertColumn(2,"电话",LVCFMT_LEFT,100);
	m_list.InsertColumn(3,"地址",LVCFMT_LEFT,100);
	m_list.InsertColumn(4,"商品编号",LVCFMT_LEFT,100);
	m_list.InsertColumn(5,"供应量",LVCFMT_LEFT,100);
	m_list.InsertColumn(6,"价格",LVCFMT_LEFT,100);
}

void CUserManagerDlg::ShowFrim()
{
	CRecordset rs;
	int salary,sale_num;
	float all_sale;
	CString  con,sql,tmp;
	sql.Format("select * from firm_info_view");
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	try
	{
		rs.m_pDatabase = &m_db;
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			int nRow = m_list.GetItemCount();
			CDBVariant var;
			rs.GetFieldValue("FID",var,SQL_C_CHAR);
			m_list.InsertItem(nRow,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("FNAME",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,1,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("FPHONE",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,2,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("FADDRESS",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,3,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("GID",var,SQL_C_CHAR);
			m_list.SetItemText(nRow,4,*var.m_pstring);
			var.Clear();
			rs.GetFieldValue("SUPPLYNUM",var,SQL_C_SLONG);
			tmp.Format("%d",var.m_lVal);
			m_list.SetItemText(nRow,5,tmp);
			var.Clear();
			rs.GetFieldValue("PRICE",var,SQL_C_DOUBLE);
			tmp.Format("%.2f",var.m_dblVal);
			m_list.SetItemText(nRow,6,tmp);
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

void CUserManagerDlg::AlterFirm()
{
	CString  con,sql,tmp,FID,FNAME,FPHONE,FADDRESS;
	int i,count = m_list.GetItemCount();
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 
	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	for(i=0;i<count;i++)
	{
		FID = m_list.GetItemText(i,0);
		FNAME = m_list.GetItemText(i,1);
		FPHONE = m_list.GetItemText(i,2);
		FADDRESS = m_list.GetItemText(i,3);
		sql.Format("update hf_firm set FNAME='%s',FPHONE='%s',FADDRESS='%s' where FID= '%s'",FNAME,FPHONE,FADDRESS,FID);		
		try
		{
			m_db.ExecuteSQL(sql);
			AfxMessageBox("修改成功！");
		}catch (CDBException *ex)
		{
			AfxMessageBox(ex->m_strError);
		}
	}
	m_db.Close();
}

void CUserManagerDlg::InsertFirm()
{
	CString  con,sql,tmp,FID,FNAME,FPHONE,FADDRESS;
	int i,n = m_list.GetItemCount()-1;
	FID = m_list.GetItemText(n,0);
	for(i=0;i<n;i++)
	{
		tmp = m_list.GetItemText(i,0);
		if(tmp.Compare(FID)==0)
		{
			AfxMessageBox("编号重复!");
			return;
		}
	}
	FNAME = m_list.GetItemText(n,1);
	FPHONE = m_list.GetItemText(n,2);
	FADDRESS = m_list.GetItemText(n,3);
	con.Format("DSN=%s;UID=%s;PWD=%s",g_DSN,g_UID,g_PWD); 	
	if(!m_db.OpenEx(con,0))
	{
		AfxMessageBox("ON");
	}
	sql.Format("insert into  hf_firm values('%s','%s','%s','%s')",FID,FNAME,FPHONE,FADDRESS);		
	try
	{
		m_db.ExecuteSQL(sql);
		AfxMessageBox("添加成功！");
	}catch (CDBException *ex)
	{
		AfxMessageBox(ex->m_strError);

	}
	m_db.Close();
}
