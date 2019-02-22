
// pictest1Dlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cpictest1Dlg �Ի���
Cpictest1Dlg::Cpictest1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cpictest1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lpBitmap=0;
	//lpBackup=0;
	l = new int[200];
	m_sum = 0;
	g_sobelKernelSize=1;//TrackBarλ�ò��� 
	//�Ҷ���ֵ��ر���
	g_binaryThreshold = 11;
	//��ֵ�˲�
	g_medfiltKernel = 7;
	g_nGaussianBlurValue=7;  //��˹�˲�����ֵ
	g_nGaussianVerticalValue=10;  //��˹�˲�����ֵ
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


// Cpictest1Dlg ��Ϣ�������

BOOL Cpictest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��������ΪSource������Ϊ�Ӵ����ҿɼ��ĳ����Σ���ͼ���������Ϊ10000
	//source.Create(0,LPCTSTR("Source"),WS_CHILD|WS_VISIBLE,CRect(40,40,360,280), this, 10000);
	//��������ΪDestination������Ϊ�Ӵ����ҿɼ��ĳ����Σ���ͼ���������Ϊ10001
    //Create(0,LPCTSTR("Destination"),WS_CHILD|WS_VISIBLE,CRect(450,40,770,280), this, 10001);
	m_buttonopen.LoadBitmaps(IDB_BITMAP2,IDB_BITMAP3);   //����  
	m_buttonopen.SizeToContent();  //ʹ��ť��ӦͼƬ��С
	m_bctp.LoadBitmaps(IDB_bctp1,IDB_bctp2);   //����  
	m_bctp.SizeToContent();
	m_bjjg.LoadBitmaps(IDB_bjjg1,IDB_bjjg2);   //����  
	m_bjjg.SizeToContent();
	m_txycl.LoadBitmaps(IDB_txycl1,IDB_txycl2);   //����  
	m_txycl.SizeToContent();
	m_gslb.LoadBitmaps(IDB_gslb1,IDB_gslb2);   //����  
	m_gslb.SizeToContent();
	m_sobel.LoadBitmaps(IDB_sobel1,IDB_sobel2);   //����  
	m_sobel.SizeToContent();
	m_zzlb.LoadBitmaps(IDB_zzlb1,IDB_zzlb2);   //����  
	m_zzlb.SizeToContent();
	m_ezh.LoadBitmaps(IDB_ezh1,IDB_ezh2);   //����  
	m_ezh.SizeToContent();
	m_pz.LoadBitmaps(IDB_pz1,IDB_pz2);   //����  
	m_pz.SizeToContent();
	lwsb.LoadBitmaps(IDB_lwsb1,IDB_lwsb2);   //����  
	lwsb.SizeToContent();
	m_dcjg.LoadBitmaps(IDB_dcjg1,IDB_dcjg2);   //����  
	m_dcjg.SizeToContent();
	m_new.LoadBitmaps(IDB_BITMAP4,IDB_BITMAP5);   //����  
	m_new.SizeToContent();
	m_yjtxfg.LoadBitmaps(IDB_yjlwfg,IDB_yjlwfg1);   //����  
	m_yjtxfg.SizeToContent();
	m_xsyt.LoadBitmaps(IDB_xsyt,IDB_xsyt1);   //����  
	m_xsyt.SizeToContent();
	m_xsclhtp.LoadBitmaps(IDB_xsclhtp,IDB_xsclhtp1);   //����  
	m_xsclhtp.SizeToContent();

	CRect rect;
	GetClientRect(&rect);
	old.x=rect.right-rect.left;
	old.y=rect.bottom-rect.top;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cpictest1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cpictest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cpictest1Dlg::LoadBitmap()
{
BITMAPINFOHEADER *pInfo;
pInfo=(BITMAPINFOHEADER *)(lpBitmap+sizeof(BITMAPFILEHEADER));//λͼ��Ϣͷָ�룬ָ��lpBitmap�ڴ�����BITMAPFILEHEADER�����׵�ַ 
nWidth=pInfo->biWidth;//��λͼ��Ϣͷ��ȡ��λͼ�����Ϣ��������nWidth 
nByteWidth=nWidth*3;//ÿ��ͼ����ռ�ֽ���ĿΪͼ���ȵ�3����24λ���ɫͼ��
if (nByteWidth%4)
 nByteWidth+=4-(nByteWidth%4); //ÿ��ͼ����ռ�ֽ���Ŀ���벹��Ϊ4��������
nHeight=pInfo->biHeight;
if (pInfo->biBitCount!=24) //��ͼ�������ɫͼ����ת��
{
   if (pInfo->biBitCount!=8)//��ͼ���8λͼ���ͷ�lpBitmap�ڴ棬��������
   {
      MessageBox(_T("��Чλͼ"));
      delete lpBitmap;
      lpBitmap=0;
      return;
   }
   unsigned int PaletteSize=1<<pInfo->biBitCount;//�����ɫ���С�����������������nλ���൱��2��n���� 
      if (pInfo->biClrUsed!=0 && pInfo->biClrUsed<PaletteSize)//��biClrUsed��Ϊ�㣬��ɫ���С����ʵ��ʹ�õ���ɫ��
		  PaletteSize=pInfo->biClrUsed;
      lpBits=lpBitmap+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);//lpBitsָ��Ϊ8λͼ���ɫ����
      RGBQUAD *pPalette=(RGBQUAD *)lpBits;//RGBQUADΪ��ɫ������Ԫ�صĽṹ�壬��ʱ�����ɫ������ָ��pPalette����lpBitsָ��ͬһ�ڴ�λ�� 
      lpBits+=sizeof(RGBQUAD)*PaletteSize;//ʹlpBitsָ��8λͼ��������� 
      nLen=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+nByteWidth*nHeight;//24λλͼ�ļ��ֽڴ�С 
      BYTE *lpTemp=lpBitmap;//�¶���lpTempָ��ԭlpBitmap��Ӧ���ڴ��� 
      lpBitmap=new BYTE[nLen];//�¿���һ������24λλͼ�ļ����ڴ�����ָ������ڴ��ָ��ΪlpBitmap 
	  BITMAPFILEHEADER bmh;
      BITMAPINFOHEADER bmi;
      //��ȡλͼ�ļ�ͷ�������Ϣ
	  bmh.bfType='B'+'M'*256;
      bmh.bfSize=nLen;
      bmh.bfReserved1=0;
      bmh.bfReserved2=0;
      bmh.bfOffBits=54;
	  //��ȡλͼ��Ϣͷ�������Ϣ
      bmi.biSize=sizeof(BITMAPINFOHEADER);
      bmi.biWidth=nWidth;
      bmi.biHeight=nHeight;
      bmi.biPlanes=1;
      bmi.biBitCount=24;//������λͼ�ļ���Ϊ24λ
      bmi.biCompression=BI_RGB;
      bmi.biSizeImage=0;
      bmi.biXPelsPerMeter=0;
      bmi.biYPelsPerMeter=0;
      bmi.biClrUsed=0;
      bmi.biClrImportant=0;
      int nBWidth=pInfo->biWidth;//�ٴδ�8λλͼ��Ϣͷ�ж���ÿ��ͼ����Ŀ
      if (nBWidth%4)
		  nBWidth+=4-(nBWidth%4);//ÿ��ͼ����ռ�ֽ���Ŀ���벹��Ϊ4�������� 
      memset(lpBitmap,0,nLen);//lpBitmapָ����ڴ���ȫ��nLen�ֽ���0 
      memcpy(lpBitmap,&bmh,sizeof(BITMAPFILEHEADER));//д��λͼ�ļ�
      memcpy(lpBitmap+sizeof(BITMAPFILEHEADER),&bmi,sizeof(BITMAPINFOHEADER));//д��λͼ�ļ�
      BYTE *lpBits2=lpBitmap+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);//������ָ��lpBits2ָ��24λͼ�������� 
      int x,y,p1,p2,Palette;
	   //�������а�����ת��
      for(y=0;y<nHeight;y++)//ÿ��
	  {
          for(x=0;x<nWidth;x++)//ÿ��
		  {
             p1=y*nBWidth+x;;//��ͼ��ײ���ʼ��ԭ8λͼ��ĵ�y�е�x������ 
             p2=y*nByteWidth+x*3;//��ͼ��ײ���ʼ����24λͼ��ĵ�y�е�x������ 
			 //lpBits��ʱָ��8λͼ���������������y�е�x����������С�ڵ�ɫ���С�����������ݼ�Ϊ��Ӧ�ĵ�ɫ������ֵ 
             if (lpBits[p1]<PaletteSize)
				 Palette=lpBits[p1];
             else Palette=0;
			 //���ݵ�ɫ������ֵ�������24λͼ���ڸ�����λ�ô�����ԭɫ��Ϣ��������ͼ���ڴ��� 
             lpBits2[p2]=pPalette[Palette].rgbBlue;
             lpBits2[p2+1]=pPalette[Palette].rgbGreen;
             lpBits2[p2+2]=pPalette[Palette].rgbRed;
		  }
	  }
      delete lpTemp;//ɾ��lpTempָ���ԭʼ8λͼ���ڴ��� 
}
lpBits=lpBitmap+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);//ʹlpBitsָ��24λͼ��������� 
//if (lpBackup)
  //delete lpBackup;
//lpBackup=new BYTE[nLen];//���ո����ɵ�ȥ����ɫ���lpBitmap��ָͼ����lpBackup��ָ�ڴ����򱸷ݣ��ѱ�����ʹ��  
//memcpy(lpBackup,lpBitmap,nLen);//��λͼ����д��λͼ�ļ� 
}


//===================�˵����ļ�����=================
void Cpictest1Dlg::OnOpen()
{
	// TODO: �ڴ���������������
	OnClickedOpen();
}

//===================�˵�-����-����=================
void Cpictest1Dlg::On32777()
{
	// TODO: �ڴ���������������
	MessageBox(_T("�Զ����ɲ��������ϵͳʹ��˵����\n�����ԭͼ��ťѡ��һ��bmp��ʽ��ɲ����ͼ�񣻵��ͼ��Ԥ�������ո�˹�˲���Sobel��Ե��⡢��ֵ����Ե��⡢��ֵ�˲������͵�˳����ͼ�񣨻���ʹ��һ�����Ʒָ�ܣ���������Ʒָ�֮��������ʶ�𣻵����ʾ�����ͼ�񣻵���ȽϽ����ʾ�����ͼ���ԭͼ�����ͼ��"),_T("˵��"));
	//system("rundll32.exe user32.dll,LockWorkStation ");
	//system("shutdown -h");
}


//===================���¡�ͼ��Ԥ����=============
void Cpictest1Dlg::OnRebg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_txycl.EnableWindow();  
	CDialog1 Dialog1;
	if(Dialog1.DoModal()==IDOK)
	{   int a=Dialog1.m_up;
		if (!lpBitmap)
		{
			MessageBox(_T("���ȴ�ͼƬ��"));
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
	    if( !g_srcImage.data ) { MessageBox(_T("Oh��no����ȡͼ�����~��")); }
		namedWindow("Ԥ������ͼ��",0);
		imshow("Ԥ������ͼ��",g_srcImage);
	}

}

//===================�˵�-�鿴����=============
void Cpictest1Dlg::Onhelpview()
{
	// TODO: �ڴ���������������
	MessageBox(_T("��Ŀ��λ��������ͨ��ѧ�����������Ϣ����ѧԺ������ҽѧ����\n��Ŀ��������\n��Ŀ������������\n�����ܼࣺ�����\n�����������޴�\n��������������\n��������С��\n��������С��"),_T("����"));
}

//===================���¡���ԭͼ��=============
void Cpictest1Dlg::OnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
  dlg.m_ofn.lpstrTitle = _T("��ͼƬ"); 
  if (dlg.DoModal()==IDOK)//�������ť
  {
      FileName=dlg.GetPathName();
      if(dlg.GetFileExt()!="bmp")  
        {  
            AfxMessageBox(_T("��ѡ��bmpͼƬ��ʽ��"),MB_OK);  
            return;  
        }  
	  //string strStl=FileName.GetBuffer(0);//��·��תΪstring 
	  if (!File.Open(FileName,CFile::modeRead))
	   return;
      // TODO: add loading code here
      //�����û���ѡȡ��ͼ���ļ�   
      //�������lpBitmap������ϴβ�����ͼ������ 
      if (lpBitmap)//��ʼʱ����ͼ����ɾ��
	      delete lpBitmap;
       //���ͼ���ļ��ĳ��ȣ����ֽ�Ϊ��λ
       nLen=File.GetLength(); 
       //����nLen�ֽڳ��ȵ��ڴ��������������ͼ���ļ��������ļ�ͷ����ɫ�壬�;��������ֵ���� 
       lpBitmap=new BYTE[nLen];
       File.Read(lpBitmap,nLen);//�����ڴ���
       LoadBitmap();
	   //����ͼƬ������Ŀ¼
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

//===================���¡�����ʶ��=============
void Cpictest1Dlg::OnBnClickedDetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	lwsb.EnableWindow();  
	CFile File;
	Dialog2 Dialog2;
	if(Dialog2.DoModal()==IDOK)
	{
	 File.Open(_T("GiveToWJF.bmp"),CFile::modeRead);
      //�������lpBitmap������ϴβ�����ͼ������ 
      if (lpBitmap)//��ʼʱ����ͼ����ɾ��
	   delete lpBitmap;
      //���ͼ���ļ��ĳ��ȣ����ֽ�Ϊ��λ
      nLen=File.GetLength(); 
      //����nLen�ֽڳ��ȵ��ڴ��������������ͼ���ļ��������ļ�ͷ����ɫ�壬�;��������ֵ���� 
      lpBitmap=new BYTE[nLen];
      File.Read(lpBitmap,nLen);//�����ڴ���
      LoadBitmap();
	 CString str=Dialog2.str;
	 if(str=="ͼƬ1")
		picxx=1930;
	 else if(str=="ͼƬ2")
	    picxx=2248;
	 else if(str=="ͼƬ3")
		picxx=1362;
	 else if(str=="ͼƬ4")
	    picxx=1486;
	 else if(str=="ͼƬ5")
		picxx=1700;
	 else 
		picxx=2000;
	 m_yuzhi=(int)(Dialog2.m_yuzhi/13.2*picxx);
	 NiceTest();
	}
}

//=========================****κ���忪ʼ****============
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

/*���㳤�ȵĵݹ麯��*/
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

/*����ĳһ������ĳһ���е���������(�ӵ�һ�����ؿ�ʼ)*/
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

/*�ж���һ���Ƿ�������(�ӵ�ǰ���е����ؿ�ʼ)*/
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

/*�������ƶϵ�(�ӵ�һ�����ؿ�ʼ)*/
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

/*��ֵ����*/
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

/*��ĳһ�������º�(�ӵ�һ�����ؿ�ʼ)*/
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
//==============================****κ�������*****====================

//===================�˵�-����-����ʶ��=================
void Cpictest1Dlg::OnLwsb()
{
	// TODO: �ڴ���������������
	OnBnClickedDetect();
}

//===================���¡����������=================
void Cpictest1Dlg::OnClickedRes()
{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
    m_dcjg.EnableWindow();
	CString FilePathName;
	CFileDialog dlg(FALSE,L"txt",NULL,OFN_OVERWRITEPROMPT,L"(*.txt)|*.txt||");
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();
		CStdioFile File;
		CString s;
		if(File.Open(FilePathName,CFile::modeCreate|CFile::modeWrite|CFile::typeText))//�����ļ�
		{
			s.Format(L"The total number is %d,The maximum is %f cm",m_sum,m_max);
			File.WriteString(s);
			MessageBox(L"�ɹ����浽:"+FilePathName);
		}
		File.Close();
	}
	
}

//===================���¡�ͼ��ָ������˹�˲���=================
void Cpictest1Dlg::OnBnClickedSege()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	  //��¡ԭͼ������Mat������
	
	if(!g_srcImage.data )
	{
		g_srcImage = imread("start1.bmp");
		if(!g_srcImage.data )
		{
		MessageBox(_T("����ͼ��Ԥ��������ʹ�ø߼�ȥ��������!"));
		return;}
	}
	//g_dstImage1 = g_srcImage.clone();
	//g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	m_gslb.EnableWindow();  
	namedWindow("����˹�˲���", 0);
	//�����켣��
	//createTrackbar("�ں�ֵ��", "��<3>��˹�˲���",&g_nGaussianBlurValue, 40,&Cpictest1Dlg::on_GaussianBlur );
	//createTrackbar("��׼�", "��<3>��˹�˲���",&g_nGaussianVerticalValue, 150,&Cpictest1Dlg::on_GaussianVertical );
	on_GaussianBlur(0,0);
		
}


//===================���¡�ͼ��ָ����sobel��Ե��⡱=================
void Cpictest1Dlg::OnBnClickedSob()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ������srcͬ���ͺʹ�С�ľ���(dst)
		if(!g_dstImage3.data )
	{
		MessageBox(_T("���ȸ�˹�˲���"));
		return;
	}
	Mat g_dstImage;
	m_sobel.EnableWindow();  
	g_dstImage.create( g_dstImage3.size(), g_dstImage3.type() );
	// ������ʾ����
	namedWindow( "��Ч��ͼ��Sobel��Ե���", 0 );
	// ����trackbar
	//createTrackbar( "����ֵ��", "��Ч��ͼ��Sobel��Ե���", &g_sobelKernelSize, 30,&Cpictest1Dlg::on_Sobel);
	// ���ûص�����
	on_Sobel(0, 0);
}


//===================���¡�ͼ��ָ������ֵ����Ե��⡱=================
void Cpictest1Dlg::OnBnClickedBin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!g_sobelAbsGradient_Y.data )
	{
		MessageBox(_T("����Sobel��Ե��⣡"));
		return;
	}
	Mat g_srcGrayImage;
	m_ezh.EnableWindow();  
	namedWindow( "��ֵ��", 0 );
	//createTrackbar( "�Ҷ���ֵ��", "��ֵ����Ե���", &g_binaryThreshold, 25, &Cpictest1Dlg::on_Binary);
	cvtColor( g_sobelAbsGradient_Y, g_srcGrayImage, COLOR_RGB2GRAY);
	adaptiveThreshold(g_srcGrayImage,g_biImage,maxgray,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,(2*7+1),2.75);
	imshow("��ֵ��",g_biImage);
}



//===================���¡�ͼ��ָ������ֵ�˲���=================
void Cpictest1Dlg::OnBnClickedMed()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_zzlb.EnableWindow();  
	if(!g_biImage.data )
	{
		MessageBox(_T("���ȶ�ֵ����Ե��⣡"));
		return;
	}
	namedWindow("��ֵ�˲�",0);
	//createTrackbar( "���ڴ�С��", "��ֵ�˲����ͺ�", &g_medfiltKernel, 10, (cv::TrackbarCallback)Cpictest1Dlg::on_MedianFilter);
	Mat g_medfiltImage2;
    medianBlur(g_biImage,g_medfiltImage,5);
	medianBlur(g_medfiltImage,g_medfiltImage2,5);
	threshold(g_medfiltImage2,g_biFINALImage,125,255,THRESH_BINARY_INV);
	imshow("��ֵ�˲�",g_biFINALImage);
}


//===================���¡�ͼ��ָ�������͡�=================
void Cpictest1Dlg::OnBnClickedDilate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pz.EnableWindow();  
		if(!g_biFINALImage.data )
	{
		MessageBox(_T("������ֵ�˲���"));
		return;
	}
	Mat img_dilate1;
	Mat ele1(3,4,CV_8U,Scalar(1));	//�����һ�����͵ĽṹԪ��
	ele1.at<uchar>(0,2) = 0;
	ele1.at<uchar>(0,3) = 0;
	ele1.at<uchar>(1,0) = 0;
	ele1.at<uchar>(1,3) = 0;
	ele1.at<uchar>(2,0) = 0;
	ele1.at<uchar>(2,1) = 0;
	dilate(g_biFINALImage, img_dilate1, ele1, Point(-1,-1),4);//����4��

	Mat img_dilate2;
	Mat ele2(3,4,CV_8U,Scalar(1));	//����ڶ������ͽṹԪ��
	ele2.at<uchar>(0,0) = 0;
	ele2.at<uchar>(0,1) = 0;
	ele2.at<uchar>(1,0) = 0;
	ele2.at<uchar>(1,3) = 0;
	ele2.at<uchar>(2,2) = 0;
	ele2.at<uchar>(2,3) = 0;
	dilate(img_dilate1, img_dilate2, ele2, Point(-1,-1),3);//����3��

	Mat ele3 = getStructuringElement(MORPH_RECT,Size(4,1),Point(-1,-1));
	dilate(img_dilate2, img_dilate3, ele3, Point(-1,-1),1);//����1��
	namedWindow("����",0);	//��������
	imshow("����",img_dilate3);  //�ڴ�������ʾ���ͺ�ͼ��
	imwrite("GiveToWJF.bmp",img_dilate3);
}

//-----------------------------��ContrastAndBright( )������------------------------------------
//	��������˹�˲������Ļص�����
//-----------------------------------------------------------------------------------------------
void Cpictest1Dlg::on_GaussianBlur(int, void *)
{
	//��˹�˲�
	GaussianBlur( g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1 ), g_nGaussianVerticalValue,g_nGaussianVerticalValue);
	//��ʾ����
	//��������
	imshow("����˹�˲���", g_dstImage3);
}


//-----------------------------------��on_Sobel( )������----------------------------------
//		������Sobel��Ե��ⴰ�ڹ������Ļص�����
//-----------------------------------------------------------------------------------------
void Cpictest1Dlg::on_Sobel(int, void*)
{
	
	// ��Y�����ݶ�
	Sobel( g_dstImage3, g_sobelGradient_Y, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_Y, g_sobelAbsGradient_Y );//�������ֵ���������ת����8λ

	//��ʾЧ��ͼ
	imshow("��Ч��ͼ��Sobel��Ե���", g_sobelAbsGradient_Y);

}


void Cpictest1Dlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bctp.EnableWindow(); 
	if(!img_contour22.data)
	{
		MessageBox(_T("���Ƚ�������ʶ��"));
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
			MessageBox(_T("ͼƬ�ɹ����浽��")+FilePathName);
		}
		else
		{
			MessageBox(L"error");
		}
	}
}


void Cpictest1Dlg::OnBnClickedComp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	namedWindow("����ͼ�ɲ�ɫͼ",WINDOW_NORMAL);
	//namedWindow("ԭͼ",WINDOW_NORMAL);
	//imshow("ԭͼ",g_srcImage);
	imshow("����ͼ�ɲ�ɫͼ",g_Contour24bmp);
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
//��ֵ��
void Cpictest1Dlg::ezh2(int nWidth, int nHeight, BYTE *lpInput, BYTE *lpOutput,int a)
{   
	int t=a;
	if(t<0||t>255)
		MessageBox( _T("�������"), _T("����"),MB_OK|MB_ICONWARNING);
	
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

   for(y=0;y<nHeight;y++)//��ȡ��ɫ���ֵ�����
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


//====================================������ʼ================================================
void Cpictest1Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_new.EnableWindow(); 
	if(!img_dilate3.data)
	{
		MessageBox(_T("���Ƚ���ͼ��ָ"));
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
	//if(str=="ͼƬ1")
		//x=1930;
	//else if(str=="ͼƬ2")
	    //x=2248;
	//else if(str=="ͼƬ3")
		//x=1362;
	//else if(str=="ͼƬ4")
	    //x=1486;
	//else if(str=="ͼƬ5")
		//x=1700;
	//else 
		//x=2000;

	///////////////////////��1��ȥ���±߽�////////////////////////////////////////////////
	int imgr = image.rows;
	int imgc = image.cols;
	for (int i=imgr-up;i<imgr;i++)//�˴�530Ϊϵͳ�е������ڵ�Ԥ��ֵ�������пɵ������������ֵ
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
	///////////////////////��1��ȥ���±߽����////////////////////////////////////////////////


	//////////////////////��2��������ȡ////////////////////////////////////////////////
	Mat img;
	//cvtColor(image,img,COLOR_RGB2GRAY);//����ͼ��ҪΪ��ֵͼ��
	blur( image, img, Size(3,3) ); //ȡ����ǰƽ������ģ����
	//imwrite("smoothAfterRemove.bmp",img);
	vector<vector<Point>> contours; //���Ϊÿһ����ͨ�����������ļ���
	//���vector��size������ͼ���������ĸ���������vector�� size�����������ϵ�ĸ���

	//======findContours======
	findContours(img,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);	


	//======First drawContours======//ȥ���±߽��ȫ���ҵ�������
	Mat img_contour(img.size(),CV_8U,Scalar(0)); 
	drawContours(img_contour,contours,-1,Scalar(255),1,LINE_8 );

	//namedWindow("contours1",WINDOW_NORMAL); 
	//imshow("contours1",img_contour); 
	//imwrite("contours1.bmp",img_contour); 

	//=======����ȡ����ÿһ������============
	double maxarea = 15000; 
    double minarea=min/13.2*x*3.0;  //�����е������������ֵ
	int num = contours.size();
	double MaxLength = 0;
	for (unsigned int i=0;i<contours.size();i++)
	{
		double tmparea = fabs(contourArea(contours[i]));

		//ɾ�����С���趨ֵ������
		if ((tmparea<minarea) | (tmparea>maxarea))
		{
			contours.erase(contours.begin() + i);
			num--;
			continue;
		}

		//����������ֱ�����
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

	//======Second drawContours======//�����ҵ���ȫ�������趨��ֵ֮���ٴ���ȡ����
	Mat img_contour2(img_contour.size(),CV_8U,Scalar(0)); 
	for (unsigned int i=0;i<contours.size();i++)
	{
		drawContours(img_contour2,contours,i,Scalar(255),1,LINE_8 );
	}

	img_contour22=img_contour2;
	
	//////////////////////��2��������ȡ����////////////////////////////////////////////////


	///////////////////////��3������������Ŀ������Ƴ���////////////////////////////////////////////////
	m_sum=num;
	m_max=MaxLength/x*13.2;
	UpdateData(false);
	
	///////////////////////��3���������////////////////////////////////////////////////
	}
}
//============================================================================================




void Cpictest1Dlg::Onmsave()
{
	// TODO: �ڴ���������������
	OnBnClickedSave();
}


void Cpictest1Dlg::On32788()
{
	// TODO: �ڴ���������������
	OnBnClickedComp();
}


void Cpictest1Dlg::Onmtxyvl()
{
	// TODO: �ڴ���������������
	OnRebg();
}


void Cpictest1Dlg::Onmgslb()
{
	// TODO: �ڴ���������������
	OnBnClickedSege();
}


void Cpictest1Dlg::Onmsobel()
{
	// TODO: �ڴ���������������
	OnBnClickedSob();
}


void Cpictest1Dlg::Onmezh()
{
	// TODO: �ڴ���������������
	OnBnClickedBin();
}


void Cpictest1Dlg::Onmzzlb()
{
	// TODO: �ڴ���������������
	OnBnClickedMed();
}


void Cpictest1Dlg::Onmpz()
{
	// TODO: �ڴ���������������
	OnBnClickedDilate();
}


void Cpictest1Dlg::Onmlwsb2()
{
	// TODO: �ڴ���������������
	OnBnClickedButton1();
}


void Cpictest1Dlg::Onmdcdjg()
{
	// TODO: �ڴ���������������
	OnClickedRes();
}


void Cpictest1Dlg::OnBnClickedsmall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	    m_xsyt.EnableWindow(); 
		if(!originalImg.data )
		{
			MessageBox(_T("���ȴ�ԭͼ"));
		}
		namedWindow("ԭͼ",WINDOW_NORMAL); 
	    imshow("ԭͼ",originalImg); 

		CBitmap bitmap;  // CBitmap�������ڼ���λͼ     
		HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��     

		
		//bitmap.LoadBitmap(originalImg);  // ��λͼIDB_BITMAP1���ص�bitmap    
		//hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��    
		//m_Picture1.SetBitmap((HBITMAP)originalImg.data);
}


//=============================����һ������================================
void Cpictest1Dlg::OnBnClickedOne()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_yjtxfg.EnableWindow();
	OnBnClickedSege();
	OnBnClickedSob();
	OnBnClickedBin();
	OnBnClickedMed();
	OnBnClickedDilate();
}


void Cpictest1Dlg::OnBnClickedAfter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_xsclhtp.EnableWindow(); 
	if(!img_contour22.data)
	{
		MessageBox(L"δ��������ʶ��!");
	    return;
	}
	namedWindow("�����Ľ��",WINDOW_NORMAL); 
	imshow("�����Ľ��",img_contour22); 
	
}


void Cpictest1Dlg::OnRegister()
{
	// TODO: �ڴ���������������
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
					MessageBox(_T("�û���������Ϊ��"));
					continue;
			}
	    	if(rpas!=rpas2)
			{
				MessageBox(_T("�������벻һ��"));
				Register.m_rpas=_T("");
				Register.m_rpas2=_T("");
				//Register.UpdateData(false);
			}
		}
	 }while((rpas!=rpas2)||(rusername==""));
		db.Open(_T("test.mdb"),FALSE,FALSE);
	    strSQL.Format(_T("insert into test values('%s','%s')"),rusername,rpas);
        db.Execute(strSQL);
	    MessageBox(_T("ע���û��ɹ�"));
	    db.Close();
	}


void Cpictest1Dlg::OnRevise()
{
	// TODO: �ڴ���������������
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
					MessageBox(_T("�û���������Ϊ��"));
					continue;
			}
	    	if(cpas!=cpas2)
			{
				MessageBox(_T("�������벻һ��"));
				Revise.m_cpas=_T("");
				Revise.m_cpas2=_T("");
			}
		}
	 }while((cpas!=cpas2)||(cusername==""));
		db.Open(_T("test.mdb"),FALSE,FALSE);
	    strSQL.Format(_T("update test set username='%s',key='%s'where username='%s'"),cusername,cpas,cusername);
        db.Execute(strSQL);
	    MessageBox(_T("�޸�����ɹ�"));
	    db.Close();
}


void Cpictest1Dlg::OnDelete()
{
	// TODO: �ڴ���������������
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
	  MessageBox(_T("ɾ���û��ɹ���"));
	}
}


HBRUSH Cpictest1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	CFont m_Font1,m_Font2;
	m_Font1.CreatePointFont(120, L"�����п�"); 
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
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	else
	return hbr;
}

//==========================�˵�-�߼����ܡ��ֶ�ȥ����================
void Cpictest1Dlg::Onsuper()
{
	// TODO: �ڴ���������������
	CSuper super;
    super.DoModal();
}


void Cpictest1Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
