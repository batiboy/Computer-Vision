
// FeatureAndMatchingDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FeatureAndMatching.h"
#include "FeatureAndMatchingDlg.h"
#include "afxdialogex.h"
#include "Display.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFeatureAndMatchingDlg 对话框



CFeatureAndMatchingDlg::CFeatureAndMatchingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREANDMATCHING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFeatureAndMatchingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_OPERATIONS, mTabOps);
	DDX_Control(pDX, IDC_OUTPUTAREA, mOutput);
}

BEGIN_MESSAGE_MAP(CFeatureAndMatchingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OPERATIONS, &CFeatureAndMatchingDlg::OnTcnSelchangeTabOperations)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CFeatureAndMatchingDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CFeatureAndMatchingDlg 消息处理程序

BOOL CFeatureAndMatchingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->SetTabOperations();
	this->InitDisplay();
	Dp->OutputLine(_T("初始化中..."));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFeatureAndMatchingDlg::InitDisplay()
{
	auto d = Display::GetInstance();
	d->OutputArea = &this->mOutput;
}

void CFeatureAndMatchingDlg::SetTabOperations(void)
{
	mTabOps.InsertItem(0, _T("FERNS"));
	mTabOps.InsertItem(1, _T("特征与匹配"));
	mTabOps.InsertItem(2, _T("视频实时特征检测"));

	Tab1.Create(IDD_TAB_FERNS_DIALOG, &mTabOps);
	CRect rs;
	mTabOps.GetClientRect(&rs);
	// HiDPI 支持，需要修改rs.top的偏移量，100%为22。
	rs.top += 26;
	Tab1.MoveWindow(&rs);
	Tab1.ShowWindow(true);
	mTabOps.SetCurSel(0);

	Tab2.Create(IDD_TAB_FEAANDMAT_DIALOG, &mTabOps);
	Tab2.MoveWindow(&rs);
	Tab2.ShowWindow(false);

	Tab3.Create(IDD_TAB_VIDEOPROCESS_DIALOG, &mTabOps);
	Tab3.MoveWindow(&rs);
	Tab3.ShowWindow(false);
}

void CFeatureAndMatchingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFeatureAndMatchingDlg::OnPaint()
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
HCURSOR CFeatureAndMatchingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFeatureAndMatchingDlg::OnTcnSelchangeTabOperations(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	Tab1.ShowWindow(false);
	Tab2.ShowWindow(false);
	Tab3.ShowWindow(false);
	int selection = mTabOps.GetCurSel();
	switch (selection)
	{
	case 0:
		Tab1.ShowWindow(true);
		break;
	case 1:
		Tab2.ShowWindow(true);
		break;
	case 2:
		Tab3.ShowWindow(true);
		break;
	default:;
	}
	*pResult = 0;
}


void CFeatureAndMatchingDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	Dp->ClearOutput();
}
