// Delete.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pictest1.h"
#include "Delete.h"
#include "afxdialogex.h"


// CDelete �Ի���

IMPLEMENT_DYNAMIC(CDelete, CDialogEx)

CDelete::CDelete(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDelete::IDD, pParent)
{

	m_dusername = _T("");
}

CDelete::~CDelete()
{
}

void CDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Dusername, m_dusername);
}


BEGIN_MESSAGE_MAP(CDelete, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDelete ��Ϣ�������


void CDelete::OnPaint()
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


HBRUSH CDelete::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
