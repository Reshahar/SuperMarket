; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInStockDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SuperMarket.h"

ClassCount=11
Class1=CSuperMarketApp
Class2=CSuperMarketDlg

ResourceCount=10
Resource2=IDD_USER_DIALOG
Resource1=IDR_MAINFRAME
Resource3=IDD_SUPERMARKET_DIALOG
Class3=CManagerDlg
Class4=CUserDlg
Resource4=IDD_DIALOG_FEE
Class5=CFeeDlg
Resource5=IDD_GOOD_IN_DLG
Class6=CUserManagerDlg
Resource6=IDD_USER_MANAGER_DLG
Class7=CGoodInDlg
Resource7=IDD_STOCK_MANAGER_DLG
Class8=CSaleManagerDlg
Resource8=IDD_SALE_MANAGER_DLG
Class9=CStockManagerDlg
Class10=CEditListCtrl
Resource9=IDD_MANAGER_DLALOG
Class11=CInStockDlg
Resource10=IDD_IN_STOCK_DLG

[CLS:CSuperMarketApp]
Type=0
HeaderFile=SuperMarket.h
ImplementationFile=SuperMarket.cpp
Filter=N
LastObject=CSuperMarketApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CSuperMarketDlg]
Type=0
HeaderFile=SuperMarketDlg.h
ImplementationFile=SuperMarketDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSuperMarketDlg



[DLG:IDD_SUPERMARKET_DIALOG]
Type=1
Class=CSuperMarketDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_NAME,edit,1350631552
Control4=IDC_PWD,edit,1350631584
Control5=IDC_LOG,button,1342242817
Control6=IDC_EXIT,button,1342242816

[DLG:IDD_MANAGER_DLALOG]
Type=1
Class=CManagerDlg
ControlCount=8
Control1=IDC_TAB,SysTabControl32,1342179584
Control2=IDC_STATIC,button,1342210055
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC_EMP_ID,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_EMP_NAME,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_TIME,static,1342308352

[DLG:IDD_USER_DIALOG]
Type=1
Class=CUserDlg
ControlCount=34
Control1=IDC_SALE,button,1342242817
Control2=IDC_GOOD_NUM,edit,1350631554
Control3=IDC_COMMODITY,SysListView32,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FEE,button,1342242816
Control6=IDC_STATIC,button,1342210055
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_EMP_ID,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC_EMP_NAME,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC_TIME,static,1342308352
Control13=IDC_STATIC,static,1342308864
Control14=IDC_CAN,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_GOOD_ID,button,1342308361
Control17=IDC_GOOD_NAME,button,1342177289
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308865
Control20=IDC_STATIC,static,1342308352
Control21=IDC_GOOD_COUNT,edit,1350631554
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC_MEM_ID,static,1342308363
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC_MEM_NAME,static,1342308363
Control26=IDC_STATIC_MEM_DATA,static,1342308363
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,button,1342177287
Control29=IDC_MEM_IN,button,1342242816
Control30=IDC_STATIC,static,1342308864
Control31=IDC_MEM_NUM_IN,edit,1350631554
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC_MEM_SPEND,static,1342308363
Control34=IDC_STATIC_ALL_SPEND,static,1342308352

[CLS:CManagerDlg]
Type=0
HeaderFile=ManagerDlg.h
ImplementationFile=ManagerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CManagerDlg
VirtualFilter=dWC

[CLS:CUserDlg]
Type=0
HeaderFile=UserDlg.h
ImplementationFile=UserDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_FEE]
Type=1
Class=CFeeDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308864
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FACT_MONEY,edit,1350631554
Control5=IDC_SHOULD_FIND_MONEY,edit,1350631554
Control6=IDC_SHOULD_MONEY,edit,1350633602
Control7=IDC_MY_OK,button,1342242817
Control8=IDC_MY_EXIT,button,1342242816

[CLS:CFeeDlg]
Type=0
HeaderFile=FeeDlg.h
ImplementationFile=FeeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CFeeDlg
VirtualFilter=dWC

[DLG:IDD_USER_MANAGER_DLG]
Type=1
Class=CUserManagerDlg
ControlCount=14
Control1=IDC_STATIC,static,1342308864
Control2=IDC_USER,button,1342177289
Control3=IDC_FIRM,button,1342177289
Control4=IDC_MEMBER,button,1342177289
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308865
Control7=IDC_LIST,SysListView32,1350631427
Control8=IDC_FIND_DATA,button,1342242816
Control9=IDC_ADD,button,1342242816
Control10=IDC_ALTER,button,1342242816
Control11=IDC_EDIT_LIST,edit,1350631552
Control12=IDC_DEL,button,1342242816
Control13=IDC_INSERT,button,1342242816
Control14=IDC_DELETE,button,1342242816

[CLS:CUserManagerDlg]
Type=0
HeaderFile=UserManagerDlg.h
ImplementationFile=UserManagerDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CUserManagerDlg

[DLG:IDD_GOOD_IN_DLG]
Type=1
Class=CGoodInDlg
ControlCount=27
Control1=IDC_STATIC,static,1342308352
Control2=IDC_GOOD_ID,button,1342177289
Control3=IDC_GOOD_NAME,button,1342177289
Control4=IDC_GOOD_NUMBER,edit,1350631552
Control5=IDC_GOOD_IN,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_LIST_GOOD,SysListView32,1350631427
Control9=IDC_STATIC,static,1342308864
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STATIC,static,1342308864
Control12=IDC_STATIC,static,1342308864
Control13=IDC_GOOD_NEW_IN,button,1342242816
Control14=IDC_NEW_GOOD_ID,edit,1350631552
Control15=IDC_NEW_GOOD_NAME,edit,1350631552
Control16=IDC_NEW_GOOD_PRICE,edit,1350631552
Control17=IDC_STATIC,static,1342308353
Control18=IDC_GOOD_EXIT,button,1342242816
Control19=IDC_GOOD_ALTER,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308864
Control22=IDC_NEW_GOOD_SHELF_LIFE,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_KEEP_DAY,edit,1350631552
Control26=IDC_DATETIMEPICKER_OLD,SysDateTimePick32,1342242848
Control27=IDC_DATETIMEPICKER_NEW,SysDateTimePick32,1342242848

[CLS:CGoodInDlg]
Type=0
HeaderFile=GoodInDlg.h
ImplementationFile=GoodInDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CGoodInDlg

[DLG:IDD_SALE_MANAGER_DLG]
Type=1
Class=CSaleManagerDlg
ControlCount=7
Control1=IDC_LIST,SysListView32,1350631427
Control2=IDC_ALTER,button,1342242816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,button,1342177287
Control5=IDC_SHOW,button,1342242816
Control6=IDC_EDIT_ALTER,edit,1350631552
Control7=IDC_STATIC,static,1342308352

[CLS:CSaleManagerDlg]
Type=0
HeaderFile=SaleManagerDlg.h
ImplementationFile=SaleManagerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSaleManagerDlg
VirtualFilter=dWC

[DLG:IDD_STOCK_MANAGER_DLG]
Type=1
Class=CStockManagerDlg
ControlCount=8
Control1=IDC_STOCK_SUN,button,1342177289
Control2=IDC_IN_STOCK,button,1342177289
Control3=IDC_OUT_STOCK,button,1342177289
Control4=IDC_LIST,SysListView32,1350631427
Control5=IDC_STATIC,static,1342308865
Control6=IDC_SHOW,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342177280

[CLS:CStockManagerDlg]
Type=0
HeaderFile=StockManagerDlg.h
ImplementationFile=StockManagerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CStockManagerDlg
VirtualFilter=dWC

[CLS:CEditListCtrl]
Type=0
HeaderFile=EditListCtrl.h
ImplementationFile=EditListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CEditListCtrl

[DLG:IDD_IN_STOCK_DLG]
Type=1
Class=CInStockDlg
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_AUTO_IN_STOCK,button,1342242816
Control3=IDC_LIST,SysListView32,1350631427
Control4=IDC_STATIC,static,1342308865
Control5=IDC_DAY,edit,1350631552
Control6=IDC_STATIC,static,1342308865
Control7=IDC_PRINT,button,1342242816
Control8=IDC_EDIT_LIST,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_NEW_DAY,edit,1350631552

[CLS:CInStockDlg]
Type=0
HeaderFile=InStockDlg.h
ImplementationFile=InStockDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInStockDlg
VirtualFilter=dWC

