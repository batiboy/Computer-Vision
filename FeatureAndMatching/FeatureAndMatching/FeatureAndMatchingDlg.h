
// FeatureAndMatchingDlg.h: 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TabFERNS.h"
#include "TabFeaAndMat.h"
#include "TabVideoProcess.h"

// CFeatureAndMatchingDlg 对话框
class CFeatureAndMatchingDlg : public CDialogEx
{
// 构造
public:
	CFeatureAndMatchingDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEATUREANDMATCHING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl mTabOps;
	TabFERNS Tab1;
	TabFeaAndMat Tab2;
	TabVideoProcess Tab3;
private:
	void SetTabOperations();
	void InitDisplay();
public:
	afx_msg void OnTcnSelchangeTabOperations(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit mOutput;
	afx_msg void OnBnClickedButtonClear();
};
