#pragma once


// CSuper 对话框

class CSuper : public CDialogEx
{
	DECLARE_DYNAMIC(CSuper)

public:
	CSuper(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSuper();
	Mat g_srcImage,g_maskImage;//定义原始图、目标图、灰度图、掩模图
	int g_nFillMode ;//漫水填充的模式
	int g_nLowDifference ,g_nUpDifference;//负差最大值、正差最大值
	int g_nConnectivity ;//表示floodFill函数标识符低八位的连通值
	int g_bIsColor;//是否为彩色图的标识符布尔值
	bool g_bUseMask;//是否显示掩膜窗口的布尔值
	int g_nNewMaskVal;//新的重新绘制的像素值
	Mat g_floodImage;

// 对话框数据
	enum { IDD = IDD_Super };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
