
// pictest1Dlg.h : ͷ�ļ�
//
#if !defined(AFX_CLDLG_H__DBB2C124_BE02_454D_B800_BF5D83E036E5__INCLUDED_)
#define AFX_CLDLG_H__DBB2C124_BE02_454D_B800_BF5D83E036E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Cpictest1Dlg �Ի���
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "afxext.h"
#include "afxwin.h"
using namespace cv;
using namespace std;
class Cpictest1Dlg : public CDialogEx
{
// ����
public:
	Cpictest1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	void LoadBitmap();
	void LoadsmallBitmap();
	void ezh2(int nWidth,int nHeight,BYTE *lpInput,BYTE *lpOutput,int a);
	void xb2(int nWidth,int nHeight,BYTE *lpInput,BYTE *lpOutput);
	void GetMPoints(int nWidth,int nHeight,BYTE *lpBits,BYTE *lpMPoints);
	void PutMPoints(int nWidth,int nHeight,BYTE *lpBits,BYTE *lpMPoints);
	int nHeight;
	int nWidth;
    int nLen;
    int nByteWidth;
    //BYTE *lpBackup;
    BYTE *lpBitmap;
    BYTE *lpBits;
    CString FileName;
	int m_yuzhi;
	//==================================κ���忪ʼ===========================
	void NiceTestNow(BYTE *lpInput, BYTE *lpOutput);
	void NiceTest();
	int yuzhi(int *l,int count);
	void clear(BYTE *lpInput,int X,int y);
	void set(BYTE *lpInput,int X,int y);
	int ifnextis(BYTE *lpInput,int X,int y);
	int Mid(BYTE *lpInput,int X,int y);
	int length(BYTE *lpInput,int X,int y);
	int *l;
	int picxx;
	//==================κ�������================================
	//=================������ʼ=========================
	Mat g_srcImage,g_dstImage3;
	//Mat g_dstImage1,g_dstImage2,g_dstImage;
	Mat originalImg;
	Mat g_biFINALImage;
    Mat g_biImage,g_medfiltImage;
	Mat img_contour22;
	Mat img_dilate3;
	int g_nGaussianBlurValue;  //��˹�˲�����ֵ
    int g_nGaussianVerticalValue;  //��˹�˲�����ֵ
	double maxgray;

    //Sobel��Ե�����ر���
    Mat g_sobelGradient_X, g_sobelGradient_Y;
    Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
    int g_sobelKernelSize;//TrackBarλ�ò��� 
    //�Ҷ���ֵ��ر���
    int g_binaryThreshold;
    //��ֵ�˲�
    int g_medfiltKernel;
    void on_GaussianBlur(int, void *);//��˹�˲�ģ���˴�С
    void on_GaussianVertical(int, void *);//��˹�˲���ֱģ����׼��
    void ShowHelpText();
    void on_Sobel(int, void*);//Sobel��Ե��ⴰ�ڹ������Ļص�����
    //void on_Binary(int,void*);
    //void on_MedianFilter(int,void*);
	//=====================��������==========
    // �Ի�������
	enum { IDD = IDD_PICTEST1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Resize();
	POINT old;

	afx_msg void OnOpen();
	afx_msg void On32777();
	afx_msg void OnRebg();
	afx_msg void Onhelpview();
	afx_msg void OnClickedOpen();
	afx_msg void OnBnClickedDetect();
	int m_sum;
	afx_msg void OnLwsb();
	afx_msg void OnClickedRes();
	afx_msg void OnBnClickedSege();
	afx_msg void OnBnClickedSob();
	afx_msg void OnBnClickedBin();
	afx_msg void OnBnClickedMed();
	afx_msg void OnBnClickedDilate();
	CBitmapButton m_buttonopen;
	CBitmapButton m_bctp;
	CBitmapButton m_bjjg;
	CBitmapButton m_txycl;
	CBitmapButton m_gslb;
	CBitmapButton m_sobel;
	CBitmapButton m_ezh;
	CBitmapButton m_zzlb;
	CBitmapButton m_pz;
	CBitmapButton lwsb;
	CBitmapButton m_dcjg;
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedComp();
	afx_msg void OnBnClickedButton1();
	double m_max;
	CBitmapButton m_new;
	afx_msg void Onmsave();
	afx_msg void On32788();
	afx_msg void Onmtxyvl();
	afx_msg void Onmgslb();
	afx_msg void Onmsobel();
	afx_msg void Onmezh();
	afx_msg void Onmzzlb();
	afx_msg void Onmpz();
	afx_msg void Onmlwsb2();
	afx_msg void Onmdcdjg();
	afx_msg void OnBnClickedsmall();
	CBitmapButton m_yjtxfg;
	CBitmapButton m_xsyt;
	CBitmapButton m_xsclhtp;
	afx_msg void OnBnClickedOne();
	afx_msg void OnBnClickedAfter();
	afx_msg void OnRegister();
	afx_msg void OnRevise();
	afx_msg void OnDelete();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void Onsuper();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeEditSum();
	afx_msg void OnStnClickedStatic4();
	afx_msg void On23432806();
	CStatic m_Picture;
	CStatic m_Picture1;
};
#endif