#pragma once


// CRevise �Ի���

class CRevise : public CDialogEx
{
	DECLARE_DYNAMIC(CRevise)

public:
	CRevise(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRevise();

// �Ի�������
	enum { IDD = IDD_Revise };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_cpas;
	CString m_cpas2;
	CString m_cusername;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
