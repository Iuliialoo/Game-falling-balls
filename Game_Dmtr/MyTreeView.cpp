// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "Game_Dmtr.h"
#include "MyTreeView.h"
#include "Game_DmtrDoc.h"

// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView

void CMyTreeView::FillTree() {
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_level = tree.InsertItem(L"level", -1, -1, NULL, TVI_FIRST);
	level1 = tree.InsertItem(L"level 1", -1, -1, m_level, TVI_LAST);
	level2 = tree.InsertItem(L"level 2", -1, -1, m_level, TVI_LAST);
	level3 = tree.InsertItem(L"level 3", -1, -1, m_level, TVI_LAST);
}


//BOOL CMyTreeView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
	// TODO: добавьте специализированный код или вызов базового класса

//	return CTreeView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	/*lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;*/
	lpCreateStruct->style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CMyTreeView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CTreeCtrl& tree = GetTreeCtrl();

	CRect rc;


	tree.GetItemRect(level1, &rc, false);

	if (rc.PtInRect(point)) {
		for (int i = 0; i < m_pDoc->circleList.size(); i++) {
			m_pDoc->circleList[i].startMove = false;
		}
		m_pDoc->myPlayer.isGameOver = false;
		m_pDoc->myPlayer.isGameWin = false;
		for (int i = 0; i < m_pDoc->circleList.size(); i++) {
			m_pDoc->circleList[i].create(&rc, 1);
		}
	}

	tree.GetItemRect(level2, &rc, false);

	if (rc.PtInRect(point)) {
		for (int i = 0; i < m_pDoc->circleList.size(); i++) {
			m_pDoc->circleList[i].startMove = false;
		}
		m_pDoc->myPlayer.isGameOver = false;
		m_pDoc->myPlayer.isGameWin = false;
		for (int i = 0; i < m_pDoc->circleList.size(); i++) {
			m_pDoc->circleList[i].create(&rc, 2);
		}
	}

	tree.GetItemRect(level3, &rc, false);

	if (rc.PtInRect(point)) {
		for (int i = 0; i < m_pDoc->circleList.size(); i++) {
			m_pDoc->circleList[i].startMove = false;
		}
		m_pDoc->myPlayer.isGameOver = false;
		m_pDoc->myPlayer.isGameWin = false;
		for (int i = 0; i < m_pDoc->circleList.size(); i++) {
			m_pDoc->circleList[i].create(&rc, 3);
		}
	}

	CTreeView::OnLButtonDblClk(nFlags, point);
}

