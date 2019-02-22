// Dialog1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pictest1.h"
#include "Dialog1.h"
#include "afxdialogex.h"


// CDialog1 �Ի���

IMPLEMENT_DYNAMIC(CDialog1, CDialogEx)

CDialog1::CDialog1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog1::IDD, pParent)
{

	m_up = 0;
}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UP, m_up);
}


BEGIN_MESSAGE_MAP(CDialog1, CDialogEx)
	ON_BN_CLICKED(IDC_DO, &CDialog1::OnBnClickedDo)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDialog1 ��Ϣ�������


void CDialog1::OnBnClickedDo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CDialog1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
   CRect   rect;   
   GetClientRect(&rect);   
   CDC   dcMem;   
   dcMem.CreateCompatibleDC(&dc);   
   CBitmap   bmpBackground;   
   bmpBackground.LoadBitmap(IDB_BITMAP1); 
   BITMAP   bitmap;   
   bmpBackground.GetBitmap(&bitmap);   
   CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
   dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
}


HBRUSH CDialog1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
    if(nCtlColor == CTLCOLOR_STATIC)
    {
	         pDC->SetTextColor(RGB(0, 111, 255));
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
