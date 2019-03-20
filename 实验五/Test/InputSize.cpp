// InputSize.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "InputSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputSize dialog


CInputSize::CInputSize(CWnd* pParent /*=NULL*/)
	: CDialog(CInputSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputSize)
	m_width = 100.0;
	m_height = 100.0;
	m_thickness = 100.0;
	//}}AFX_DATA_INIT
}


void CInputSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputSize)
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDV_MinMaxDouble(pDX, m_width, 1., 1000.);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDV_MinMaxDouble(pDX, m_height, 1., 1000.);
	DDX_Text(pDX, IDC_THICKNESS, m_thickness);
	DDV_MinMaxDouble(pDX, m_thickness, 1., 1000.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputSize, CDialog)
	//{{AFX_MSG_MAP(CInputSize)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputSize message handlers
