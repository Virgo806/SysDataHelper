
// SysDataDemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SysDataDemo.h"
#include "SysDataDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSysDataDemoDlg 对话框



CSysDataDemoDlg::CSysDataDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYSDATADEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSysDtHelper = NULL;
	m_nUserID = 0;
}

CSysDataDemoDlg::~CSysDataDemoDlg()
{
	if (m_pSysDtHelper)
		m_pSysDtHelper->Disconnect();
	
	UH_SAFE_DELETE(m_pSysDtHelper);
}

void CSysDataDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSysDataDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSysDataDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSysDataDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CSysDataDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CSysDataDemoDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &CSysDataDemoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CSysDataDemoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CSysDataDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON8, &CSysDataDemoDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CSysDataDemoDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CSysDataDemoDlg 消息处理程序

BOOL CSysDataDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSysDataDemoDlg::OnPaint()
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
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSysDataDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSysDataDemoDlg::OnBnClickedButton1()
{
	std::string sPath = "";
	std::string sFile = "";

	if (UtilsHelper::GetAppsPath(sPath))
		sFile = sPath + "AppConfige.ini";

	if (!sFile.empty())
	{
		std::string sHost = "";
		std::string sPort = "";
		std::string sName = "";
		std::string sUser = "";
		std::string sPass = "";

		if (!UtilsHelper::ReadIniKey("DatabasePara", "Host", "", sFile, sHost))
		{
			UtilsHelper::WriteIniKey("DatabasePara", "Host", "127.0.0.1", sFile);
			sHost = "127.0.0.1";
		}

		if (!UtilsHelper::ReadIniKey("DatabasePara", "Port", "", sFile, sPort))
		{
			UtilsHelper::WriteIniKey("DatabasePara", "Port", "53306", sFile);
			sPort = "53306";
		}

		if (!UtilsHelper::ReadIniKey("DatabasePara", "Name", "", sFile, sName))
		{
			UtilsHelper::WriteIniKey("DatabasePara", "Name", "fisms", sFile);
			sName = "fisms";
		}

		if (!UtilsHelper::ReadIniKey("DatabasePara", "User", "", sFile, sUser))
		{
			UtilsHelper::WriteIniKey("DatabasePara", "User", "root", sFile);
			sUser = "root";
		}

		if (!UtilsHelper::ReadIniKey("DatabasePara", "Pass", "", sFile, sPass))
		{
			UtilsHelper::WriteIniKey("DatabasePara", "Pass", "root0000", sFile);
			sPass = "root0000";
		}

		if (NULL == m_pSysDtHelper)
			m_pSysDtHelper = new SysDataHelper::CSysDataHelper();

		if (m_pSysDtHelper->IsConnect())
			m_pSysDtHelper->Disconnect();

		if (m_pSysDtHelper->Connection(sHost, atoi(sPort.c_str()), sName, sUser, sPass, SysDataHelper::E_DATABSE_TYPE_MYSQL))
		{
			m_nUserID = 0;
			GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		}
	}
}

void CSysDataDemoDlg::OnBnClickedButton2()
{
	if (NULL == m_pSysDtHelper)
		return;

	if (!m_pSysDtHelper->IsConnect())
		return;

	if (m_pSysDtHelper->Disconnect())
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	}
}

void CSysDataDemoDlg::OnBnClickedButton4()
{
	CTabUserRecordPtr pUserRec(new CTabUserRecord);

	pUserRec->user_name = "test";
	pUserRec->user_pw = "test";
	pUserRec->role_id = 2;
	pUserRec->level = 2;
	pUserRec->unit_id = 1;
	pUserRec->comment = "中文测试￥￥%……&&*";

	m_nUserID = m_pSysDtHelper->InsterUserRecord(pUserRec, true);
	if (m_nUserID > 0)
		UtilsHelper::LogsDebug(" 插入数据库记录成功，记录ID：%d", m_nUserID);
	else
		UtilsHelper::LogsError(" 插入数据库记录失败。");
}

void CSysDataDemoDlg::OnBnClickedButton7()
{
	CTabUserRecordPtr pUserRec = m_pSysDtHelper->GetUserRecordByID(m_nUserID);
	if (pUserRec.get())
	{
		UtilsHelper::LogsDebug("查询记录成功，记录信息：%d, %s, %s, %d, %d, %d, %s", pUserRec->user_id,
			pUserRec->user_name.c_str(), pUserRec->user_pw.c_str(), pUserRec->role_id, pUserRec->level, pUserRec->unit_id, pUserRec->comment.c_str());
	}
	else
		UtilsHelper::LogsError("查询记录失败，记录ID：%d", m_nUserID);
}

void CSysDataDemoDlg::OnBnClickedButton5()
{
	CTabUserRecordPtr pUserRec = m_pSysDtHelper->GetUserRecordByID(m_nUserID);
	if (pUserRec.get())
	{
		pUserRec->comment = "特殊太56";
		if (m_pSysDtHelper->UpdateUserRecord(pUserRec))
		{
			UtilsHelper::LogsDebug("修改数据库记录成功，参数<%d, %s, %s, %d, %d, %d, %s>", pUserRec->user_id,
				pUserRec->user_name.c_str(), pUserRec->user_pw.c_str(), pUserRec->role_id, pUserRec->level, pUserRec->unit_id, pUserRec->comment.c_str());
		}
		else
		{
			UtilsHelper::LogsError("修改数据库记录失败，记录ID：%d", m_nUserID);
		}
	}
	else
		UtilsHelper::LogsError("查询数据库记录失败，记录ID：%d", m_nUserID);
}

void CSysDataDemoDlg::OnBnClickedButton6()
{
	if (m_pSysDtHelper->DeleteUserRecord(m_nUserID))
		UtilsHelper::LogsDebug("删除数据库记录成功，记录ID：%d", m_nUserID);
	else
		UtilsHelper::LogsError("删除数据库记录失败，记录ID：%d", m_nUserID);
}

void CSysDataDemoDlg::OnBnClickedButton3()
{
	CTabUserRecordVec vecUser = m_pSysDtHelper->GetAllUserRecordToVec();
	if (vecUser.size() > 0)
	{
		for (int i = 0; i < (int)vecUser.size(); i++)
		{
			UtilsHelper::LogsDebug("查询记录信息：%d, %s, %s, %d, %d, %d, %s", vecUser[i]->user_id,
				vecUser[i]->user_name.c_str(), vecUser[i]->user_pw.c_str(), vecUser[i]->role_id, vecUser[i]->level, vecUser[i]->unit_id, vecUser[i]->comment.c_str());
		}
	}
	else
		UtilsHelper::LogsError("查询记录集失败。");
}


void CSysDataDemoDlg::OnBnClickedButton8()
{
	CTabUserRecordMap mapUser = m_pSysDtHelper->GetAllUserRecordToMap();
	if (mapUser.size() > 0)
	{
		CTabUserRecordMapIterator itUser = mapUser.begin();
		for (itUser; itUser != mapUser.end(); itUser++)
		{
			UtilsHelper::LogsDebug("查询记录信息：%d, %s, %s, %d, %d, %d, %s", itUser->second->user_id,
				itUser->second->user_name.c_str(), itUser->second->user_pw.c_str(), itUser->second->role_id, itUser->second->level, itUser->second->unit_id, itUser->second->comment.c_str());
		}
	}
	else
		UtilsHelper::LogsError("查询记录集失败。");
}

void CSysDataDemoDlg::OnBnClickedButton9()
{
	ProviderHelper::IDataObjectSetPtr pObjectSet;
	std::string sSQL = "";

	if (ProviderHelper::CreateDataProviderSQLite(pObjectSet, "test.db"))
	{
		if (!pObjectSet->IsExistTable("tab_user"))
		{
			sSQL = "CREATE TABLE IF NOT EXISTS tab_user("\
				"name vaechar(255)"\
				", pass vaechar(255))";
			pObjectSet->Execute(sSQL);
		}

		sSQL = "insert into tab_user(name, pass) values('中文测温', '0000')";
		pObjectSet->Execute(sSQL);

		ProviderHelper::IDataRecordSetPtr pRecord;
		sSQL = "select * from tab_user";
		if (pObjectSet->Execute(sSQL, pRecord))
		{
			pRecord->MoveFirst();
			while (!pRecord->IsEof())
			{
				std::string sName = "";
				std::string sPass = "";
				pRecord->GetFieldValue("name", sName);
				pRecord->GetFieldValue("pass", sPass);
				UtilsHelper::LogsDebug("查询记录信息：%s, %s", sName.c_str(), sPass.c_str());

				pRecord->MoveNext();
			};
		}
	}
}
