#pragma once
#include <string>
using namespace std;

// TabVideoProcess 对话框

class TabVideoProcess : public CDialog
{
	DECLARE_DYNAMIC(TabVideoProcess)

public:
	TabVideoProcess(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TabVideoProcess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_VIDEOPROCESS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton mButtonExecute;
	afx_msg void OnBnClickedButtonExecute();
private:
	void VideoProcess(string filePath);
};
