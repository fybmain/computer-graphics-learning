#if !defined(AFX_INPUTRECTDIALOG_H__51D0D8D1_EA7E_4E28_9B47_F80FDA4D4C4E__INCLUDED_)
#define AFX_INPUTRECTDIALOG_H__51D0D8D1_EA7E_4E28_9B47_F80FDA4D4C4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputRectDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputRectDialog dialog

class CInputRectDialog : public CDialog
{
// Construction
public:
	CInputRectDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputRectDialog)
	enum { IDD = IDD_DIALOG_INPUT_RECT };
	double	m_width;
	double	m_height;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputRectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputRectDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTRECTDIALOG_H__51D0D8D1_EA7E_4E28_9B47_F80FDA4D4C4E__INCLUDED_)
