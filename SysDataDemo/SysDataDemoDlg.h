
// SysDataDemoDlg.h: 头文件
//

#pragma once


// CSysDataDemoDlg 对话框
class CSysDataDemoDlg : public CDialogEx
{
// 构造
public:
	CSysDataDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CSysDataDemoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSDATADEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	SysDataHelper::CSysDataHelper* m_pSysDtHelper;
	int m_nUserID;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
};
