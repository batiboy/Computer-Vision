// TabFERNS.cpp: 实现文件
//

#include "pch.h"
#include "FeatureAndMatching.h"
#include "TabFERNS.h"
#include "afxdialogex.h"


// TabFERNS 对话框

IMPLEMENT_DYNAMIC(TabFERNS, CDialog)

TabFERNS::TabFERNS(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB_FERNS_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

TabFERNS::~TabFERNS()
{
}

void TabFERNS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabFERNS, CDialog)
END_MESSAGE_MAP()


// TabFERNS 消息处理程序
