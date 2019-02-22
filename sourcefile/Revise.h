#pragma once


// CRevise 对话框

class CRevise : public CDialogEx
{
	DECLARE_DYNAMIC(CRevise)

public:
	CRevise(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRevise();

// 对话框数据
	enum { IDD = IDD_Revise };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_cpas;
	CString m_cpas2;
	CString m_cusername;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
