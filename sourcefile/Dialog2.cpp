// Dialog2.cpp : 实现文件
//

#include "stdafx.h"
#include "pictest1.h"
#include "Dialog2.h"
#include "afxdialogex.h"


// Dialog2 对话框

IMPLEMENT_DYNAMIC(Dialog2, CDialogEx)

Dialog2::Dialog2(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog2::IDD, pParent)
{

	//  m_yuzhi = 0;
	m_down = 0;
	m_down2 = 0.0;
	m_yuzhi = 0.0;
	str = _T("");
}

Dialog2::~Dialog2()
{
}

void Dialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_YZ, m_yuzhi);
	DDX_Text(pDX, IDC_EDIT_DOWN2, m_down2);
	DDX_Text(pDX, IDC_EDIT_DOWN, m_down);
	DDX_Text(pDX, IDC_EDIT_YZ, m_yuzhi);
	DDX_Control(pDX, IDC_COMBO1, m_pic);
}


BEGIN_MESSAGE_MAP(Dialog2, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Dialog2::OnCbnSelchangeCombo1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_YZ, &Dialog2::OnEnChangeEditYz)
	ON_EN_CHANGE(IDC_EDIT_DOWN, &Dialog2::OnEnChangeEditDown)
	ON_EN_CHANGE(IDC_EDIT_DOWN2, &Dialog2::OnEnChangeEditrate)
END_MESSAGE_MAP()


// Dialog2 消息处理程序


void Dialog2::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	  int index=0;
	  index=m_pic.GetCurSel();
	  m_pic.GetLBText(index,str);
}


void Dialog2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
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


HBRUSH Dialog2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	// TODO:  在此更改 DC 的任何特性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	else 
	return hbr;
}


void Dialog2::OnEnChangeEditYz()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Dialog2::OnEnChangeEditDown()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Dialog2::OnEnChangeEditrate()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
