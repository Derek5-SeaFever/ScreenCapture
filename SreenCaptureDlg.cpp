
// SreenCaptureDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SreenCapture.h"
#include "SreenCaptureDlg.h"
#include "afxdialogex.h"
#include "CShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSreenCaptureDlg 对话框



CSreenCaptureDlg::CSreenCaptureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SREENCAPTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSreenCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSreenCaptureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CAPTURE, &CSreenCaptureDlg::OnBnClickedBtnCapture)
	ON_BN_CLICKED(IDC_BUTTON2, &CSreenCaptureDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSreenCaptureDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSreenCaptureDlg 消息处理程序

BOOL CSreenCaptureDlg::OnInitDialog()
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

void CSreenCaptureDlg::OnPaint()
{
	
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);    //这个IDB_BITMAP1要自己添加
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 455, 453);   // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
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
HCURSOR CSreenCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//新建
void CSreenCaptureDlg::OnBnClickedBtnCapture()
{
	//过程(备忘)：
	//1.制作一个弹窗
	//2.点击按钮，弹出做好的弹窗
	//3.修改弹窗样式
	//4.调整弹窗大小
	//5.截图屏幕
	//6.将截图显示到弹窗
	//7.截图选框
	//8.保存选框图像
	ShowWindow(SW_HIDE);	//点击前关闭窗口
	Sleep(200);				//延时等待关闭窗口
	CShowDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);	//恢复窗口
}

//博客
void CSreenCaptureDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	system("start explorer http://www.cnblogs.com/seafever/");
}

//Help?
void CSreenCaptureDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, _T("open"), _T(".\\res\\help.html"), NULL, NULL, SW_SHOWNORMAL);
}

