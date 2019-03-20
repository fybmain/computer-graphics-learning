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
	ON_COMMAND(IDM_PLAY, OnPlay)
	ON_UPDATE_COMMAND_UI(IDM_PLAY, OnUpdatePlay)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	this->playing = false;
	this->R = 800;
	this->d = 1000;
	this->alpha = 0;
	this->beta = 0;
	this->theta = 0;
	this->phi = PI/2;
	this->transform = Transform3D::Identity();

	this->ReadData();
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

	this->drawObject(&memDC);

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

void CTestView::ReadData() {
	const double goldenSection = (sqrt(5)-1)/2;
	double a = 160;
	double b = a * goldenSection;

	int i,j;

	const double v[12][3] = {
		{ 0, a, b },
		{ 0, a, -b },
		{ a, b, 0 },
		{ a, -b, 0 },
		{ 0, -a, -b },
		{ 0, -a, b },
		{ b, 0, a },
		{ -b, 0, a },
		{ b, 0, -a },
		{ -b, 0, -a },
		{ -a, b, 0 },
		{ -a, -b, 0 },
	};

	this->p.resize(12);
	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			this->p[i].comp[j] = v[i][j];
		}
	}

	const int vi[20][3] = {
		{ 0, 6, 2 },
		{ 2, 6, 3 },
		{ 3, 6, 5 },
		{ 5, 6, 7 },
		{ 0, 7, 6 },
		{ 2, 3, 8 },
		{ 1, 2, 8 },
		{ 0, 2, 1 },
		{ 0, 1, 10 },
		{ 1, 9, 10 },
		{ 1, 8, 9 },
		{ 3, 4, 8 },
		{ 3, 5, 4 },
		{ 4, 5, 11 },
		{ 7, 10, 11 },
		{ 0, 10, 7 },
		{ 4, 11, 9 },
		{ 4, 9, 8 },
		{ 5, 7, 11 },
		{ 9, 11, 10 },
	};
	this->f.resize(20);
	for(i=0;i<20;i++){
		this->f[i].p_ind.resize(3);
		for(int j=0;j<3;j++){
			this->f[i].p_ind[j] = vi[i][j];
		}
	}
}

void CTestView::drawObject(CDC *dc){
	int i,j;

	double k[9];
	k[1] = sin(this->theta);
	k[2] = sin(this->phi);
	k[3] = cos(this->theta);
	k[4] = cos(this->phi);
	k[5] = k[2] * k[3];
	k[6] = k[2] * k[1];
	k[7] = k[4] * k[3];
	k[8] = k[4] * k[1];

	const double perMat[4][4] = {
		{ k[3], 0, -k[1], 0 },
		{ -k[8], k[2], -k[7], 0 },
		{ -k[6], -k[4], -k[5], (this->R) },
		{ 0, 0, 0, 1 },
	};

	Transform3D perspective;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			perspective.value[i][j] = perMat[i][j];
		}
	}

	Transform3D totalTransform = perspective * (this->transform);
	for(int face_ind=0;face_ind<(this->f.size());face_ind++){
		Face &face = this->f[face_ind];
		std::vector<vec<2> > v;
		v.resize(face.p_ind.size());
		for(j=0;j<v.size();j++){
			vec<3> rp = this->p[face.p_ind[j]];
			vec<3> tp = totalTransform * rp;
			v[j].x = (this->d)*tp.x/tp.z;
			v[j].y = (this->d)*tp.y/tp.z;
		}

		const double normal = cross(v[0]-v[1], v[1]-v[2]);
		if(normal>=0){
			for(j=0;j<3;j++){
				int k = (j+1) % 3;
				dc->MoveTo(v[j]);
				dc->LineTo(v[k]);
			}
		}
	}
}

void CTestView::OnPlay() 
{
	// TODO: Add your command handler code here
	this->playing = !(this->playing);
	if(this->playing){
		this->SetTimer(888, 150, NULL);
	}else{
		this->KillTimer(888);
	}
}

void CTestView::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(this->playing){
		pCmdUI->SetCheck(true);
		pCmdUI->SetText("Í£Ö¹");
	}else{
		pCmdUI->SetCheck(false);
		pCmdUI->SetText("¿ªÊ¼");
	}
}

void CTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	this->alpha = PI * 5 / 180;
	this->beta = PI * 5 / 180;
	Transform3D transform = Transform3D::RotateY(this->beta) * Transform3D::RotateX(this->alpha);
	this->transform = transform * (this->transform);
	this->Invalidate(false);

	CView::OnTimer(nIDEvent);
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	this->R += 100;
	this->Invalidate(false);

	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	this->R -= 100;
	this->Invalidate(false);

	CView::OnRButtonDblClk(nFlags, point);
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(!(this->playing)){
		switch(nChar){
		case VK_UP:
			this->alpha = PI * (-5) / 180;
			this->transform = Transform3D::RotateX(this->alpha) * (this->transform);
			break;
		case VK_DOWN:
			this->alpha = PI * (+5) / 180;
			this->transform = Transform3D::RotateX(this->alpha) * (this->transform);
			break;
		case VK_LEFT:
			this->beta = PI * (-5) / 180;
			this->transform = Transform3D::RotateY(this->beta) * (this->transform);
			break;
		case VK_RIGHT:
			this->beta = PI * (+5) / 180;
			this->transform = Transform3D::RotateY(this->beta) * (this->transform);
			break;
		default:
			break;
		}
		Invalidate(false);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
