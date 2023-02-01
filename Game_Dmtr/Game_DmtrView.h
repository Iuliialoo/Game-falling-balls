
// Game_DmtrView.h: интерфейс класса CGameDmtrView
//

#pragma once
#include "Game_DmtrDoc.h"

class CGameDmtrView : public CView
{
protected: // создать только из сериализации
	CGameDmtrView() noexcept;
	DECLARE_DYNCREATE(CGameDmtrView)

// Атрибуты
public:
	CGameDmtrDoc* GetDocument() const;

// Операции
public:
	void createLevel(int);

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CGameDmtrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // версия отладки в Game_DmtrView.cpp
inline CGameDmtrDoc* CGameDmtrView::GetDocument() const
   { return reinterpret_cast<CGameDmtrDoc*>(m_pDocument); }
#endif

