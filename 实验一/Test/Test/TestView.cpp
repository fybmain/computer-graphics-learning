
// TestView.cpp: CTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"

#include "CInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_DRAWPIC, &CTestView::OnDrawpic)
	ON_COMMAND(IDM_DRAWPIC, &CTestView::OnDrawpic)
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView() noexcept
{
	// TODO: 在此处添加构造代码

	n = 0;
	r = 0.0;
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestView 绘图

void CTestView::OnDraw(CDC* /*pDC*/)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CTestView 打印

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView 消息处理程序

void CTestView::OnDrawpic(){
	// TODO: 在此添加命令处理程序代码
	CInputDlg dlg;
	if (dlg.DoModal() == IDOK) {
		n = dlg.m_n;
		r = dlg.m_r;
	}else{
		return;
	}
	RedrawWindow();
	p = new vec2[n];
	Diamond();
	delete[] p;
}


void CTestView::Diamond(){
	// TODO: 在此处添加实现代码.

	CDC *dc=GetDC();
	CRect rect;
	GetClientRect(&rect);
	dc->SetMapMode(MM_ANISOTROPIC);
	dc->SetWindowExt(rect.Width(), rect.Height());
	dc->SetViewportExt(rect.Width(), -rect.Height());
	dc->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	CPen pen(PS_SOLID, 1, 0xff0000);
	dc->SelectObject(&pen);

	const double PI = acos(-1);
	double alpha = 0;
	double theta = (PI * 2) / n;
	for (int i = 0; i < n; i++) {
		double angle = fmod(alpha + theta * i, PI * 2);
		p[i] = vec2::unit(angle)*r;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			dc->MoveTo(p[i]);
			dc->LineTo(p[j]);
		}
	}

	ReleaseDC(dc);
}
