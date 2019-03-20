// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

#include "InputRectDialog.h"

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
	ON_COMMAND(IDM_DRAWPIC, OnDrawpic)
	ON_COMMAND(IDM_LEFT, OnLeft)
	ON_COMMAND(IDM_RIGHT, OnRight)
	ON_COMMAND(IDM_UP, OnUp)
	ON_COMMAND(IDM_DOWN, OnDown)
	ON_COMMAND(IDM_ZOOMIN, OnZoomIn)
	ON_COMMAND(IDM_ZOOMOUT, OnZoomOut)
	ON_COMMAND(IDM_CLOCKWISE, OnClockwise)
	ON_COMMAND(IDM_ANTICLOCKWISE, OnAntiClockwise)
	ON_COMMAND(IDM_REFLECTX, OnReflectX)
	ON_COMMAND(IDM_REFLECTY, OnReflectY)
	ON_COMMAND(IDM_REFLECTORIGIN, OnReflectOrigin)
	ON_COMMAND(IDM_SHEARXPOS, OnShearXPos)
	ON_COMMAND(IDM_SHEARXNEG, OnShearXNeg)
	ON_COMMAND(IDM_SHEARYPOS, OnShearYPos)
	ON_COMMAND(IDM_SHEARYNEG, OnShearYNeg)
	ON_COMMAND(IDM_RESTORE, OnRestore)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	this->haveRect = false;
	this->transform = Transform::Identity();
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

void CTestView::OnDraw(CDC *pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	CRect rect;

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

	this->DrawImage(&memDC, rect);

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
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
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

inline void CTestView::DrawImage(CDC *dc, CRect &rect)const{
	{
		CPen pen;
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		dc->SelectObject(pen);

		dc->MoveTo(-(rect.Width()+1)/2, 0);
		dc->LineTo(+(rect.Width()+1)/2, 0);

		dc->MoveTo(0, -(rect.Height()+1)/2);
		dc->LineTo(0, +(rect.Height()+1)/2);

		pen.DeleteObject();
	}

	if(this->haveRect){
		int i;

		double halfWidth = (this->rectSize.x)/2;
		double halfHeight = (this->rectSize.y)/2;

		vec<2> p[4];

		p[0].x = -halfWidth;
		p[0].y = -halfHeight;
		p[1].x = -halfWidth;
		p[1].y = +halfHeight;
		p[2].x = +halfWidth;
		p[2].y = +halfHeight;
		p[3].x = +halfWidth;
		p[3].y = -halfHeight;

		for(i=0;i<4;i++){
			p[i] = (this->transform)*(p[i]);
		}

		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		dc->SelectObject(pen);
		for(i=0;i<4;i++){
			int j = (i+1)%4;
			dc->MoveTo(p[i]);
			dc->LineTo(p[j]);
		}
		pen.DeleteObject();
	}
}

void CTestView::OnDrawpic(){

	// TODO: Add your command handler code here
	CInputRectDialog dialog;
	if(dialog.DoModal()==IDOK){
		this->rectSize.x = dialog.m_width;
		this->rectSize.y = dialog.m_height;
		if(!this->haveRect){
			this->transform = Transform::Identity();
			this->haveRect = true;
		}
		this->Invalidate(false);
	}
}

void CTestView::OnLeft() 
{
	// TODO: Add your command handler code here
	vec<2> v;
	v.x = -10;
	v.y = 0;
	this->transform.compositeWith(Transform::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnRight() 
{
	// TODO: Add your command handler code here
	vec<2> v;
	v.x = +10;
	v.y = 0;
	this->transform.compositeWith(Transform::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnUp() 
{
	// TODO: Add your command handler code here
	vec<2> v;
	v.x = 0;
	v.y = +10;
	this->transform.compositeWith(Transform::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnDown() 
{
	// TODO: Add your command handler code here
	vec<2> v;
	v.x = 0;
	v.y = -10;
	this->transform.compositeWith(Transform::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnZoomIn() 
{
	// TODO: Add your command handler code here
	vec<2> v;
	v.x = 2;
	v.y = 2;
	Transform transform = Transform::Scale(v);
	transform.compositeWith(this->transform);
	this->transform = transform;
	this->Invalidate(false);
}

void CTestView::OnZoomOut() 
{
	// TODO: Add your command handler code here
	vec<2> v;
	v.x = 0.5;
	v.y = 0.5;
	Transform transform = Transform::Scale(v);
	transform.compositeWith(this->transform);
	this->transform = transform;
	this->Invalidate(false);
}

void CTestView::OnClockwise() 
{
	// TODO: Add your command handler code here
	Transform transform = Transform::Rotate(-PI/6);
	transform.compositeWith(this->transform);
	this->transform = transform;
	this->Invalidate(false);
}

void CTestView::OnAntiClockwise() 
{
	// TODO: Add your command handler code here
	Transform transform = Transform::Rotate(+PI/6);
	transform.compositeWith(this->transform);
	this->transform = transform;
	this->Invalidate(false);
}

void CTestView::OnReflectX() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform::ReflectX());
	this->Invalidate(false);
}

void CTestView::OnReflectY() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform::ReflectY());
	this->Invalidate(false);
}

void CTestView::OnReflectOrigin() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform::ReflectOrigin());
	this->Invalidate(false);
}

void CTestView::OnShearXPos() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform::Shear(1, 0));
	this->Invalidate(false);
}

void CTestView::OnShearXNeg() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform::Shear(-1, 0));
	this->Invalidate(false);
}

void CTestView::OnShearYPos() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform::Shear(0, 1));
	this->Invalidate(false);
}

void CTestView::OnShearYNeg() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform::Shear(0, -1));
	this->Invalidate(false);
}

void CTestView::OnRestore() 
{
	// TODO: Add your command handler code here
	this->transform = Transform::Identity();
	this->Invalidate(false);
}
