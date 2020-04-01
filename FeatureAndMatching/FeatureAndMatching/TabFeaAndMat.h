#pragma once


// TabFeaAndMat 对话框

class TabFeaAndMat : public CDialog
{
	DECLARE_DYNAMIC(TabFeaAndMat)

public:
	TabFeaAndMat(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TabFeaAndMat();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_FEAANDMAT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
