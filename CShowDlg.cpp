// CShowDlg.cpp: 实现文件
//

#include "pch.h"
#include "SreenCapture.h"
#include "CShowDlg.h"
#include "afxdialogex.h"


// CShowDlg 对话框

IMPLEMENT_DYNAMIC(CShowDlg, CDialogEx)

CShowDlg::CShowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW_DLG, pParent)
{
	//采集屏幕当前图像
	m_nWidth = GetSystemMetrics(SM_CXSCREEN);//获取屏幕宽
	m_nHeight = GetSystemMetrics(SM_CYSCREEN);//获取屏幕高
	CDC *pDC = GetDesktopWindow()->GetDC();//获取屏幕上下文
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, m_nWidth, m_nHeight);//创建位图
	m_memDC.CreateCompatibleDC(pDC);
	m_memDC.SelectObject(&bmp);
	m_memDC.BitBlt(0, 0, m_nWidth, m_nHeight, pDC, 0, 0, SRCCOPY);//创建内存DC
	//释放DC、GDI
	pDC->DeleteDC();
	bmp.DeleteObject();
}

CShowDlg::~CShowDlg()
{
}

void CShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CShowDlg 消息处理程序


BOOL CShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//获取屏幕大小信息
	m_nWidth = GetSystemMetrics(SM_CXSCREEN);
	m_nHeight = GetSystemMetrics(SM_CYSCREEN);
	//调整弹窗大小
	MoveWindow(0, 0, m_nWidth, m_nHeight);
	//初始化橡皮条                     阴影线                        手柄向外
	m_tracker.m_nStyle = CRectTracker::hatchedBorder | CRectTracker::resizeOutside;
	m_tracker.m_nHandleSize = 8;			//控制柄粗细
	m_tracker.m_rect.SetRect(0, 0, 0, 0);	//初始化选框大小

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CShowDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
	//将屏幕截图显示到弹窗
	dc.BitBlt(0, 0, m_nWidth, m_nHeight, &m_memDC, 0, 0, SRCCOPY);
	//绘制橡皮条
	m_tracker.Draw(&dc);

					   // 不为绘图消息调用 CDialogEx::OnPaint()
}


void CShowDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CShowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_tracker.HitTest(point) == CRectTracker::hitNothing)
	{
		m_tracker.TrackRubberBand(this, point, TRUE);
		m_tracker.m_rect.NormalizeRect();//反转坐标正常化
	}
	else
	{
		m_tracker.Track(this, point, TRUE);
		m_tracker.m_rect.NormalizeRect();//反转坐标正常化
	}
	//刷新
	Invalidate(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CShowDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//获得选框宽高
	int nWidth = m_tracker.m_rect.Width();
	int nHeight = m_tracker.m_rect.Height();
	//创建一个位图
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&m_memDC, nWidth, nHeight);
	//一个临时DC
	CDC tempDC;
	tempDC.CreateCompatibleDC(NULL);
	tempDC.SelectObject(&bmp);
	//复制选框图像
	tempDC.BitBlt(0, 0, nWidth, nHeight, &m_memDC, m_tracker.m_rect.left, m_tracker.m_rect.top, SRCCOPY);
	//打开剪切板
	OpenClipboard();
	//清空剪切板
	EmptyClipboard();
	//复制到剪切板
	SetClipboardData(CF_BITMAP, bmp);
	//关闭剪切板
	CloseClipboard();
	//关闭弹框
	EndDialog(0);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}
