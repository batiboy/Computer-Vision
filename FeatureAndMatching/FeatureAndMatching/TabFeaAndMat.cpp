// TabFeaAndMat.cpp: 实现文件
//

#include "pch.h"
#include "FeatureAndMatching.h"
#include "TabFeaAndMat.h"
#include "afxdialogex.h"


// TabFeaAndMat 对话框

IMPLEMENT_DYNAMIC(TabFeaAndMat, CDialog)

TabFeaAndMat::TabFeaAndMat(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB_FEAANDMAT_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

TabFeaAndMat::~TabFeaAndMat()
{
}

void TabFeaAndMat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabFeaAndMat, CDialog)
END_MESSAGE_MAP()


// TabFeaAndMat 消息处理程序
