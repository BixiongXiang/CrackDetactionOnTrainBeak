#include "StdAfx.h"
#include "ImageWnd.h"
#include "pictest1.h"
#define BACKGROUND RGB(128,128,128) 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*初始化窗口参数*/
CImageWnd::CImageWnd()
{
	HScrollPosition=0;
	HCurrentPosition=0;
	HScrollMax=0;
	VScrollPosition=0;
	VCurrentPosition=0;
	VScrollMax=0;
	lpBits=0;
}

CImageWnd::~CImageWnd()
{
	/*析构函数用于删除*/
	if (lpBits) delete lpBits;  
}

BEGIN_MESSAGE_MAP(CImageWnd, CWnd) 
//{{AFX_MSG_MAP(CImageWnd)
/*绘制背景*/
ON_WM_ERASEBKGND()   
/*控件竖直滚动触发*/
ON_WM_HSCROLL()
/*控件水平滚动触发*/      
ON_WM_VSCROLL() 
/*绘制前景*/     
ON_WM_PAINT()
/*创建消息映射*/       
ON_WM_CREATE()       
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CImageWnd::SetImage(int cx, int cy, const void *bits)
{
	nWidth=cx;
	nHeight=cy;
	/*处理的为24位的真彩图，一个像素占三个字节*/
	nByteWidth=nWidth*3;   
	/*Windows规定一个扫描行所占的字节数必须是4的倍数，所以向数轴右方向取最接近nByteWidth的4的倍数，将其赋予nByteWidth*/
	if (nByteWidth%4) nByteWidth+=4-(nByteWidth%4); 
	/*释放指针*/
	if (lpBits) delete lpBits;
	/*指向图像数据像素所占字节*/
	lpBits=new BYTE[nByteWidth*nHeight];
	memcpy(lpBits,bits,nByteWidth*nHeight);
	/*判断大小，设置垂直水平滚轮*/
	if (cx>320 || cy>240) SetScroll(cx,cy);
	else SetScroll(0,0);
	Invalidate();
}

/*设置滚轮的函数*/
void CImageWnd::SetScroll(int cx, int cy)
{
	HScrollPosition=0;
	HCurrentPosition=0;
	VScrollPosition=0;
	VCurrentPosition=0;
	SetScrollPos(SB_HORZ,0);
	SetScrollPos(SB_VERT,0);
	SCROLLINFO sinfo;
	sinfo.cbSize=sizeof(SCROLLINFO);
	sinfo.fMask=SIF_PAGE|SIF_RANGE;
	sinfo.nMin=0;
	
	//HScroll
	sinfo.nMax=cx-1;
	sinfo.nPage=302;
	SetScrollInfo(SB_HORZ,&sinfo);
	HScrollMax=cx-302;
	
	//VScroll
	sinfo.nMax=cy-1;
	sinfo.nPage=222;
	SetScrollInfo(SB_VERT,&sinfo);
	VScrollMax=cy-222;
}

BOOL CImageWnd::OnEraseBkgnd(CDC* pDC)
{
	/*创建矩形图像窗的背景颜色*/
	if (!lpBits) pDC->FillSolidRect(0,0,320,240,BACKGROUND);
	return TRUE;
}

void CImageWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (lpBits)
	{
		int x,y;
		x=-HScrollPosition;
		y=-VScrollPosition;
		if (nWidth<320) x=(320-nWidth)/2;
		if (nHeight<240) y=(240-nHeight)/2;
		/*位图信息头结构体*/
		BITMAPINFOHEADER bmi;
		/*结构体大小*/
		bmi.biSize=sizeof(BITMAPINFOHEADER);
		/*位图长宽*/
		bmi.biWidth=nWidth;
		bmi.biHeight=nHeight;
		/*位图层数，必须为1*/
		bmi.biPlanes=1;
		/*为24位图像*/
		bmi.biBitCount=24;
		/*颜色为RGB模式*/
		bmi.biCompression=BI_RGB;
		/*图像大小*/
		bmi.biSizeImage=0;
		bmi.biXPelsPerMeter=0;
		bmi.biYPelsPerMeter=0;
		/*24位bmp一班为零，不为零时表示色彩表中的条目数*/
		bmi.biClrUsed=0;
		bmi.biClrImportant=0;
		/*将位图的颜色数据拷贝到图像窗口*/
		StretchDIBits(dc.m_hDC,x,y,nWidth,nHeight,0,0,nWidth,nHeight,lpBits,
			(BITMAPINFO *)&bmi,DIB_RGB_COLORS,SRCCOPY);
	}
}

/*垂直滚轮的移动*/
void CImageWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch(nSBCode)
	{
	case SB_LINEDOWN:
		HScrollPosition+=5;
		break;
	case SB_LINEUP:
		HScrollPosition-=5;
		break;
	case SB_PAGEDOWN:
		HScrollPosition+=302;
		break;
	case SB_PAGEUP:
		HScrollPosition-=302;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		HScrollPosition=nPos;
		break;
	}
	if (HScrollPosition<0) HScrollPosition=0;
	if (HScrollPosition>HScrollMax) HScrollPosition=HScrollMax;
	SetScrollPos(SB_HORZ,HScrollPosition);
	if (HCurrentPosition!=HScrollPosition)
	{
		ScrollWindow((HCurrentPosition-HScrollPosition),0);
		HCurrentPosition=HScrollPosition;
	}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*水平滚轮的移动*/
void CImageWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch(nSBCode)
	{
	case SB_LINEDOWN:
		VScrollPosition+=5;
		break;
	case SB_LINEUP:
		VScrollPosition-=5;
		break;
	case SB_PAGEDOWN:
		VScrollPosition+=222;
		break;
	case SB_PAGEUP:
		VScrollPosition-=222;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		VScrollPosition=nPos;
		break;
	}
	if (VScrollPosition<0) VScrollPosition=0;
	if (VScrollPosition>VScrollMax) VScrollPosition=VScrollMax;
	SetScrollPos(SB_VERT,VScrollPosition);
	if (VCurrentPosition!=VScrollPosition)
	{
		ScrollWindow(0,(VCurrentPosition-VScrollPosition));
		VCurrentPosition=VScrollPosition;
	}
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

/*判断是否顺利生成*/
int CImageWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}
