#pragma once


// TabFERNS 对话框

class TabFERNS : public CDialog
{
	DECLARE_DYNAMIC(TabFERNS)

public:
	TabFERNS(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TabFERNS();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_FERNS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
