// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__B036A49E_0362_42E4_8080_E43F598073B9__INCLUDED_)
#define AFX_TESTVIEW_H__B036A49E_0362_42E4_8080_E43F598073B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <vector>


class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	bool haveRect;
	vec<2> rectSize;
	Transform transform;

	inline void DrawImage(CDC *dc, CRect &rect)const;

	//{{AFX_MSG(CTestView)
	afx_msg void OnDrawpic();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnClockwise();
	afx_msg void OnAntiClockwise();
	afx_msg void OnReflectX();
	afx_msg void OnReflectY();
	afx_msg void OnReflectOrigin();
	afx_msg void OnShearXPos();
	afx_msg void OnShearXNeg();
	afx_msg void OnShearYPos();
	afx_msg void OnShearYNeg();
	afx_msg void OnRestore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument()
   { return (CTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__B036A49E_0362_42E4_8080_E43F598073B9__INCLUDED_)
