
// pictest1Dlg.cpp : 实现文件
//
#include "stdafx.h"
#include "pictest1.h"
#include "pictest1Dlg.h"
#include "afxdialogex.h"
#include "Dialog1.h"
#include "Dialog2.h"
#include "Super.h"
#include "Register.h"
#include "Revise.h"
#include "Delete.h"
#include "afxdao.h"
#include "resource.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/objdetect/objdetect_c.h>
#include <string>
//#include <math.h>
using namespace cv;
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cpictest1Dlg 对话框
Cpictest1Dlg::Cpictest1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cpictest1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lpBitmap=0;
	//lpBackup=0;
	l = new int[200];
	m_sum = 0;
	g_sobelKernelSize=1;//TrackBar位置参数 
	//灰度阈值相关变量
	g_binaryThreshold = 11;
	//中值滤波
	g_medfiltKernel = 7;
	g_nGaussianBlurValue=7;  //高斯滤波参数值
	g_nGaussianVerticalValue=10;  //高斯滤波参数值
	m_max = 0.0;
	maxgray=255;
}

void Cpictest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//  DDX_Text(pDX, IDC_EDIT_MAX, m_max);
	//  DDX_Text(pDX, IDC_EDIT_SUM, m_sum);
	//  DDX_Text(pDX, IDC_EDIT_MAX, m_max);
	DDX_Text(pDX, IDC_EDIT_SUM, m_sum);
	DDX_Control(pDX, IDC_OPEN, m_buttonopen);
	DDX_Control(pDX, IDC_SAVE, m_bctp);
	DDX_Control(pDX, IDC_COMP, m_bjjg);
	DDX_Control(pDX, IDC_REBG, m_txycl);
	DDX_Control(pDX, IDC_SEGE, m_gslb);
	DDX_Control(pDX, IDC_SOB, m_sobel);
	DDX_Control(pDX, IDC_BIN, m_ezh);
	DDX_Control(pDX, IDC_MED, m_zzlb);
	DDX_Control(pDX, IDC_DILATE, m_pz);
	DDX_Control(pDX, IDC_DETECT, lwsb);
	DDX_Control(pDX, IDC_RES, m_dcjg);
	//  DDX_Control(pDX, IDC_COMBO1, m_pic);
	DDX_Text(pDX, IDC_EDIT_MAX, m_max);
	DDX_Control(pDX, IDC_BUTTON1, m_new);
	DDX_Control(pDX, IDC_ONE, m_yjtxfg);
	DDX_Control(pDX, IDC_small, m_xsyt);
	DDX_Control(pDX, IDC_AFTER, m_xsclhtp);
	DDX_Control(pDX, IDC_PICTURE_STATIC, m_Picture1);
}

BEGIN_MESSAGE_MAP(Cpictest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OPEN, &Cpictest1Dlg::OnOpen)
	ON_COMMAND(ID_32777, &Cpictest1Dlg::On32777)
	ON_BN_CLICKED(IDC_REBG, &Cpictest1Dlg::OnRebg)
	ON_COMMAND(ID_helpview, &Cpictest1Dlg::Onhelpview)
	ON_BN_CLICKED(IDC_OPEN, &Cpictest1Dlg::OnClickedOpen)
	ON_BN_CLICKED(IDC_DETECT, &Cpictest1Dlg::OnBnClickedDetect)
	ON_COMMAND(ID_LWSB, &Cpictest1Dlg::OnLwsb)
	ON_BN_CLICKED(IDC_RES, &Cpictest1Dlg::OnClickedRes)
	ON_BN_CLICKED(IDC_SEGE, &Cpictest1Dlg::OnBnClickedSege)
	ON_BN_CLICKED(IDC_SOB, &Cpictest1Dlg::OnBnClickedSob)
	ON_BN_CLICKED(IDC_BIN, &Cpictest1Dlg::OnBnClickedBin)
	ON_BN_CLICKED(IDC_MED, &Cpictest1Dlg::OnBnClickedMed)
	ON_BN_CLICKED(IDC_DILATE, &Cpictest1Dlg::OnBnClickedDilate)
	ON_BN_CLICKED(IDC_SAVE, &Cpictest1Dlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_COMP, &Cpictest1Dlg::OnBnClickedComp)
	ON_BN_CLICKED(IDC_BUTTON1, &Cpictest1Dlg::OnBnClickedButton1)
	ON_COMMAND(ID_msave, &Cpictest1Dlg::Onmsave)
	ON_COMMAND(ID_32788, &Cpictest1Dlg::On32788)
	ON_COMMAND(ID_mtxyvl, &Cpictest1Dlg::Onmtxyvl)
	ON_COMMAND(ID_mgslb, &Cpictest1Dlg::Onmgslb)
	ON_COMMAND(ID_msobel, &Cpictest1Dlg::Onmsobel)
	ON_COMMAND(ID_mezh, &Cpictest1Dlg::Onmezh)
	ON_COMMAND(ID_mzzlb, &Cpictest1Dlg::Onmzzlb)
	ON_COMMAND(ID_mpz, &Cpictest1Dlg::Onmpz)
	ON_COMMAND(ID_mlwsb2, &Cpictest1Dlg::Onmlwsb2)
	ON_COMMAND(ID_mdcdjg, &Cpictest1Dlg::Onmdcdjg)
	ON_BN_CLICKED(IDC_small, &Cpictest1Dlg::OnBnClickedsmall)
	ON_BN_CLICKED(IDC_ONE, &Cpictest1Dlg::OnBnClickedOne)
	ON_BN_CLICKED(IDC_AFTER, &Cpictest1Dlg::OnBnClickedAfter)
	ON_COMMAND(ID_Register, &Cpictest1Dlg::OnRegister)
	ON_COMMAND(ID_Revise, &Cpictest1Dlg::OnRevise)
	ON_COMMAND(ID_Delete, &Cpictest1Dlg::OnDelete)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_super, &Cpictest1Dlg::Onsuper)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT_SUM, &Cpictest1Dlg::OnEnChangeEditSum)
	ON_STN_CLICKED(IDC_STATIC4, &Cpictest1Dlg::OnStnClickedStatic4)
	ON_COMMAND(ID_234_32806, &Cpictest1Dlg::On23432806)
END_MESSAGE_MAP()


// Cpictest1Dlg 消息处理程序

BOOL Cpictest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//绘制名字为Source，类型为子窗口且可见的长方形（绘图区），编号为10000
	//source.Create(0,LPCTSTR("Source"),WS_CHILD|WS_VISIBLE,CRect(40,40,360,280), this, 10000);
	//绘制名字为Destination，类型为子窗口且可见的长方形（绘图区），编号为10001
    //Create(0,LPCTSTR("Destination"),WS_CHILD|WS_VISIBLE,CRect(450,40,770,280), this, 10001);
	m_buttonopen.LoadBitmaps(IDB_BITMAP2,IDB_BITMAP3);   //载入  
	m_buttonopen.SizeToContent();  //使按钮适应图片大小
	m_bctp.LoadBitmaps(IDB_bctp1,IDB_bctp2);   //载入  
	m_bctp.SizeToContent();
	m_bjjg.LoadBitmaps(IDB_bjjg1,IDB_bjjg2);   //载入  
	m_bjjg.SizeToContent();
	m_txycl.LoadBitmaps(IDB_txycl1,IDB_txycl2);   //载入  
	m_txycl.SizeToContent();
	m_gslb.LoadBitmaps(IDB_gslb1,IDB_gslb2);   //载入  
	m_gslb.SizeToContent();
	m_sobel.LoadBitmaps(IDB_sobel1,IDB_sobel2);   //载入  
	m_sobel.SizeToContent();
	m_zzlb.LoadBitmaps(IDB_zzlb1,IDB_zzlb2);   //载入  
	m_zzlb.SizeToContent();
	m_ezh.LoadBitmaps(IDB_ezh1,IDB_ezh2);   //载入  
	m_ezh.SizeToContent();
	m_pz.LoadBitmaps(IDB_pz1,IDB_pz2);   //载入  
	m_pz.SizeToContent();
	lwsb.LoadBitmaps(IDB_lwsb1,IDB_lwsb2);   //载入  
	lwsb.SizeToContent();
	m_dcjg.LoadBitmaps(IDB_dcjg1,IDB_dcjg2);   //载入  
	m_dcjg.SizeToContent();
	m_new.LoadBitmaps(IDB_BITMAP4,IDB_BITMAP5);   //载入  
	m_new.SizeToContent();
	m_yjtxfg.LoadBitmaps(IDB_yjlwfg,IDB_yjlwfg1);   //载入  
	m_yjtxfg.SizeToContent();
	m_xsyt.LoadBitmaps(IDB_xsyt,IDB_xsyt1);   //载入  
	m_xsyt.SizeToContent();
	m_xsclhtp.LoadBitmaps(IDB_xsclhtp,IDB_xsclhtp1);   //载入  
	m_xsclhtp.SizeToContent();

	CRect rect;
	GetClientRect(&rect);
	old.x=rect.right-rect.left;
	old.y=rect.bottom-rect.top;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cpictest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cpictest1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	CPaintDC dc(this); // device context for painting
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cpictest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cpictest1Dlg::LoadBitmap()
{
BITMAPINFOHEADER *pInfo;
pInfo=(BITMAPINFOHEADER *)(lpBitmap+sizeof(BITMAPFILEHEADER));//位图信息头指针，指向lpBitmap内存区中BITMAPFILEHEADER区后首地址 
nWidth=pInfo->biWidth;//从位图信息头中取出位图宽度信息赋给变量nWidth 
nByteWidth=nWidth*3;//每行图像所占字节数目为图像宽度的3倍（24位真彩色图像）
if (nByteWidth%4)
 nByteWidth+=4-(nByteWidth%4); //每行图像所占字节数目必须补齐为4的整数倍
nHeight=pInfo->biHeight;
if (pInfo->biBitCount!=24) //若图像不是真彩色图像，需转换
{
   if (pInfo->biBitCount!=8)//若图像非8位图像，释放lpBitmap内存，结束程序
   {
      MessageBox(_T("无效位图"));
      delete lpBitmap;
      lpBitmap=0;
      return;
   }
   unsigned int PaletteSize=1<<pInfo->biBitCount;//计算调色板大小，左移运算符，左移n位，相当于2的n次幂 
      if (pInfo->biClrUsed!=0 && pInfo->biClrUsed<PaletteSize)//若biClrUsed不为零，调色板大小等于实际使用的颜色数
		  PaletteSize=pInfo->biClrUsed;
      lpBits=lpBitmap+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);//lpBits指向为8位图像调色板区
      RGBQUAD *pPalette=(RGBQUAD *)lpBits;//RGBQUAD为调色板数组元素的结构体，此时定义调色板数组指针pPalette，与lpBits指向同一内存位置 
      lpBits+=sizeof(RGBQUAD)*PaletteSize;//使lpBits指向8位图像的数据区 
      nLen=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+nByteWidth*nHeight;//24位位图文件字节大小 
      BYTE *lpTemp=lpBitmap;//新定义lpTemp指向原lpBitmap对应的内存区 
      lpBitmap=new BYTE[nLen];//新开辟一块容纳24位位图文件的内存区，指向该新内存的指针为lpBitmap 
	  BITMAPFILEHEADER bmh;
      BITMAPINFOHEADER bmi;
      //获取位图文件头各相关信息
	  bmh.bfType='B'+'M'*256;
      bmh.bfSize=nLen;
      bmh.bfReserved1=0;
      bmh.bfReserved2=0;
      bmh.bfOffBits=54;
	  //获取位图信息头各相关信息
      bmi.biSize=sizeof(BITMAPINFOHEADER);
      bmi.biWidth=nWidth;
      bmi.biHeight=nHeight;
      bmi.biPlanes=1;
      bmi.biBitCount=24;//处理后的位图文件均为24位
      bmi.biCompression=BI_RGB;
      bmi.biSizeImage=0;
      bmi.biXPelsPerMeter=0;
      bmi.biYPelsPerMeter=0;
      bmi.biClrUsed=0;
      bmi.biClrImportant=0;
      int nBWidth=pInfo->biWidth;//再次从8位位图信息头中读出每行图像数目
      if (nBWidth%4)
		  nBWidth+=4-(nBWidth%4);//每行图像所占字节数目必须补齐为4的整数倍 
      memset(lpBitmap,0,nLen);//lpBitmap指向的内存区全部nLen字节置0 
      memcpy(lpBitmap,&bmh,sizeof(BITMAPFILEHEADER));//写入位图文件
      memcpy(lpBitmap+sizeof(BITMAPFILEHEADER),&bmi,sizeof(BITMAPINFOHEADER));//写入位图文件
      BYTE *lpBits2=lpBitmap+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);//定义新指针lpBits2指向24位图像数据区 
      int x,y,p1,p2,Palette;
	   //逐行逐列按像素转换
      for(y=0;y<nHeight;y++)//每行
	  {
          for(x=0;x<nWidth;x++)//每列
		  {
             p1=y*nBWidth+x;;//从图像底部开始，原8位图像的第y行第x列像素 
             p2=y*nByteWidth+x*3;//从图像底部开始，新24位图像的第y行第x列像素 
			 //lpBits此时指向8位图像的数据区，若第y行第x列像素数据小于调色板大小，该像素数据即为相应的调色板索引值 
             if (lpBits[p1]<PaletteSize)
				 Palette=lpBits[p1];
             else Palette=0;
			 //根据调色板索引值，获得新24位图像在该像素位置处的三原色信息并填入新图像内存中 
             lpBits2[p2]=pPalette[Palette].rgbBlue;
             lpBits2[p2+1]=pPalette[Palette].rgbGreen;
             lpBits2[p2+2]=pPalette[Palette].rgbRed;
		  }
	  }
      delete lpTemp;//删除lpTemp指向的原始8位图像内存区 
}
lpBits=lpBitmap+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);//使lpBits指向24位图像的数据区 
//if (lpBackup)
  //delete lpBackup;
//lpBackup=new BYTE[nLen];//将刚刚生成的去掉调色板的lpBitmap所指图像在lpBackup所指内存区域备份，已备后面使用  
//memcpy(lpBackup,lpBitmap,nLen);//把位图数据写入位图文件 
}


//===================菜单—文件—打开=================
void Cpictest1Dlg::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	OnClickedOpen();
}

//===================菜单-帮助-关于=================
void Cpictest1Dlg::On32777()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("自动检测刹车盘裂纹系统使用说明：\n点击打开原图按钮选择一张bmp格式的刹车盘图像；点击图像预处理；按照高斯滤波、Sobel边缘检测、二值化边缘检测、中值滤波、膨胀的顺序处理图像（或者使用一键裂纹分割功能）；完成裂纹分割之后点击裂纹识别；点击显示处理后图像；点击比较结果显示处理后图像和原图像叠加图。"),_T("说明"));
	//system("rundll32.exe user32.dll,LockWorkStation ");
	//system("shutdown -h");
}


//===================按下“图像预处理”=============
void Cpictest1Dlg::OnRebg()
{
	// TODO: 在此添加控件通知处理程序代码
	m_txycl.EnableWindow();  
	CDialog1 Dialog1;
	if(Dialog1.DoModal()==IDOK)
	{   int a=Dialog1.m_up;
		if (!lpBitmap)
		{
			MessageBox(_T("请先打开图片！"));
            return;	
		}
	    BYTE *lpOutput=new BYTE[nByteWidth*nHeight];
	    ezh2(nWidth,nHeight,lpBits,lpOutput,a);
	    xb2(nWidth,nHeight,lpOutput,lpOutput);
		CFile file;
		file.Open(_T("start.bmp"),CFile::modeWrite|CFile::modeCreate);
		int nLen=nByteWidth*nHeight;
		BYTE *pMem=new BYTE[nLen+sizeof(BITMAPINFOHEADER)];
		BITMAPINFOHEADER *bmi=(BITMAPINFOHEADER *)pMem;
		bmi->biSize=sizeof(BITMAPINFOHEADER);
		bmi->biWidth=nWidth;
		bmi->biHeight=nHeight;
		bmi->biPlanes=1;
		bmi->biBitCount=24;
		bmi->biCompression=BI_RGB;
		bmi->biSizeImage=0;
		bmi->biXPelsPerMeter=0;
		bmi->biYPelsPerMeter=0;
		bmi->biClrUsed=0;
		bmi->biClrImportant=0;
		BITMAPFILEHEADER bmh;
		bmh.bfType='B'+'M'*256;
		bmh.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+nLen;
		bmh.bfReserved1=0;
		bmh.bfReserved2=0;
		bmh.bfOffBits=54;

		memcpy(pMem+sizeof(BITMAPINFOHEADER),lpOutput,nLen);
		file.Write(&bmh,sizeof(BITMAPFILEHEADER));
		file.Write(pMem,nLen+sizeof(BITMAPINFOHEADER));
		file.Close();
        delete lpOutput;
		
		g_srcImage = imread("start.bmp");
	    if( !g_srcImage.data ) { MessageBox(_T("Oh，no，读取图像错误~！")); }
		namedWindow("预处理后的图像",0);
		imshow("预处理后的图像",g_srcImage);
	}

}

//===================菜单-查看帮助=============
void Cpictest1Dlg::Onhelpview()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("项目单位：北京交通大学—计算机与信息技术学院—生物医学工程\n项目经理：窦佳琦\n项目副经理：王君宇\n技术总监：向必雄\n技术助理：张修聪\n技术助理：王银燕\n美工：周小钰\n行政：周小钰"),_T("关于"));
}

//===================按下“打开原图”=============
void Cpictest1Dlg::OnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteFile(L"start.bmp");
	DeleteFile(L"start1.bmp");
	DeleteFile(L"GiveToWJF.bmp");
	DeleteFile(L"small.bmp");

  m_buttonopen.EnableWindow();  
   CFile File;
  CFileDialog dlg(TRUE, _T("*.bmp;*.jpg;*.tif"), NULL,  
        OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,  
        _T("image files All Files (*.*) |*.*||"),this
        );  
  dlg.m_ofn.lpstrTitle = _T("打开图片"); 
  if (dlg.DoModal()==IDOK)//若点击按钮
  {
      FileName=dlg.GetPathName();
      if(dlg.GetFileExt()!="bmp")  
        {  
            AfxMessageBox(_T("请选择bmp图片格式！"),MB_OK);  
            return;  
        }  
	  //string strStl=FileName.GetBuffer(0);//将路径转为string 
	  if (!File.Open(FileName,CFile::modeRead))
	   return;
      // TODO: add loading code here
      //加载用户所选取的图像文件   
      //首先清空lpBitmap所存的上次操作的图像内容 
      if (lpBitmap)//开始时存在图象，则删除
	      delete lpBitmap;
       //获得图像文件的长度，以字节为单位
       nLen=File.GetLength(); 
       //创建nLen字节长度的内存区域，来存放整个图像文件，包括文件头，调色板，和具体的像素值矩阵 
       lpBitmap=new BYTE[nLen];
       File.Read(lpBitmap,nLen);//读入内存中
       LoadBitmap();
	   //保存图片到运行目录
	   CFile file;
		file.Open(_T("small.bmp"),CFile::modeWrite|CFile::modeCreate);
		int nLen=nByteWidth*nHeight;
		BYTE *pMem=new BYTE[nLen+sizeof(BITMAPINFOHEADER)];
		BITMAPINFOHEADER *bmi=(BITMAPINFOHEADER *)pMem;
		bmi->biSize=sizeof(BITMAPINFOHEADER);
		bmi->biWidth=nWidth;
		bmi->biHeight=nHeight;
		bmi->biPlanes=1;
		bmi->biBitCount=24;
		bmi->biCompression=BI_RGB;
		bmi->biSizeImage=0;
		bmi->biXPelsPerMeter=0;
		bmi->biYPelsPerMeter=0;
		bmi->biClrUsed=0;
		bmi->biClrImportant=0;
		BITMAPFILEHEADER bmh;
		bmh.bfType='B'+'M'*256;
		bmh.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+nLen;
		bmh.bfReserved1=0;
		bmh.bfReserved2=0;
		bmh.bfOffBits=54;

		memcpy(pMem+sizeof(BITMAPINFOHEADER),lpBits,nLen);
		file.Write(&bmh,sizeof(BITMAPFILEHEADER));
		file.Write(pMem,nLen+sizeof(BITMAPINFOHEADER));
		file.Close();
		originalImg = imread("small.bmp");
  }
}

//===================按下“裂纹识别”=============
void Cpictest1Dlg::OnBnClickedDetect()
{
	// TODO: 在此添加控件通知处理程序代码
	lwsb.EnableWindow();  
	CFile File;
	Dialog2 Dialog2;
	if(Dialog2.DoModal()==IDOK)
	{
	 File.Open(_T("GiveToWJF.bmp"),CFile::modeRead);
      //首先清空lpBitmap所存的上次操作的图像内容 
      if (lpBitmap)//开始时存在图象，则删除
	   delete lpBitmap;
      //获得图像文件的长度，以字节为单位
      nLen=File.GetLength(); 
      //创建nLen字节长度的内存区域，来存放整个图像文件，包括文件头，调色板，和具体的像素值矩阵 
      lpBitmap=new BYTE[nLen];
      File.Read(lpBitmap,nLen);//读入内存中
      LoadBitmap();
	 CString str=Dialog2.str;
	 if(str=="图片1")
		picxx=1930;
	 else if(str=="图片2")
	    picxx=2248;
	 else if(str=="图片3")
		picxx=1362;
	 else if(str=="图片4")
	    picxx=1486;
	 else if(str=="图片5")
		picxx=1700;
	 else 
		picxx=2000;
	 m_yuzhi=(int)(Dialog2.m_yuzhi/13.2*picxx);
	 NiceTest();
	}
}

//=========================****魏建峰开始****============
void Cpictest1Dlg::NiceTest()
{
	if (lpBitmap==0) return;
	BYTE *lpOutput=new BYTE[nByteWidth*nHeight];
	BYTE *lptem=new BYTE[nByteWidth*nHeight];
	for(int y=0;y<nHeight;y++)
	{
		for(int x=0;x<nByteWidth;x++)
		{
			lptem[x+y*nByteWidth]=lpBits[x+y*nByteWidth];
		}
	}
	NiceTestNow(lptem,lpOutput);
	delete lpOutput;
	delete lptem;
}

void Cpictest1Dlg::NiceTestNow(BYTE *lpInput, BYTE *lpOutput)
{
	int count=0,dc,x,y,tem;
	for(y=0;y<nHeight;y++)
	{
		for(x=0;x<nWidth;x++)
		{
			int X=x*3;
			if(lpInput[X+y*nByteWidth]==255)
			{
				set(lpInput,X,y);
				int X0=Mid(lpInput,X,y);
				clear(lpInput,X,y);
				l[count]=length(lpInput,X0,y);
				count++;
			}
		}
	}
	dc=yuzhi(l,count);
	if(dc==0)
		tem=0;
	else 
		tem=l[0];
		NiceTest();	
	m_max=double(tem)/picxx*13.2;
	m_sum=dc;
	UpdateData(false);
}

/*计算长度的递归函数*/
int Cpictest1Dlg::length(BYTE *lpInput,int X,int y)
{
	int y1,t=0;
	int flag=ifnextis(lpInput,X,y);
	if(flag!=-1)
	{
		y1=y+1;
		set(lpInput,flag,y1);
		int X1=Mid(lpInput,flag,y1);
		clear(lpInput,flag,y1);
		t=1;
		t+=length(lpInput,X1,y1);
	}
	return t;
}

/*计算某一条裂纹某一行中点像素坐标(从第一个像素开始)*/
int Cpictest1Dlg::Mid(BYTE *lpInput,int X,int y)
{
	int mid,i=1;
	while((X/3+i)<nWidth&&lpInput[(X+i*3)+y*nByteWidth]==255)
	{
		i++;
	}
	i--;
	if (i%2)
	{
		i+=1;
	}
	mid=X+3*i/2;
	return mid;
}

/*判断下一行是否是裂纹(从当前行中点像素开始)*/
int Cpictest1Dlg::ifnextis(BYTE *lpInput,int X,int y)
{
	int y1=y+1,X1=X,i=3,n=0;
	while(y1<nHeight)
	{
		while(X-i>0)
		{
			if (!lpInput[X-i+y1*nByteWidth])
			{
				n++;
			}else{
				X1=X-i;
			}
			if (n==25)
			{
				break;
			}
			i+=3;
		}
		if (X1==X)
		{
			if (lpInput[X1+y*nByteWidth])
			{
				return X1;
			}
			n=0;
			i=3;
			while(X+i<nWidth*3)
			{
				if (!lpInput[X+i+y1*nByteWidth])
				{
					n++;
				}else{
					return X1;
				}
				if (n==25)
				{
					break;
				}
				i+=3;
			}
		}else{
			return X1;
		}
		y1++;
		if (y1==y+20)
		{
			break;
		}
	}
	return -1;
}

/*延拓裂纹断点(从第一个像素开始)*/
void Cpictest1Dlg::set(BYTE *lpInput,int X,int y)
{
	int i=0,j,X1=X+1,y1=y+1,n[26];
	while(X1<nWidth*3)
	{
		if (lpInput[X1+y*nByteWidth])
		{
			if(i!=0)
			{
				for (j=0;j<i;++j)
				{
					lpInput[n[j]+y*nByteWidth]=255;
					lpInput[n[j]+1+y*nByteWidth]=255;
					lpInput[n[j]+2+y*nByteWidth]=255;
				}
				i=0;
			}
		}else{
			n[i]=X1;
			i++;
			if (i==25)
			{
				break;
			}
		}
		X1+=3;
	}
}

/*阈值函数*/
int Cpictest1Dlg::yuzhi(int *l,int count)
{
	int yz=m_yuzhi;
	int c=count,i,j,tem=0;
	for (i=0;i<count;i++)
	{
		for (j=i+1;j<count;j++)
		{
			if (l[i]<l[j])
			{
				tem=l[i];
				l[i]=l[j];
				l[j]=tem;
			}
		}
	}
	for (i=0;i<count;i++)
	{
		if (l[i]<yz)
		{
			c=i;
			break;
		}
	}
	return c;
}

/*将某一行裂纹致黑(从第一个像素开始)*/
void Cpictest1Dlg::clear(BYTE *lpInput,int X,int y)
{
	while((X+3)<(nWidth*3)&&(lpInput[X+3+y*nByteWidth]==255))
	{
		lpInput[X+y*nByteWidth]=0;
		lpInput[X+1+y*nByteWidth]=0;
		lpInput[X+2+y*nByteWidth]=0;
		X+=3;
	}
	lpInput[X+y*nByteWidth]=0;
	lpInput[X+1+y*nByteWidth]=0;
	lpInput[X+2+y*nByteWidth]=0;
}
//==============================****魏建峰结束*****====================

//===================菜单-命令-裂纹识别=================
void Cpictest1Dlg::OnLwsb()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedDetect();
}

//===================按下“导出结果”=================
void Cpictest1Dlg::OnClickedRes()
{
//	// TODO: 在此添加控件通知处理程序代码
    m_dcjg.EnableWindow();
	CString FilePathName;
	CFileDialog dlg(FALSE,L"txt",NULL,OFN_OVERWRITEPROMPT,L"(*.txt)|*.txt||");
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();
		CStdioFile File;
		CString s;
		if(File.Open(FilePathName,CFile::modeCreate|CFile::modeWrite|CFile::typeText))//建立文件
		{
			s.Format(L"The total number is %d,The maximum is %f cm",m_sum,m_max);
			File.WriteString(s);
			MessageBox(L"成功保存到:"+FilePathName);
		}
		File.Close();
	}
	
}

//===================按下“图像分割”—“高斯滤波”=================
void Cpictest1Dlg::OnBnClickedSege()
{
	// TODO: 在此添加控件通知处理程序代码
	  //克隆原图到三个Mat类型中
	
	if(!g_srcImage.data )
	{
		g_srcImage = imread("start1.bmp");
		if(!g_srcImage.data )
		{
		MessageBox(_T("请先图像预处理！或者使用高级去背景功能!"));
		return;}
	}
	//g_dstImage1 = g_srcImage.clone();
	//g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	m_gslb.EnableWindow();  
	namedWindow("【高斯滤波】", 0);
	//创建轨迹条
	//createTrackbar("内核值：", "【<3>高斯滤波】",&g_nGaussianBlurValue, 40,&Cpictest1Dlg::on_GaussianBlur );
	//createTrackbar("标准差：", "【<3>高斯滤波】",&g_nGaussianVerticalValue, 150,&Cpictest1Dlg::on_GaussianVertical );
	on_GaussianBlur(0,0);
		
}


//===================按下“图像分割”—“sobel边缘检测”=================
void Cpictest1Dlg::OnBnClickedSob()
{
	// TODO: 在此添加控件通知处理程序代码
	// 创建与src同类型和大小的矩阵(dst)
		if(!g_dstImage3.data )
	{
		MessageBox(_T("请先高斯滤波！"));
		return;
	}
	Mat g_dstImage;
	m_sobel.EnableWindow();  
	g_dstImage.create( g_dstImage3.size(), g_dstImage3.type() );
	// 创建显示窗口
	namedWindow( "【效果图】Sobel边缘检测", 0 );
	// 创建trackbar
	//createTrackbar( "参数值：", "【效果图】Sobel边缘检测", &g_sobelKernelSize, 30,&Cpictest1Dlg::on_Sobel);
	// 调用回调函数
	on_Sobel(0, 0);
}


//===================按下“图像分割”—“二值化边缘检测”=================
void Cpictest1Dlg::OnBnClickedBin()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!g_sobelAbsGradient_Y.data )
	{
		MessageBox(_T("请先Sobel边缘检测！"));
		return;
	}
	Mat g_srcGrayImage;
	m_ezh.EnableWindow();  
	namedWindow( "二值化", 0 );
	//createTrackbar( "灰度阈值：", "二值化边缘检测", &g_binaryThreshold, 25, &Cpictest1Dlg::on_Binary);
	cvtColor( g_sobelAbsGradient_Y, g_srcGrayImage, COLOR_RGB2GRAY);
	adaptiveThreshold(g_srcGrayImage,g_biImage,maxgray,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,(2*7+1),2.75);
	imshow("二值化",g_biImage);
}



//===================按下“图像分割”—“中值滤波”=================
void Cpictest1Dlg::OnBnClickedMed()
{
	// TODO: 在此添加控件通知处理程序代码
	m_zzlb.EnableWindow();  
	if(!g_biImage.data )
	{
		MessageBox(_T("请先二值化边缘检测！"));
		return;
	}
	namedWindow("中值滤波",0);
	//createTrackbar( "窗口大小：", "中值滤波膨胀后", &g_medfiltKernel, 10, (cv::TrackbarCallback)Cpictest1Dlg::on_MedianFilter);
	Mat g_medfiltImage2;
    medianBlur(g_biImage,g_medfiltImage,5);
	medianBlur(g_medfiltImage,g_medfiltImage2,5);
	threshold(g_medfiltImage2,g_biFINALImage,125,255,THRESH_BINARY_INV);
	imshow("中值滤波",g_biFINALImage);
}


//===================按下“图像分割”—“膨胀”=================
void Cpictest1Dlg::OnBnClickedDilate()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pz.EnableWindow();  
		if(!g_biFINALImage.data )
	{
		MessageBox(_T("请先中值滤波！"));
		return;
	}
	Mat img_dilate1;
	Mat ele1(3,4,CV_8U,Scalar(1));	//定义第一个膨胀的结构元素
	ele1.at<uchar>(0,2) = 0;
	ele1.at<uchar>(0,3) = 0;
	ele1.at<uchar>(1,0) = 0;
	ele1.at<uchar>(1,3) = 0;
	ele1.at<uchar>(2,0) = 0;
	ele1.at<uchar>(2,1) = 0;
	dilate(g_biFINALImage, img_dilate1, ele1, Point(-1,-1),4);//膨胀4次

	Mat img_dilate2;
	Mat ele2(3,4,CV_8U,Scalar(1));	//定义第二个膨胀结构元素
	ele2.at<uchar>(0,0) = 0;
	ele2.at<uchar>(0,1) = 0;
	ele2.at<uchar>(1,0) = 0;
	ele2.at<uchar>(1,3) = 0;
	ele2.at<uchar>(2,2) = 0;
	ele2.at<uchar>(2,3) = 0;
	dilate(img_dilate1, img_dilate2, ele2, Point(-1,-1),3);//膨胀3次

	Mat ele3 = getStructuringElement(MORPH_RECT,Size(4,1),Point(-1,-1));
	dilate(img_dilate2, img_dilate3, ele3, Point(-1,-1),1);//膨胀1次
	namedWindow("膨胀",0);	//创建窗口
	imshow("膨胀",img_dilate3);  //在窗口中显示膨胀后图像
	imwrite("GiveToWJF.bmp",img_dilate3);
}

//-----------------------------【ContrastAndBright( )函数】------------------------------------
//	描述：高斯滤波操作的回调函数
//-----------------------------------------------------------------------------------------------
void Cpictest1Dlg::on_GaussianBlur(int, void *)
{
	//高斯滤波
	GaussianBlur( g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1 ), g_nGaussianVerticalValue,g_nGaussianVerticalValue);
	//显示窗口
	//创建窗口
	imshow("【高斯滤波】", g_dstImage3);
}


//-----------------------------------【on_Sobel( )函数】----------------------------------
//		描述：Sobel边缘检测窗口滚动条的回调函数
//-----------------------------------------------------------------------------------------
void Cpictest1Dlg::on_Sobel(int, void*)
{
	
	// 求Y方向梯度
	Sobel( g_dstImage3, g_sobelGradient_Y, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_Y, g_sobelAbsGradient_Y );//计算绝对值，并将结果转换成8位

	//显示效果图
	imshow("【效果图】Sobel边缘检测", g_sobelAbsGradient_Y);

}


void Cpictest1Dlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bctp.EnableWindow(); 
	if(!img_contour22.data)
	{
		MessageBox(_T("请先进行裂纹识别！"));
		return;
	}
	CFileDialog dlg(FALSE,L"bmp",NULL,OFN_OVERWRITEPROMPT,L"(*.bmp)|*.bmp|(*.jpg)|*.jpg||");
	CStringW FilePathName;
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();
		CStringA stra(FilePathName.GetBuffer(0));
		FilePathName.ReleaseBuffer();
		string imgpath=stra.GetBuffer(0);
		stra.ReleaseBuffer();
		if(imwrite(imgpath,img_contour22))
		{
			MessageBox(_T("图片成功保存到：")+FilePathName);
		}
		else
		{
			MessageBox(L"error");
		}
	}
}


void Cpictest1Dlg::OnBnClickedComp()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bjjg.EnableWindow(); 
    Mat  g_contourRed,g_contourGreen,g_contourBlue,g_Contour24bmp,g_addImage;
	vector<Mat>channels; 

	double alphaValue = 0.5;  
	double betaValue;  
	betaValue= ( 1.0 - alphaValue );  

	split(originalImg,channels);
	g_contourBlue = channels.at(0);
	g_contourGreen = channels.at(1);
	g_contourRed = channels.at(2);
	
	addWeighted(g_contourBlue, alphaValue, img_contour22, betaValue, 0.0, g_contourBlue);  
	addWeighted(g_contourGreen, alphaValue, img_contour22, betaValue, 0.0, g_contourGreen);  
	addWeighted(g_contourRed, alphaValue, img_contour22, betaValue, 0.0, g_contourRed);  
	
	merge(channels,g_Contour24bmp); 

	namedWindow("轮廓图成彩色图",WINDOW_NORMAL);
	//namedWindow("原图",WINDOW_NORMAL);
	//imshow("原图",g_srcImage);
	imshow("轮廓图成彩色图",g_Contour24bmp);
	imwrite("g_Contour24bmp.bmp",g_Contour24bmp);

}



#define MPoint(x,y) lpMPoints[(x)+(y)*nWidth]
#define MPoint1(x,y) lpMPoints1[(x)+(y)*nWidth]
void Cpictest1Dlg::GetMPoints(int nWidth,int nHeight,BYTE *lpBits,BYTE *lpMPoints)
{
int x,y,p;
int nByteWidth=nWidth*3;
if (nByteWidth%4) nByteWidth+=4-(nByteWidth%4);
for(y=0;y<nHeight;y++)
{
for(x=0;x<nWidth;x++)
{
p=x*3+y*nByteWidth;
lpMPoints[x+y*nWidth]=(BYTE)(0.299*(float)lpBits[p+2]+0.587*(float)lpBits[p+1]+0.114*(float)lpBits[p]+0.1);
}
}
}

void Cpictest1Dlg::PutMPoints(int nWidth,int nHeight,BYTE *lpBits,BYTE *lpMPoints)
{
int nByteWidth=nWidth*3;
if (nByteWidth%4) nByteWidth+=4-(nByteWidth%4);
int x,y,p,p1;
for(y=0;y<nHeight;y++)
{
for(x=0;x<nWidth;x++)
{
p=x*3+y*nByteWidth;
p1=x+y*nWidth;
lpBits[p]=lpMPoints[p1];
lpBits[p+1]=lpMPoints[p1];
lpBits[p+2]=lpMPoints[p1];
}
}
}
//二值化
void Cpictest1Dlg::ezh2(int nWidth, int nHeight, BYTE *lpInput, BYTE *lpOutput,int a)
{   
	int t=a;
	if(t<0||t>255)
		MessageBox( _T("输入错误"), _T("错误"),MB_OK|MB_ICONWARNING);
	
	BYTE *lpMPoints=new BYTE[nWidth*nHeight];
	GetMPoints(nWidth,nHeight,lpInput,lpMPoints);
	BYTE threshold=(BYTE)t;
	int x,y;
	for(y=0;y<nHeight;y++)
	{
		for(x=0;x<nWidth;x++)
		{
			if (MPoint(x,y)>threshold) MPoint(x,y)=255;
			else MPoint(x,y)=0;
		}
	}

	PutMPoints(nWidth,nHeight,lpOutput,lpMPoints);
	delete lpMPoints;

}

void Cpictest1Dlg::xb2(int nWidth, int nHeight, BYTE *lpInput, BYTE *lpOutput)
{
   BYTE *lpMPoints=new BYTE[nWidth*nHeight];
   GetMPoints(nWidth,nHeight,lpInput,lpMPoints);
   int x,y;
   int i=0,j=0;
   int **a=new int*[nWidth];
   for(i=0;i<nWidth;i++)
   {
       a[i] = new int[nHeight]; 
   }

   for(y=0;y<nHeight;y++)//获取黑色部分的坐标
   {
	   for(x=0;x<nWidth;x++)
	   {
		   if(MPoint(x,y)==0)
		   {
			   a[x][y]=1;
		   }

		   else
			   a[x][y]=0;
	   }
   }
   
   GetMPoints(nWidth,nHeight,lpBits,lpMPoints);
   for(x=nWidth-1;x>=0;x--)
   {
	   for(y=nHeight-1;y>0;y--)
	   {  
		  MPoint(x,y)=0;
		  if(a[x][y]==1)
		  {
			 
			  MPoint(x,y)=0;
		      break; 
		  }
	   }
   }

    PutMPoints(nWidth,nHeight,lpOutput,lpMPoints);
	delete lpMPoints;
	for(i= 0;i<nWidth;i++)
	{
       delete [] a[i];
	}
    delete a;
}


//====================================陈丽开始================================================
void Cpictest1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_new.EnableWindow(); 
	if(!img_dilate3.data)
	{
		MessageBox(_T("请先进行图像分割！"));
		return;
	}
	Mat image = img_dilate3;
	//namedWindow("expand",WINDOW_NORMAL); 
	//imshow("expand",image);
	Dialog2 Dialog;
	if(Dialog.DoModal()==IDOK)
	{
	int up=Dialog.m_down;
	double x;
	double min=Dialog.m_yuzhi;
	CString str=Dialog.str;
	x=Dialog.m_down2;
	//if(str=="图片1")
		//x=1930;
	//else if(str=="图片2")
	    //x=2248;
	//else if(str=="图片3")
		//x=1362;
	//else if(str=="图片4")
	    //x=1486;
	//else if(str=="图片5")
		//x=1700;
	//else 
		//x=2000;

	///////////////////////【1】去掉下边界////////////////////////////////////////////////
	int imgr = image.rows;
	int imgc = image.cols;
	for (int i=imgr-up;i<imgr;i++)//此处530为系统中弹出窗口的预设值，界面中可弹出窗口输入该值
	{
		for (int j=0;j<imgc;j++)
		{
			image.at<uchar>(i,j) = 0;
			//image.at<Vec3b>(i,j)[1] = 0;
			//image.at<Vec3b>(i,j)[2] = 0;
		}
	}

	//namedWindow("RemoveLowerBoundary",WINDOW_NORMAL); 
	//imshow("RemoveLowerBoundary",image); 
	//imwrite("RemoveLowerBoundary.bmp",image);
	///////////////////////【1】去掉下边界结束////////////////////////////////////////////////


	//////////////////////【2】轮廓提取////////////////////////////////////////////////
	Mat img;
	//cvtColor(image,img,COLOR_RGB2GRAY);//输入图像要为二值图像
	blur( image, img, Size(3,3) ); //取轮廓前平滑处理（模糊）
	//imwrite("smoothAfterRemove.bmp",img);
	vector<vector<Point>> contours; //输出为每一个连通区域的轮廓点的集合
	//外层vector的size代表了图像中轮廓的个数，里面vector的 size代表了轮廓上点的个数

	//======findContours======
	findContours(img,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);	


	//======First drawContours======//去掉下边界后全部找到的轮廓
	Mat img_contour(img.size(),CV_8U,Scalar(0)); 
	drawContours(img_contour,contours,-1,Scalar(255),1,LINE_8 );

	//namedWindow("contours1",WINDOW_NORMAL); 
	//imshow("contours1",img_contour); 
	//imwrite("contours1.bmp",img_contour); 

	//=======遍历取出的每一个轮廓============
	double maxarea = 15000; 
    double minarea=min/13.2*x*3.0;  //界面中弹出窗口输入该值
	int num = contours.size();
	double MaxLength = 0;
	for (unsigned int i=0;i<contours.size();i++)
	{
		double tmparea = fabs(contourArea(contours[i]));

		//删除面积小于设定值的轮廓
		if ((tmparea<minarea) | (tmparea>maxarea))
		{
			contours.erase(contours.begin() + i);
			num--;
			continue;
		}

		//计算轮廓的直径宽高
		Rect aRect = boundingRect(contours[i]);
		if (aRect.height > MaxLength)
		{
			MaxLength = aRect.height;
		}
		if (aRect.width > MaxLength)
		{
			MaxLength = aRect.width;
		}
	}

	//======Second drawContours======//对于找到的全部轮廓设定阈值之后，再次提取轮廓
	Mat img_contour2(img_contour.size(),CV_8U,Scalar(0)); 
	for (unsigned int i=0;i<contours.size();i++)
	{
		drawContours(img_contour2,contours,i,Scalar(255),1,LINE_8 );
	}

	img_contour22=img_contour2;
	
	//////////////////////【2】轮廓提取结束////////////////////////////////////////////////


	///////////////////////【3】计算裂纹数目和最长裂纹长度////////////////////////////////////////////////
	m_sum=num;
	m_max=MaxLength/x*13.2;
	UpdateData(false);
	
	///////////////////////【3】计算结束////////////////////////////////////////////////
	}
}
//============================================================================================




void Cpictest1Dlg::Onmsave()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedSave();
}


void Cpictest1Dlg::On32788()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedComp();
}


void Cpictest1Dlg::Onmtxyvl()
{
	// TODO: 在此添加命令处理程序代码
	OnRebg();
}


void Cpictest1Dlg::Onmgslb()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedSege();
}


void Cpictest1Dlg::Onmsobel()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedSob();
}


void Cpictest1Dlg::Onmezh()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBin();
}


void Cpictest1Dlg::Onmzzlb()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedMed();
}


void Cpictest1Dlg::Onmpz()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedDilate();
}


void Cpictest1Dlg::Onmlwsb2()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButton1();
}


void Cpictest1Dlg::Onmdcdjg()
{
	// TODO: 在此添加命令处理程序代码
	OnClickedRes();
}


void Cpictest1Dlg::OnBnClickedsmall()
{
	// TODO: 在此添加控件通知处理程序代码
	    m_xsyt.EnableWindow(); 
		if(!originalImg.data )
		{
			MessageBox(_T("请先打开原图"));
		}
		namedWindow("原图",WINDOW_NORMAL); 
	    imshow("原图",originalImg); 

		CBitmap bitmap;  // CBitmap对象，用于加载位图     
		HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄     

		
		//bitmap.LoadBitmap(originalImg);  // 将位图IDB_BITMAP1加载到bitmap    
		//hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄    
		//m_Picture1.SetBitmap((HBITMAP)originalImg.data);
}


//=============================按下一键处理================================
void Cpictest1Dlg::OnBnClickedOne()
{
	// TODO: 在此添加控件通知处理程序代码
	m_yjtxfg.EnableWindow();
	OnBnClickedSege();
	OnBnClickedSob();
	OnBnClickedBin();
	OnBnClickedMed();
	OnBnClickedDilate();
}


void Cpictest1Dlg::OnBnClickedAfter()
{
	// TODO: 在此添加控件通知处理程序代码
	m_xsclhtp.EnableWindow(); 
	if(!img_contour22.data)
	{
		MessageBox(L"未进行裂纹识别!");
	    return;
	}
	namedWindow("处理后的结果",WINDOW_NORMAL); 
	imshow("处理后的结果",img_contour22); 
	
}


void Cpictest1Dlg::OnRegister()
{
	// TODO: 在此添加命令处理程序代码
	CRegister Register;
	CString rusername,rpas,rpas2;
	CString strSQL;
	CDaoDatabase db; 
	do
	{
		if(Register.DoModal()==IDOK)
		{
		//Register.UpdateData(true);
			rusername=Register.m_rusername;
			rpas=Register.m_rpas;
			rpas2=Register.m_rpas2;
			if(rusername.IsEmpty()||rpas.IsEmpty())
			{
					MessageBox(_T("用户名或密码为空"));
					continue;
			}
	    	if(rpas!=rpas2)
			{
				MessageBox(_T("两次密码不一致"));
				Register.m_rpas=_T("");
				Register.m_rpas2=_T("");
				//Register.UpdateData(false);
			}
		}
	 }while((rpas!=rpas2)||(rusername==""));
		db.Open(_T("test.mdb"),FALSE,FALSE);
	    strSQL.Format(_T("insert into test values('%s','%s')"),rusername,rpas);
        db.Execute(strSQL);
	    MessageBox(_T("注册用户成功"));
	    db.Close();
	}


void Cpictest1Dlg::OnRevise()
{
	// TODO: 在此添加命令处理程序代码
	CRevise Revise;
	CString cusername,cpas,cpas2;
	CString strSQL;
	CDaoDatabase db; 
	do
	{
		if(Revise.DoModal()==IDOK)
		{
			cusername=Revise.m_cusername;
			cpas=Revise.m_cpas;
			cpas2=Revise.m_cpas2;
			if(cusername.IsEmpty()||cpas.IsEmpty())
			{
					MessageBox(_T("用户名或密码为空"));
					continue;
			}
	    	if(cpas!=cpas2)
			{
				MessageBox(_T("两次密码不一致"));
				Revise.m_cpas=_T("");
				Revise.m_cpas2=_T("");
			}
		}
	 }while((cpas!=cpas2)||(cusername==""));
		db.Open(_T("test.mdb"),FALSE,FALSE);
	    strSQL.Format(_T("update test set username='%s',key='%s'where username='%s'"),cusername,cpas,cusername);
        db.Execute(strSQL);
	    MessageBox(_T("修改密码成功"));
	    db.Close();
}


void Cpictest1Dlg::OnDelete()
{
	// TODO: 在此添加命令处理程序代码
	CDelete Delete;
	CString dusername;
    CString strSQL;
	CDaoDatabase db; 
	if(Delete.DoModal()==IDOK)
	{
	  dusername=Delete.m_dusername;
	  db.Open(_T("test.mdb"),FALSE,FALSE);
      strSQL.Format(_T("delete from test where username='%s'"),dusername);
      db.Execute(strSQL);
      db.Close();
	  MessageBox(_T("删除用户成功！"));
	}
}


HBRUSH Cpictest1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	CFont m_Font1,m_Font2;
	m_Font1.CreatePointFont(120, L"华文行楷"); 
	m_Font2.CreatePointFont(100, L"Arial"); 
	if(nCtlColor == CTLCOLOR_STATIC)
    {
	         pDC->SetTextColor(RGB(0, 111, 255));
			 pDC-> SetBkMode(TRANSPARENT);
			 pDC->SelectObject(&m_Font1); 
			 return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	} 
   else if(nCtlColor == CTLCOLOR_EDIT)
	{
		     pDC->SetTextColor(RGB(0, 255, 0));
			 pDC-> SetBkMode(TRANSPARENT);
			 pDC->SelectObject(&m_Font2); 
			 return (HBRUSH)::GetStockObject(BLACK_BRUSH); 
	} 
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	else
	return hbr;
}

//==========================菜单-高级功能—手动去背景================
void Cpictest1Dlg::Onsuper()
{
	// TODO: 在此添加命令处理程序代码
	CSuper super;
    super.DoModal();
}


void Cpictest1Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DeleteFile(L"start.bmp");
	DeleteFile(L"start1.bmp");
	DeleteFile(L"GiveToWJF.bmp");
	DeleteFile(L"small.bmp");
	CDialogEx::OnClose();
}

void Cpictest1Dlg::Resize()
{
	float fsp[2];
	POINT Newp;
	CRect recta;
	GetClientRect(&recta);
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/old.x;
	fsp[1]=(float)Newp.y/old.y;
	CRect Rect;
	int woc;
	CPoint oldTLPoint,TLPoint;
	CPoint oldBRPoint,BRPoint;
	HWND hwndchild=::GetWindow(m_hWnd,GW_CHILD);
	while(hwndchild)
	{
		woc=::GetDlgCtrlID(hwndchild);
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			oldTLPoint=Rect.TopLeft();
			TLPoint.x=long(oldTLPoint.x*fsp[0]);
			TLPoint.y=long(oldTLPoint.y*fsp[1]);
			oldBRPoint=Rect.BottomRight();
			BRPoint.x=long(oldBRPoint.x*fsp[0]);
			BRPoint.y=long(oldBRPoint.y*fsp[1]);
			Rect.SetRect(TLPoint,BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			hwndchild=::GetWindow(hwndchild, GW_HWNDNEXT);  
	}
	old=Newp;
}



void Cpictest1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType,cx,cy);
	if (nType==SIZE_MAXIMIZED||nType==SIZE_RESTORED)
	{
		Resize();
	}
}

void Cpictest1Dlg::OnEnChangeEditSum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Cpictest1Dlg::OnStnClickedStatic4()
{
	// TODO: Add your control notification handler code here
}


void Cpictest1Dlg::On23432806()
{
	// TODO: Add your command handler code here
}
