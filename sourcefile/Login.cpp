// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pictest1.h"
#include "Login.h"
#include "afxdialogex.h"
#include "afxdao.h"


// CLogin �Ի���

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


// CLogin ��Ϣ�������


void CLogin::OnBnClickedLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	CDaoDatabase db;                                       //���ݿ�
        CDaoRecordset RecSet(&db);                   //��¼��
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
		AfxMessageBox(_T("�û������������"));
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
	// TODO:  �ڴ˸��� DC ���κ�����
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	else 
	return hbr;
}



//BOOL CLogin::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	CDC dc;  
//   dc.CreateCompatibleDC(pDC); 
//   CBitmap m_Back;  
//   m_Back.LoadBitmap(IDB_BITMAP1); 
//   dc.SelectObject(&m_Back); 
//   BITMAP hb; 
//   m_Back.GetBitmap(&hb);   //��ȡ���ڴ�С
//   CRect rt; 
//   GetClientRect(&rt);  //��ʾλͼ 
//   pDC->StretchBlt(0, 0, rt.Width(), rt.Height(),&dc, 0, 0, hb.bmWidth, hb.bmHeight, SRCCOPY);
//   //return TRUE; 
//
//
//	return CDialogEx::OnEraseBkgnd(pDC);
//}


void CLogin::OnPaint()
{
   CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	// todo: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� cdialogex::onpaint()

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
	font.CreatePointFont(200,_T("����"),NULL);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	GetDlgItem(IDC_STATIC1)->SetFont(&font);
}
