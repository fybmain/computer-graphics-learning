// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

#include "InputSize.h"

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
	ON_COMMAND(IDM_LEFT, OnLeft)
	ON_COMMAND(IDM_RIGHT, OnRight)
	ON_COMMAND(IDM_UP, OnUp)
	ON_COMMAND(IDM_DOWN, OnDown)
	ON_COMMAND(IDM_ZOOMIN, OnZoomIn)
	ON_COMMAND(IDM_ZOOMOUT, OnZoomOut)
	ON_COMMAND(IDM_REFLECTORIGIN, OnReflectOrigin)
	ON_COMMAND(IDM_RESTORE, OnRestore)
	ON_COMMAND(IDM_SHEAR_X_NEG, OnShearXNeg)
	ON_COMMAND(IDM_SHEAR_X_POS, OnShearXPos)
	ON_COMMAND(IDM_SHEAR_Y_NEG, OnShearYNeg)
	ON_COMMAND(IDM_SHEAR_Y_POS, OnShearYPos)
	ON_COMMAND(IDM_SHEAR_Z_NEG, OnShearZNeg)
	ON_COMMAND(IDM_SHEAR_Z_POS, OnShearZPos)
	ON_COMMAND(IDM_ANTICLOCKWISE_X, OnAnticlockwiseX)
	ON_COMMAND(IDM_ANTICLOCKWISE_Y, OnAnticlockwiseY)
	ON_COMMAND(IDM_ANTICLOCKWISE_Z, OnAnticlockwiseZ)
	ON_COMMAND(IDM_BACK, OnBack)
	ON_COMMAND(IDM_CLOCKWISE_X, OnClockwiseX)
	ON_COMMAND(IDM_CLOCKWISE_Y, OnClockwiseY)
	ON_COMMAND(IDM_CLOCKWISE_Z, OnClockwiseZ)
	ON_COMMAND(IDM_FRONT, OnFront)
	ON_COMMAND(IDM_REFLECT_X, OnReflectX)
	ON_COMMAND(IDM_REFLECT_Y, OnReflectY)
	ON_COMMAND(IDM_REFLECT_Z, OnReflectZ)
	ON_COMMAND(IDM_SET_SIZE, OnSetSize)
	ON_COMMAND(IDM_REFLECT_XOY, OnReflectXOY)
	ON_COMMAND(IDM_REFLECT_YOZ, OnReflectYOZ)
	ON_COMMAND(IDM_REFLECT_ZOX, OnReflectZOX)
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
	this->haveCuboid = false;
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

inline void CTestView::DrawFace(CDC *dc, const Face &face)const{
	size_t s = face.p.size();
	for(size_t i = 0;i<s;i++){
		int j =  (i+1)%s;
		dc->MoveTo(face.p[i].toVec2());
		dc->LineTo(face.p[j].toVec2());
	}
}

inline void CTestView::DrawImage(CDC *dc, CRect &rect)const{
	{
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		dc->SelectObject(pen);

		dc->MoveTo(0, 0);
		dc->LineTo(+(rect.Width()+1)/2, 0);

		dc->MoveTo(0, 0);
		dc->LineTo(0, +(rect.Height()+1)/2);

		int mx = max(rect.Width(), rect.Height());
		dc->MoveTo(0, 0);
		dc->LineTo(-mx, -mx);

		pen.DeleteObject();
	}

	if(this->haveCuboid){
		int i,j;

		double halfX = (this->cuboidSize.x)/2;
		double halfY = (this->cuboidSize.y)/2;
		double halfZ = (this->cuboidSize.z)/2;

		vec<3> p[8];
		for(i=0;i<8;i++){
			for(j=0;j<3;j++){
				double tmp;
				if(i&(1<<j)){
					tmp = this->cuboidSize.comp[j];
				}else{
					tmp = 0;
				}
				p[i].comp[j] = tmp;
			}
		}
		
		int faceIndex[3][4] = {
			{0, 2, 6, 4},
			{0, 4, 5, 1},
			{0, 1, 3, 2},
		};

		Face face[6];
		for(i=0;i<3;i++){
			face[i*2].p.resize(4);
			for(j=0;j<4;j++){
				int index = faceIndex[i][4-j-1];
				face[i*2].p[j] = p[index];
			}

			face[i*2+1].p.resize(4);
			int d = (1<<i);
			for(j=0;j<4;j++){
				int index = faceIndex[i][j]+d;
				face[i*2+1].p[j] = p[index];
			}
		}

		double c[6];
		for(i=0;i<6;i++){
			face[i] = (Transform3D::ObliqueProject())*(this->transform)*(face[i]);
			const vec<2> p0 = face[i].p[0].toVec2();
			const vec<2> p1 = face[i].p[1].toVec2();
			const vec<2> p2 = face[i].p[2].toVec2();
			c[i] = cross(p1-p0, p2-p1);
		}

		CPen pen;

		pen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
		dc->SelectObject(pen);
		for(i=0;i<6;i++){
			if(c[i]<0){
				this->DrawFace(dc, face[i]);
			}
		}
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		dc->SelectObject(pen);
		for(i=0;i<6;i++){
			if(c[i]>=0){
				this->DrawFace(dc, face[i]);
			}
		}
		pen.DeleteObject();
	}
}

void CTestView::OnLeft() 
{
	// TODO: Add your command handler code here
	vec<3> v;
	v.x = -10;
	v.y = 0;
	v.z = 0;
	this->transform.compositeWith(Transform3D::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnRight() 
{
	// TODO: Add your command handler code here
	vec<3> v;
	v.x = +10;
	v.y = 0;
	v.z = 0;
	this->transform.compositeWith(Transform3D::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnUp() 
{
	// TODO: Add your command handler code here
	vec<3> v;
	v.x = 0;
	v.y = +10;
	v.z = 0;
	this->transform.compositeWith(Transform3D::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnDown() 
{
	// TODO: Add your command handler code here
	vec<3> v;
	v.x = 0;
	v.y = -10;
	v.z = 0;
	this->transform.compositeWith(Transform3D::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnFront() 
{
	// TODO: Add your command handler code here
	vec<3> v;
	v.x = 0;
	v.y = 0;
	v.z = +10;
	this->transform.compositeWith(Transform3D::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnBack() 
{
	// TODO: Add your command handler code here
	vec<3> v;
	v.x = 0;
	v.y = 0;
	v.z = -10;
	this->transform.compositeWith(Transform3D::Translate(v));
	this->Invalidate(false);
}

void CTestView::OnZoomIn() 
{
	// TODO: Add your command handler code here
	vec<3> v;
	v.x = 2;
	v.y = 2;
	v.z = 2;
	Transform3D transform = Transform3D::Scale(v);
	transform.compositeWith(this->transform);
	this->transform = transform;
	this->Invalidate(false);
}

void CTestView::OnZoomOut() 
{
	// TODO: Add your command handler code here
	vec<3> v;
	v.x = 0.5;
	v.y = 0.5;
	v.z = 0.5;
	Transform3D transform = Transform3D::Scale(v);
	transform.compositeWith(this->transform);
	this->transform = transform;
	this->Invalidate(false);
}

void CTestView::OnReflectX() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ReflectX());
	this->Invalidate(false);
}

void CTestView::OnReflectY() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ReflectY());
	this->Invalidate(false);
}

void CTestView::OnReflectZ() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ReflectZ());
	this->Invalidate(false);
}

void CTestView::OnReflectXOY() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ReflectXOY());
	this->Invalidate(false);
}

void CTestView::OnReflectYOZ() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ReflectYOZ());
	this->Invalidate(false);
}

void CTestView::OnReflectZOX() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ReflectZOX());
	this->Invalidate(false);
}

void CTestView::OnReflectOrigin() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ReflectOrigin());
	this->Invalidate(false);
}

void CTestView::OnShearXNeg() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ShearX(-1, -1));
	this->Invalidate(false);
}

void CTestView::OnShearXPos() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ShearX(+1, +1));
	this->Invalidate(false);
}

void CTestView::OnShearYNeg() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ShearY(-1, -1));
	this->Invalidate(false);
}

void CTestView::OnShearYPos() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ShearY(+1, +1));
	this->Invalidate(false);
}

void CTestView::OnShearZNeg() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ShearZ(-1, -1));
	this->Invalidate(false);
}

void CTestView::OnShearZPos() 
{
	// TODO: Add your command handler code here
	this->transform.compositeWith(Transform3D::ShearZ(+1, +1));
	this->Invalidate(false);
}

void CTestView::OnAnticlockwiseX() 
{
	const vec<3> p0 = (this->transform)*(vec<3>::zero());
	this->transform.compositeWith(Transform3D::RotateX(+PI/6, p0));
	this->Invalidate(false);
}

void CTestView::OnAnticlockwiseY() 
{
	const vec<3> p0 = (this->transform)*(vec<3>::zero());
	this->transform.compositeWith(Transform3D::RotateY(+PI/6, p0));
	this->Invalidate(false);
}

void CTestView::OnAnticlockwiseZ() 
{
	const vec<3> p0 = (this->transform)*(vec<3>::zero());
	this->transform.compositeWith(Transform3D::RotateZ(+PI/6, p0));
	this->Invalidate(false);
}

void CTestView::OnClockwiseX() 
{
	// TODO: Add your command handler code here
	const vec<3> p0 = (this->transform)*(vec<3>::zero());
	this->transform.compositeWith(Transform3D::RotateX(-PI/6, p0));
	this->Invalidate(false);
}

void CTestView::OnClockwiseY() 
{
	// TODO: Add your command handler code here
	const vec<3> p0 = (this->transform)*(vec<3>::zero());
	this->transform.compositeWith(Transform3D::RotateY(-PI/6, p0));
	this->Invalidate(false);
}

void CTestView::OnClockwiseZ() 
{
	// TODO: Add your command handler code here
	const vec<3> p0 = (this->transform)*(vec<3>::zero());
	this->transform.compositeWith(Transform3D::RotateZ(-PI/6, p0));
	this->Invalidate(false);
}

void CTestView::OnRestore() 
{
	// TODO: Add your command handler code here
	this->transform = Transform3D::Identity();
	this->Invalidate(false);
}

void CTestView::OnSetSize() 
{
	// TODO: Add your command handler code here
	CInputSize dialog;
	if(dialog.DoModal()==IDOK){
		this->cuboidSize.x = dialog.m_width;
		this->cuboidSize.y = dialog.m_height;
		this->cuboidSize.z = dialog.m_thickness;
		if(!this->haveCuboid){
			this->transform = Transform3D::Identity();
			this->haveCuboid = true;
		}
		this->Invalidate(false);
	}
}
