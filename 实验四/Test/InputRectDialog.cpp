// InputRectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "InputRectDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputRectDialog dialog


CInputRectDialog::CInputRectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInputRectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputRectDialog)
	m_width = 300.0;
	m_height = 200.0;
	//}}AFX_DATA_INIT
}


void CInputRectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputRectDialog)
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDV_MinMaxDouble(pDX, m_width, 1., 1000.);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDV_MinMaxDouble(pDX, m_height, 1., 1000.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputRectDialog, CDialog)
	//{{AFX_MSG_MAP(CInputRectDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputRectDialog message handlers
