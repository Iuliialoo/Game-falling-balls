
// Game_DmtrDoc.h: интерфейс класса CGameDmtrDoc 
//


#pragma once
#include "MyTreeView.h"
#include <vector>
#include "DLGCOLOR.h"

class CPlayer {
public:
	int x, y, r;
	CPlayer();
	void create(CRect*);
	void Draw(CDC* pDC);
	bool isGameOver;
	bool isGameWin;
	int speed;
};

class CMyCircle {
public:
	int x, y, r, dy;
	CMyCircle();
	COLORREF color;
	void create(CRect*, int);
	void create1(CRect*, int);
	void Draw(CDC* pDC);
	void move();
	bool checkTouch(CPlayer&);
	bool startMove;
};


class CGameDmtrDoc : public CDocument
{
protected: // создать только из сериализации
	CGameDmtrDoc() noexcept;
	DECLARE_DYNCREATE(CGameDmtrDoc)

// Атрибуты
public:
	std::vector<CMyCircle> circleList;
	CPlayer myPlayer;

	CMyTreeView* m_pTreeView;

	CDLGCOLOR colorDlg;

// Операции
public:
	void drawCircles(CDC* pDC);
	void drawPlayer(CDC* pDC);
	void moveCircle();
	void win(CRect* rect, CPlayer&);
	void getColor(int);

	int checkCreate();

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CGameDmtrDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnSettingColorBlack();
	afx_msg void OnSettingColorBlue();
	afx_msg void OnSettingColorGreen();
	afx_msg void OnSettingColorRed();
	afx_msg void OnSettingMyColor();
	
	//afx_msg void OnBnClickedMfccolorbutton1();
};
