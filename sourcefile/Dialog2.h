#pragma once


// Dialog2 �Ի���

class Dialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog2)

public:
	Dialog2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	int m_yuzhi;
	afx_msg void OnBnClickedOk();
	int m_down;
	double m_down2;
	double m_yuzhi;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_pic;
	CString str;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditYz();
	afx_msg void OnEnChangeEditDown();
	afx_msg void OnEnChangeEditrate();
};
