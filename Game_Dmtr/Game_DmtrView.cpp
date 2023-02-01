
// Game_DmtrView.cpp: реализация класса CGameDmtrView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Game_Dmtr.h"
#endif

#include "Game_DmtrDoc.h"
#include "Game_DmtrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameDmtrView

IMPLEMENT_DYNCREATE(CGameDmtrView, CView)

BEGIN_MESSAGE_MAP(CGameDmtrView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CGameDmtrView

CGameDmtrView::CGameDmtrView() noexcept
{
	// TODO: добавьте код создания

}

CGameDmtrView::~CGameDmtrView()
{
}

BOOL CGameDmtrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CGameDmtrView

void CGameDmtrView::OnDraw(CDC* pDC)
{
	CGameDmtrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	/*pDC->MoveTo(, );
	pDC->LineTo(rect.Width(), rect.Height() / 2);

	pDC->MoveTo(0, rect.Height() / 2);*/

	/*for (double i = 0; i < rect.Width(); i += 0.1)
	{
		pDC->LineTo(i * (rect.Width() / 3.14) / 2, -sin(i) * rect.Height() / 2 + rect.Height() / 2);
	}*/
	CString str;
	str.Format(L"SPACE - START");
	pDC->TextOutW(0, 0, str);
	
	if (!pDoc->myPlayer.isGameOver) {
		pDoc->drawCircles(pDC);
		pDoc->drawPlayer(pDC);
	}
	else {
		str.Format(L"YOU LOSE");
		pDC->TextOutW(rect.Width() / 2.0, rect.Height()/ 2.0, str);
	}

	if (pDoc->myPlayer.isGameWin) {
		str.Format(L"YOU WIN");
		pDC->TextOutW(rect.Width() / 2.0, rect.Height() / 2.0, str);
	}
	else {
		str.Format(L"");
		pDC->TextOutW(rect.Width() / 2.0, rect.Height() / 2.0, str);
	}

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CGameDmtrView

BOOL CGameDmtrView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGameDmtrView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGameDmtrView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CGameDmtrView

#ifdef _DEBUG
void CGameDmtrView::AssertValid() const
{
	CView::AssertValid();
}

void CGameDmtrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDmtrDoc* CGameDmtrView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDmtrDoc)));
	return (CGameDmtrDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CGameDmtrView
void CGameDmtrView::createLevel(int speed) {
	CGameDmtrDoc* pDoc = GetDocument();
	//pDoc->myPlayer.isGameOver = false;

	CRect rect;
	GetClientRect(&rect);

	for (int i = 0; i < pDoc->circleList.size(); i++) {
		pDoc->circleList[i].startMove = false;;
	}
	

	int circleCount = 10;
	pDoc->circleList.resize(circleCount);

	for (int i = 0; i < circleCount; i++) {
		pDoc->circleList.resize(i + 1);
		do {
			pDoc->circleList[i].create(&rect, speed);
		} while (!pDoc->checkCreate());
	}
}

void CGameDmtrView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	srand(time(NULL));

	CGameDmtrDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	pDoc->myPlayer.create(&rect);
	createLevel(1);

	// TODO: добавьте специализированный код или вызов базового класса
	SetTimer(0, 10, NULL);
}


void CGameDmtrView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CGameDmtrDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);


	if (!pDoc->myPlayer.isGameOver) {
		pDoc->moveCircle();
		pDoc->win(&rect, pDoc->myPlayer);
	}

	Invalidate(TRUE);
	CView::OnTimer(nIDEvent);
}




void CGameDmtrView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CGameDmtrDoc* pDoc = GetDocument();
	if (nChar == VK_LEFT)
		pDoc->myPlayer.x -= 5;
	if (nChar == VK_RIGHT)
		pDoc->myPlayer.x += 5;
	if (nChar == VK_SPACE) {
		for (int i = 0; i < pDoc->circleList.size(); i++) {
			pDoc->circleList[i].startMove = true;
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

