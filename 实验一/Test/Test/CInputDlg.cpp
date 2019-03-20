// CInputDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "CInputDlg.h"
#include "afxdialogex.h"


// CInputDlg 对话框

IMPLEMENT_DYNAMIC(CInputDlg, CDialogEx)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_n(30)
	, m_r(300.0)
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_n);
	DDX_Text(pDX, IDC_EDIT2, m_r);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CInputDlg 消息处理程序


void CInputDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	GetDlgItem(IDC_EDIT1)->SetFocus();
	((CEdit *)GetDlgItem(IDC_EDIT1))->SetSel(0,-1);
}
