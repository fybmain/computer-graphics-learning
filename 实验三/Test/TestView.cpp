// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

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
	this->fill = false;
	this->ReadPoint();
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
	this->UpdatePolygon(pDC);

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

/*
void CTestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	vec<2> mouse = this->translateMousePosition(point);
	this->currentLine.a = mouse;
	this->currentLine.b = mouse;
	this->mousePressed = true;

	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	vec<2> mouse = this->translateMousePosition(point);
	this->currentLine.b = mouse;
	this->lineList.push_back(this->currentLine);
	this->mousePressed = false;

	CView::OnLButtonUp(nFlags, point);
}

void CTestView::OnMouseMove(UINT nFlags, CPoint point){
	// TODO: Add your message handler code here and/or call default

	if(this->mousePressed){
		vec<2> mouse = this->translateMousePosition(point);
		this->currentLine.b = mouse;
		this->InvalidateRect(NULL, true);
	}

	CView::OnMouseMove(nFlags, point);
}

void CTestView::OnSize(UINT nType, int cx, int cy){
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->GetClientRect(&(this->clientRect));
}

vec<2> CTestView::translateMousePosition(const CPoint mouse){
	vec<2> raw;
	raw = mouse;

	vec<2> result;
	result.x = raw.x-clientRect.Width()/2;
	result.y = clientRect.Height()/2-raw.y;
	return result;
}

void CTestView::DrawLines((CDC *pDC){
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

	for(int i=0;i<this->lineList.size();i++){
		line<2> l = this->lineList[i];
		this->DrawLine(&memDC, l);
	}
	if(this->mousePressed){
		this->DrawLine(&memDC, this->currentLine);
	}

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
*/

void CTestView::DrawLinePixel(CDC *dc, const vec<2> point){
	vec<3> color;
	color.red = 0;
	color.green = 0;
	color.blue = 0;
	dc->SetPixelV(point, color);
}

void CTestView::DrawLine(CDC* dc, const line<2> l){
	/*
	// deprecated code of drawing a line by MFC
	pDC->MoveTo(l.a);
	pDC->LineTo(l.b);
	*/

	using namespace std;

	const double eps = 1e-6;

	vec<2> a = l.a;
	vec<2> b = l.b;
	vec<2> p;

	if(fabs(a.x-b.x)<eps){
		if(a.y>b.y){
			swap(a, b);
		}
		for(p=floor(a);p.y<b.y;p.y+=1){
			this->DrawLinePixel(dc, p);
		}
	}else{
		double k,d;
		k = gradient(a, b);
		if(k<-1){
			// k<-1
			if(a.y<b.y){
				swap(a, b);
			}
			d=-1-0.5*k;
			for(p=a;p.y>b.y;p.y-=1){
				this->DrawLinePixel(dc, p);
				if(d<0){
					p.x+=1;
					d-=1+k;
				}else{
					d-=1;
				}
			}
		}else if(k<0){
			// -1<=k<0
			if(a.x>b.x){
				swap(a,b);
			}
			d=-0.5-k;
			for(p=a;p.x<b.x;p.x+=1){
				this->DrawLinePixel(dc, p);
				if(d>0){
					p.y--;
					d-=1+k;
				}else{
					d-=k;
				}
			}
		}else if(k<=1){
			// 0<=k<=1
			if(a.x>b.x){
				swap(a,b);
			}
			d = 0.5-k;
			for(p=a;p.x<b.x;p.x+=1){
				this->DrawLinePixel(dc, p);
				if(d<0){
					p.y++;
					d+=1-k;
				}else{
					d-=k;
				}
			}
		}else{
			// k>1
			if(a.y>b.y){
				swap(a, b);
			}
			d = 1-k*0.5;
			for(p=a;p.y<b.y;p.y+=1){
				this->DrawLinePixel(dc, p);
				if(d>=0){
					p.x++;
					d+=1-k;
				}else{
					d+=1;
				}
			}
		}
	}
}

void CTestView::ReadPoint(){
	p.resize(7);

	p[0].x = 50;	p[0].y = 100;
	p[1].x = -150;	p[1].y = 300;
	p[2].x = -250;	p[2].y = 50;
	p[3].x = -150;	p[3].y = -250;
	p[4].x = 0.0;	p[4].y = -50;
	p[5].x = 100;	p[5].y = -250;
	p[6].x = 300;	p[6].y = 150;
}

void CTestView::UpdatePolygon(CDC *dc){
	GetClientRect(&(this->clientRect));
	CRect &rect = this->clientRect;

	dc->SetMapMode(MM_ANISOTROPIC);
	dc->SetWindowExt(rect.Width(), rect.Height());
	dc->SetViewportExt(rect.Width(), -rect.Height());
	dc->SetViewportOrg(rect.Width()/2, rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2, -rect.Height()/2);

	DrawPolygon(dc);
	if(fill)FillPolygon(dc);
}

void CTestView::DrawPolygon(CDC *dc){
	int s = p.size();
	int i;
	for(i=0;i<s;i++){
		int j = (i+1)%s;
		line<2> l;
		l.a = p[i];
		l.b = p[j];
		this->DrawLine(dc, l);
	}
}

void CTestView::FillPolygon(CDC *dc){
	FillContext context;
	context.color = this->color;

	int s = this->p.size();
	context.p.resize(s);

	int i;
	for(i=0;i<s;i++){
		context.p[i] = round(this->p[i]);
	}

	context.CreateBucket();
	context.CreateEdge();
	context.Fill(dc);
}

void CTestView::OnDrawpic(){

	// TODO: Add your command handler code here
	COLORREF colorRef=RGB(0, 255, 255);
	CColorDialog dialog(colorRef, CC_SOLIDCOLOR);
	if(dialog.DoModal()==IDOK){
		colorRef = dialog.GetColor();
		this->color = vec<3>::fromColorRef(colorRef);
		fill = true;
		this->InvalidateRect(NULL);
	}
}
