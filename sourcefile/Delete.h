#pragma once


// CDelete �Ի���

class CDelete : public CDialogEx
{
	DECLARE_DYNAMIC(CDelete)

public:
	CDelete(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDelete();

// �Ի�������
	enum { IDD = IDD_Delete };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_dusername;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
