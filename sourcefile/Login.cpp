// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "pictest1.h"
#include "Login.h"
#include "afxdialogex.h"
#include "afxdao.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
{

	m_key = _T("");
	m_username = _T("");
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
	//  DDX_Control(pDX, IDC_EDIT_USER, m_username);
	DDX_Text(pDX, IDC_EDIT_USER, m_username);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN, &CLogin::OnBnClickedLogin)
//	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLogin 消息处理程序


void CLogin::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	CDaoDatabase db;                                       //数据库
        CDaoRecordset RecSet(&db);                   //记录集
	CString m_searchSQL,m_searchSQL2;
	db.Open(_T("test.mdb"),FALSE,FALSE);
	//RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM test",NULL);
	UpdateData(true);
	m_searchSQL.Format(_T("select username,key from test where key='%s' and username='%s'"),m_key,m_username);
	//m_searchSQL2.Format("select username from test where username='%s'",m_username);
	RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,m_searchSQL);
	//RecSet2.Open(AFX_DAO_USE_DEFAULT_TYPE,m_searchSQL2);
	if(RecSet.GetRecordCount()!=1)
        {
	        ok=true;
	}
	else
	{
		AfxMessageBox(_T("用户名或密码错误！"));
		ok=false;
	}
	RecSet.Close();
	db.Close();
	*/
	ok = true;
	CDialogEx::OnOK();
}


HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
    if(nCtlColor == CTLCOLOR_STATIC)
    {
	         pDC->SetTextColor(RGB(0, 0, 0));
			 pDC-> SetBkMode(TRANSPARENT);
			 return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	} 
	else if(nCtlColor == CTLCOLOR_EDIT)
	{
		     pDC->SetTextColor(RGB(0, 111, 255));
			 pDC-> SetBkMode(TRANSPARENT);
			 return (HBRUSH)::GetStockObject(WHITE_BRUSH); 
	} 
	else if(nCtlColor == CTLCOLOR_BTN)
	{
			 pDC-> SetBkMode(TRANSPARENT);
			 return (HBRUSH)::GetStockObject(NULL_BRUSH); 
	} 
	// TODO:  在此更改 DC 的任何特性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	else 
	return hbr;
}



//BOOL CLogin::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CDC dc;  
//   dc.CreateCompatibleDC(pDC); 
//   CBitmap m_Back;  
//   m_Back.LoadBitmap(IDB_BITMAP1); 
//   dc.SelectObject(&m_Back); 
//   BITMAP hb; 
//   m_Back.GetBitmap(&hb);   //获取窗口大小
//   CRect rt; 
//   GetClientRect(&rt);  //显示位图 
//   pDC->StretchBlt(0, 0, rt.Width(), rt.Height(),&dc, 0, 0, hb.bmWidth, hb.bmHeight, SRCCOPY);
//   //return TRUE; 
//
//
//	return CDialogEx::OnEraseBkgnd(pDC);
//}


void CLogin::OnPaint()
{
   CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	// todo: 在此处添加消息处理程序代码
	// 不为绘图消息调用 cdialogex::onpaint()

   CRect  rect;   
   GetClientRect(&rect);   
   CDC   dcMem;   
   dcMem.CreateCompatibleDC(&dc);   
   CBitmap   bmpBackground;   
   bmpBackground.LoadBitmap(IDB_BITMAP1); 
   BITMAP   bitmap;   
   bmpBackground.GetBitmap(&bitmap);   
   CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
   dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
   CFont font;
	font.CreatePointFont(200,_T("隶书"),NULL);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	GetDlgItem(IDC_STATIC1)->SetFont(&font);
}
