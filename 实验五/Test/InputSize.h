#if !defined(AFX_INPUTSIZE_H__CF6A7DA2_8E03_4028_A17B_972867EB383C__INCLUDED_)
#define AFX_INPUTSIZE_H__CF6A7DA2_8E03_4028_A17B_972867EB383C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputSize dialog

class CInputSize : public CDialog
{
// Construction
public:
	CInputSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputSize)
	enum { IDD = IDD_INPUT_SIZE };
	double	m_width;
	double	m_height;
	double	m_thickness;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputSize)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTSIZE_H__CF6A7DA2_8E03_4028_A17B_972867EB383C__INCLUDED_)
