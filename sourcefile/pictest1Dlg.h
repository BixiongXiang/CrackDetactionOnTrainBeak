
// pictest1Dlg.h : 头文件
//
#if !defined(AFX_CLDLG_H__DBB2C124_BE02_454D_B800_BF5D83E036E5__INCLUDED_)
#define AFX_CLDLG_H__DBB2C124_BE02_454D_B800_BF5D83E036E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Cpictest1Dlg 对话框
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "afxext.h"
#include "afxwin.h"
using namespace cv;
using namespace std;
class Cpictest1Dlg : public CDialogEx
{
// 构造
public:
	Cpictest1Dlg(CWnd* pParent = NULL);	// 标准构造函数
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
	//==================================魏建峰开始===========================
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
	//==================魏建峰结束================================
	//=================其他开始=========================
	Mat g_srcImage,g_dstImage3;
	//Mat g_dstImage1,g_dstImage2,g_dstImage;
	Mat originalImg;
	Mat g_biFINALImage;
    Mat g_biImage,g_medfiltImage;
	Mat img_contour22;
	Mat img_dilate3;
	int g_nGaussianBlurValue;  //高斯滤波参数值
    int g_nGaussianVerticalValue;  //高斯滤波参数值
	double maxgray;

    //Sobel边缘检测相关变量
    Mat g_sobelGradient_X, g_sobelGradient_Y;
    Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
    int g_sobelKernelSize;//TrackBar位置参数 
    //灰度阈值相关变量
    int g_binaryThreshold;
    //中值滤波
    int g_medfiltKernel;
    void on_GaussianBlur(int, void *);//高斯滤波模糊核大小
    void on_GaussianVertical(int, void *);//高斯滤波垂直模糊标准差
    void ShowHelpText();
    void on_Sobel(int, void*);//Sobel边缘检测窗口滚动条的回调函数
    //void on_Binary(int,void*);
    //void on_MedianFilter(int,void*);
	//=====================其他结束==========
    // 对话框数据
	enum { IDD = IDD_PICTEST1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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