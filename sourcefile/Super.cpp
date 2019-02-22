// Super.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pictest1.h"
#include "Super.h"
#include "afxdialogex.h"


// CSuper �Ի���

IMPLEMENT_DYNAMIC(CSuper, CDialogEx)

CSuper::CSuper(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSuper::IDD, pParent)
{
	g_nFillMode = 1;//��ˮ����ģʽ
    g_nLowDifference = 50, g_nUpDifference = 50;//�������ֵ���������ֵ
    g_nConnectivity = 4;//��ʾfloodFill������ʶ���Ͱ�λ����ֵͨ
    g_bIsColor = true;//�Ƿ�Ϊ��ɫͼ�ı�ʶ������ֵ
    g_bUseMask = false;//�Ƿ���ʾ��Ĥ���ڵĲ���ֵ
    g_nNewMaskVal = 255;//�µ����»��Ƶ�����ֵ
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


// CSuper ��Ϣ�������


static void onMouse( int event, int x, int y, int, void*)
{
	// ��������û�а��£��㷵��
	imshow("Ч��ͼ", g_grayImage);
	if( event != EVENT_LBUTTONDOWN )
		return;
	//-------------------��<1>����floodFill����֮ǰ�Ĳ���׼�����֡�---------------
	Point seed = Point(x,y);
	int LowDifference =50;//g_nLowDifference;//�շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_nLowDifference
	int UpDifference = 50;//g_nUpDifference;//�շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_nUpDifference
	int flags =4/*g_nConnectivity*/ + (255/*g_nNewMaskVal*/ << 8) + FLOODFILL_FIXED_RANGE;//��ʶ����0~7λΪg_nConnectivity��8~15λΪg_nNewMaskVal����8λ��ֵ��16~23λΪCV_FLOODFILL_FIXED_RANGE����0��

	//�������bgrֵ
	//int b = (unsigned)theRNG() & 255;//�������һ��0~255֮���ֵ
	//int g = (unsigned)theRNG() & 255;//�������һ��0~255֮���ֵ
	//int r = (unsigned)theRNG() & 255;//�������һ��0~255֮���ֵ
	int b = 0;
	int g = 0;
	int r = 0;
	Rect ccomp;//�����ػ��������С�߽��������

	Scalar newVal = Scalar(b, g, r);//���ػ��������ص���ֵ�����ǲ�ɫͼģʽ��ȡScalar(b, g, r)�����ǻҶ�ͼģʽ��ȡScalar(r*0.299 + g*0.587 + b*0.114)

	Mat dst =g_grayImage;//Ŀ��ͼ�ĸ�ֵ
	int area;

	//--------------------��<2>��ʽ����floodFill������-----------------------------
			area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	
	dst.copyTo(g_dstImage);//����Դͼ��Ŀ��ͼ
	imshow("Ч��ͼ", dst);
}

//��ʼ
void CSuper::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������  
	//����ԭͼ
	g_srcImage = imread("small.bmp", 1);

    if( !g_srcImage.data ) { MessageBox(L"Oh��no����ȡͼƬ����~�� "); return; }  

	//��ʾ��������
	//================zijijia
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	//==================zijijiaend
	namedWindow( "Ч��ͼ",WINDOW_NORMAL );

	//���ص�����
	setMouseCallback( "Ч��ͼ",onMouse,0);
}

//�ָ�
void CSuper::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
	imshow("Ч��ͼ", g_grayImage);
}

//ȷ��
void CSuper::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_dstImage.copyTo(g_floodImage);
	namedWindow("ȷ�Ϻ��ͼƬ",WINDOW_NORMAL);
	imshow("ȷ�Ϻ��ͼƬ",g_floodImage);
	imwrite("start1.bmp",g_floodImage);
}

