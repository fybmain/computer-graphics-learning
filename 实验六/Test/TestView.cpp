// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"

#include <math.h>

#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

#include "combination.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(IDM_DRAW_BEZIER, OnDrawBezier)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	this->drawing = false;
	this->editingPoint = -1;
	this->p.clear();
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	CRect &rect = this->clientRect;
	this->GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width()/2, rect.Height()/2);

	CDC memDC;
	CBitmap memBitmap;

	memDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC.SelectObject(&memBitmap);
	memDC.FillSolidRect(rect, pDC->GetBkColor());

	rect.OffsetRect(-rect.Width()/2, -rect.Height()/2);
	memDC.SetMapMode(MM_ANISOTROPIC);
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width()/2, rect.Height()/2);

	this->drawBezier(&memDC);

	pDC->BitBlt(
		rect.left, rect.top,
		rect.Width(), rect.Height(),
		&memDC,
		-rect.Width()/2, -rect.Height()/2,
		SRCCOPY
	);
	memBitmap.DeleteObject();
	memDC.DeleteDC();
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::OnDrawBezier() 
{
	// TODO: Add your command handler code here
	this->MessageBox("左键绘制控制多边形定点，右键结束绘制", "提示", MB_OK);
	this->p.clear();
	vec<2> point;
	this->editingPoint = this->p.size();
	this->p.push_back(point);
	this->drawing = true;
}

void CTestView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(this->editingPoint>=0){
		this->p[editingPoint] = this->translateMousePosition(point);
		this->Invalidate(false);
	}

	CView::OnMouseMove(nFlags, point);
}


void CTestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!(this->drawing)){
		vec<2> mouse = this->translateMousePosition(point);
		for(int i=0;i<(this->p.size());i++){
			const double dist = (mouse-p[i]).length();
			if(dist<=controlableRadius){
				this->editingPoint = i;
				break;
			}
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(this->editingPoint>=0){
		vec<2> v = this->translateMousePosition(point);
		this->p[editingPoint] = v;
		if(this->drawing){
			if((this->p.size())<(maxControlPointNum-1)){
				this->editingPoint = this->p.size();
				this->p.push_back(v);
			}else{
				this->drawing = false;
				this->editingPoint = -1;
				this->MessageBox("控制点数量已达到上限", "提示", MB_ICONERROR);
			}
		}else{
			this->editingPoint = -1;
		}
	}

	CView::OnLButtonUp(nFlags, point);
}

void CTestView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(this->drawing){
		this->drawing = false;
		this->editingPoint = -1;
		this->MessageBox("拖动控制点可继续编辑曲线形状", "提示", MB_OK);
	}

	CView::OnRButtonUp(nFlags, point);
}

vec<2> CTestView::translateMousePosition(const CPoint mouse){
	vec<2> raw;
	raw = mouse;

	vec<2> result;
	result.x = raw.x-clientRect.Width()/2;
	result.y = clientRect.Height()/2-raw.y;
	return result;
}

void CTestView::drawBezier(CDC *dc){
	double r;
	int i;

	if(this->p.empty())return;

	CPen blackPen;
	blackPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen nullPen;
	nullPen.CreatePen(PS_NULL, 1, RGB(255, 255, 255));
	CBrush redBrush;
	redBrush.CreateStockObject(GRAY_BRUSH);
	CBrush greenBrush;
	greenBrush.CreateSolidBrush(RGB(0, 255, 0));

	// Draw controlable area of control points
	r = controlableRadius;
	dc->SelectObject(&nullPen);
	dc->SelectObject(&greenBrush);
	for(i=0;i<(this->p.size());i++){
		dc->Ellipse(p[i].x-r, p[i].y-r, p[i].x+r, p[i].y+r);
	}

	// Draw control points
	r = controlPointRadius;
	dc->SelectObject(&blackPen);
	dc->SelectObject(&redBrush);
	for(i=0;i<(this->p.size());i++){
		dc->Ellipse(p[i].x-r, p[i].y-r, p[i].x+r, p[i].y+r);
	}

	// Draw control polygon
	dc->SelectObject(&blackPen);
	for(i=1;i<(this->p.size());i++){
		dc->MoveTo(p[i-1]);
		dc->LineTo(p[i]);
	}

	redBrush.DeleteObject();
	blackPen.DeleteObject();

	CPen bluePen;
	bluePen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	dc->SelectObject(&bluePen);

	const double step = 0.001;

	const size_t n = this->p.size();
	double t;
	dc->MoveTo(this->p[0]);
	for(t=0;t<=1;t+=step){
		vec<2> currentP;
		currentP.x = 0;
		currentP.y = 0;

		for(i=0;i<n;i++){
			const double c = combination(n-1, i)*pow(t, i)*pow(1-t, n-1-i);
			currentP.x += p[i].x*c;
			currentP.y += p[i].y*c;
		}
		dc->LineTo(currentP);
	}

	bluePen.DeleteObject();
}
