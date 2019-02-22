// ImageWnd.h: interface for the CImageWnd class.
//
//������Ҫ���ڴ���ͼƬ����
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEWND_H__29412C4D_6A8A_4BD2_895F_FC45268735FA__INCLUDED_)
#define AFX_IMAGEWND_H__29412C4D_6A8A_4BD2_895F_FC45268735FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageWnd :public CWnd //CImageWnd ��̳���CWnd���࣬���ڴ�������
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
//{{AFX_MSG(CImageWnd)       /*���ڴ�����Ϣ*/
afx_msg BOOL OnEraseBkgnd(CDC* pDC);    /*���ڱ�����Ϣ*/
afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);    /*��ֱ������Ϣ*/
afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);    /*ˮƽ������Ϣ*/
afx_msg void OnPaint();                        /*����ǰ����Ϣ*/
afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);      /*����������Ϣ*/
//}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_IMAGEWND_H__29412C4D_6A8A_4BD2_895F_FC45268735FA__INCLUDED_)
