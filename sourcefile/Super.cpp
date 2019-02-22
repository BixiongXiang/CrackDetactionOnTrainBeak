// Super.cpp : 实现文件
//

#include "stdafx.h"
#include "pictest1.h"
#include "Super.h"
#include "afxdialogex.h"


// CSuper 对话框

IMPLEMENT_DYNAMIC(CSuper, CDialogEx)

CSuper::CSuper(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSuper::IDD, pParent)
{
	g_nFillMode = 1;//漫水填充的模式
    g_nLowDifference = 50, g_nUpDifference = 50;//负差最大值、正差最大值
    g_nConnectivity = 4;//表示floodFill函数标识符低八位的连通值
    g_bIsColor = true;//是否为彩色图的标识符布尔值
    g_bUseMask = false;//是否显示掩膜窗口的布尔值
    g_nNewMaskVal = 255;//新的重新绘制的像素值
}

CSuper::~CSuper()
{
}

void CSuper::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSuper, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSuper::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSuper::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSuper::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSuper 消息处理程序


static void onMouse( int event, int x, int y, int, void*)
{
	// 若鼠标左键没有按下，便返回
	imshow("效果图", g_grayImage);
	if( event != EVENT_LBUTTONDOWN )
		return;
	//-------------------【<1>调用floodFill函数之前的参数准备部分】---------------
	Point seed = Point(x,y);
	int LowDifference =50;//g_nLowDifference;//空范围的漫水填充，此值设为0，否则设为全局的g_nLowDifference
	int UpDifference = 50;//g_nUpDifference;//空范围的漫水填充，此值设为0，否则设为全局的g_nUpDifference
	int flags =4/*g_nConnectivity*/ + (255/*g_nNewMaskVal*/ << 8) + FLOODFILL_FIXED_RANGE;//标识符的0~7位为g_nConnectivity，8~15位为g_nNewMaskVal左移8位的值，16~23位为CV_FLOODFILL_FIXED_RANGE或者0。

	//随机生成bgr值
	//int b = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
	//int g = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
	//int r = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
	int b = 0;
	int g = 0;
	int r = 0;
	Rect ccomp;//定义重绘区域的最小边界矩形区域

	Scalar newVal = Scalar(b, g, r);//在重绘区域像素的新值，若是彩色图模式，取Scalar(b, g, r)；若是灰度图模式，取Scalar(r*0.299 + g*0.587 + b*0.114)

	Mat dst =g_grayImage;//目标图的赋值
	int area;

	//--------------------【<2>正式调用floodFill函数】-----------------------------
			area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	
	dst.copyTo(g_dstImage);//拷贝源图到目标图
	imshow("效果图", dst);
}

//开始
void CSuper::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码  
	//载入原图
	g_srcImage = imread("small.bmp", 1);

    if( !g_srcImage.data ) { MessageBox(L"Oh，no，读取图片错误~！ "); return; }  

	//显示帮助文字
	//================zijijia
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	//==================zijijiaend
	namedWindow( "效果图",WINDOW_NORMAL );

	//鼠标回调函数
	setMouseCallback( "效果图",onMouse,0);
}

//恢复
void CSuper::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
	imshow("效果图", g_grayImage);
}

//确认
void CSuper::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	g_dstImage.copyTo(g_floodImage);
	namedWindow("确认后的图片",WINDOW_NORMAL);
	imshow("确认后的图片",g_floodImage);
	imwrite("start1.bmp",g_floodImage);
}

