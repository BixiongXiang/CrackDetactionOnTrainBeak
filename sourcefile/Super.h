#pragma once


// CSuper �Ի���

class CSuper : public CDialogEx
{
	DECLARE_DYNAMIC(CSuper)

public:
	CSuper(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSuper();
	Mat g_srcImage,g_maskImage;//����ԭʼͼ��Ŀ��ͼ���Ҷ�ͼ����ģͼ
	int g_nFillMode ;//��ˮ����ģʽ
	int g_nLowDifference ,g_nUpDifference;//�������ֵ���������ֵ
	int g_nConnectivity ;//��ʾfloodFill������ʶ���Ͱ�λ����ֵͨ
	int g_bIsColor;//�Ƿ�Ϊ��ɫͼ�ı�ʶ������ֵ
	bool g_bUseMask;//�Ƿ���ʾ��Ĥ���ڵĲ���ֵ
	int g_nNewMaskVal;//�µ����»��Ƶ�����ֵ
	Mat g_floodImage;

// �Ի�������
	enum { IDD = IDD_Super };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
