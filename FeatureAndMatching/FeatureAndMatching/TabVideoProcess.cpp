// TabVideoProcess.cpp: 实现文件
//

#include "pch.h"
#include "FeatureAndMatching.h"
#include "TabVideoProcess.h"
#include "afxdialogex.h"
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgcodecs/legacy/constants_c.h"
#include <iostream>
#include "Display.h"
using namespace cv;
using namespace std;



// TabVideoProcess 对话框

IMPLEMENT_DYNAMIC(TabVideoProcess, CDialog)

TabVideoProcess::TabVideoProcess(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB_VIDEOPROCESS_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

TabVideoProcess::~TabVideoProcess()
{
}

void TabVideoProcess::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_EXECUTE, mButtonExecute);
    DDX_Control(pDX, IDC_BUTTON_STOP, mButtonStop);
}


BEGIN_MESSAGE_MAP(TabVideoProcess, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, &TabVideoProcess::OnBnClickedButtonExecute)
    ON_BN_CLICKED(IDC_BUTTON_STOP, &TabVideoProcess::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// TabVideoProcess 消息处理程序


void TabVideoProcess::OnBnClickedButtonExecute()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;
	filter = "所有文件(*.avi,*.3gp,*.mp4,*.rm,*rmvb,*flash) | *.avi;*.3gp;*.mp4;*.rm;*.rmvb;*flash";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
	if (dlg.DoModal() == IDOK)  //用户单击OK按钮中止对话框的返回值
	{
		CString FileName = dlg.GetPathName();   //获取文件路径名 如D:\\1.jpg
		string filename = (CStringA)FileName;   //把CString转换成filename。
        this->mButtonExecute.EnableWindow(false);
        isClicked = false;
		VideoProcess(filename);
        Dp->PrintTimeElapsed();
        this->mButtonExecute.EnableWindow(true);
	}   
}

void TabVideoProcess::VideoProcess(string filePath)
{
    VideoCapture cap;
    cap.open(filePath); //打开视频,等价于   VideoCapture cap("E://2.avi");

    if (!cap.isOpened())
        return;

    int width = cap.get(CAP_PROP_FRAME_WIDTH);  //帧宽度
    int height = cap.get(CAP_PROP_FRAME_HEIGHT); //帧高度
    int frameRate = cap.get(CAP_PROP_FPS);  //帧率 x frames/s
    int totalFrames = cap.get(CAP_PROP_FRAME_COUNT); //总帧数

    Ptr<ORB> orb = ORB::create();
    Mat frame;
    float i = 0;
    float j = 0;
    char tem[20];
    char temp[16];

    CString s(filePath.c_str());
    Dp->OutputLine(_T("加载视频: ") + s);
    CString str;
    str.Format(_T("原视频宽度：%d ， 高度：%d ，总帧数：%d ，帧率：%d "), width, height, totalFrames, frameRate);
    Dp->OutputLine(str);
    Dp->OutputLine(_T("开始处理：视频实时特征检测！"));
    Dp->StartTick();

    while (!isClicked)
    {
        cap >> frame;//等价于cap.read(frame);
        if (frame.empty())
            break;

        // vector of keypoints
        std::vector<cv::KeyPoint> keypoints;
        // Construction of the Fast feature detector object
        // feature point detection
        orb->detect(frame, keypoints);
        Mat tmpFrame;
        // Draw key points
        drawKeypoints(frame, keypoints, tmpFrame, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
        Mat outFrame;
        resize(tmpFrame, outFrame, Size(1440, 810), 0, 0);
        ++i;
        j = 1.0 * i / totalFrames * 100;
        sprintf_s(tem, "Progress = %.2f%%", j);
        putText(outFrame, tem, Point(15, 50), cv::FONT_HERSHEY_PLAIN, 1.25, Scalar(0, 200, 0), 2, 8);
        sprintf_s(temp, "Keypoints = %d", keypoints.size());
        putText(outFrame, temp, Point(15, 25), cv::FONT_HERSHEY_PLAIN, 1.25, Scalar(0, 200, 0), 2, 8);
        imshow("视频特征检测", outFrame);
        moveWindow("视频特征检测", 250, 100);   
        if (waitKey(20) > 0)
        {
            break;
        }           
    }
    cv::destroyWindow("视频特征检测");
    if (i == totalFrames)
    {
        Dp->OutputLine(_T("视频处理完毕！"));
    }
    else
    {
        Dp->OutputLine(_T("停止视频处理！"));
    }
    cap.release();
}


void TabVideoProcess::OnBnClickedButtonStop()
{
    // TODO: 在此添加控件通知处理程序代码
    isClicked = true;
}
