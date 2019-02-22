// ImageWnd.h: interface for the CImageWnd class.
//
//该类主要用于创建图片窗口
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEWND_H__29412C4D_6A8A_4BD2_895F_FC45268735FA__INCLUDED_)
#define AFX_IMAGEWND_H__29412C4D_6A8A_4BD2_895F_FC45268735FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageWnd :public CWnd //CImageWnd 类继承自CWnd基类，用于创建窗口
{
public:
	void SetScroll(int cx,int cy);
	void SetImage(int cx,int cy,const void *bits);
	byte *lpBits;
	int nByteWidth;
	int nHeight;
	int nWidth;
	int VScrollPosition;
	int VScrollMax;
	int VCurrentPosition;
	int HScrollPosition;
	int HScrollMax;
	int HCurrentPosition;
	CImageWnd();
	virtual ~CImageWnd();

protected:
//{{AFX_MSG(CImageWnd)       /*用于创建消息*/
afx_msg BOOL OnEraseBkgnd(CDC* pDC);    /*窗口背景消息*/
afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);    /*竖直滚动消息*/
afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);    /*水平滚动消息*/
afx_msg void OnPaint();                        /*窗口前景消息*/
afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);      /*创建窗口消息*/
//}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_IMAGEWND_H__29412C4D_6A8A_4BD2_895F_FC45268735FA__INCLUDED_)
