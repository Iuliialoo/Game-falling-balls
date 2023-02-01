
// Game_DmtrDoc.cpp: реализация класса CGameDmtrDoc 
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

#include <propkey.h>

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGameDmtrDoc

IMPLEMENT_DYNCREATE(CGameDmtrDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameDmtrDoc, CDocument)
	ON_COMMAND(ID_SETTING_COLOR_BLACK, &CGameDmtrDoc::OnSettingColorBlack)
	ON_COMMAND(ID_SETTING_COLOR_BLUE, &CGameDmtrDoc::OnSettingColorBlue)
	ON_COMMAND(ID_SETTING_COLOR_GREEN, &CGameDmtrDoc::OnSettingColorGreen)
	ON_COMMAND(ID_SETTING_COLOR_RED, &CGameDmtrDoc::OnSettingColorRed)
	ON_COMMAND(ID_changeColor, &CGameDmtrDoc::OnSettingMyColor)
	//ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CGameDmtrDoc::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()

CMyCircle::CMyCircle() {
	r = 0;
	x = 0;
	y = 0;
	dy = 0;
	color = RGB(0, 0, 0);
}


void CMyCircle::create(CRect* rect, int speed) {
	startMove = false;
	r = 20 + rand() % 20;
	x = (r + 5) + rand() % (rect->Width() - 2 * r - 10);
	y = (r + 5) + rand() % (rect->Height() / 3 * 2);

	dy = speed;
}

void CMyCircle::create1(CRect* rect, int speed) {
	r = 20 + rand() % 20;
	x = (r + 5) + rand() % (rect->Width() - 2 * r - 10);
	y = (r + 5) + rand() % (rect->Height() / 3 * 2);

	dy = speed;
}

void CMyCircle::Draw(CDC* pDC) {
	CPen pen(PS_SOLID, 1, color);
	pDC->SelectObject(&pen);

	pDC->MoveTo(x + r, y);
	pDC->AngleArc(x, y, r, 0, 360);
}

void CMyCircle::move() {
	if (startMove)
		y += dy;
}

bool CMyCircle::checkTouch(CPlayer& player) {
	int deltaX = x - player.x, deltaY = y - player.y;
	float dis = sqrt(deltaX * deltaX + deltaY * deltaY);
	if (dis <= (r + player.r)) {
		return true;
	}
	
	return false;
}

void CGameDmtrDoc::getColor(int color) {
	for (int i = 0; i < circleList.size(); i++) {
		circleList[i].color = color;
	}
}



CPlayer::CPlayer() {
	r = 0;
	x = 0;
	y = 0;
	isGameOver = false;
	isGameWin = false;
}

void CPlayer::create(CRect* rect) {
	isGameWin = false;
	r = 30;
	x = rect->Width() / 2;
	y = rect->Height() - r - 50;

}


void CPlayer::Draw(CDC* pDC) {
	CPen pen(PS_SOLID, 2, RGB(153, 50, 204));
	pDC->SelectObject(&pen);

	pDC->MoveTo(x + r, y);
	//pDC->Rectangle(500, 400, 5, 10);
	pDC->AngleArc(x, y, r, 0, 360);
}





void CGameDmtrDoc::drawCircles(CDC* pDC) {
	for (int i = 0; i < circleList.size(); i++) {
		circleList[i].Draw(pDC);
	}
}

void CGameDmtrDoc::drawPlayer(CDC* pDC) {
	myPlayer.Draw(pDC);
}

void  CGameDmtrDoc::moveCircle() {
	for (int i = 0; i < circleList.size(); i++) {
		circleList[i].move();
		if (circleList[i].checkTouch(myPlayer)) {
			myPlayer.isGameOver = true;
			for (int j = 0; j < circleList.size(); j++)
				circleList[j].dy = 0;
		}
	}

}


int  CGameDmtrDoc::checkCreate() {
	if (circleList.size() != 0)
		for (int i = 0; i < circleList.size() - 1; i++) {
			if (circleList[i + 1].x + circleList[i + 1].r >= circleList[i].x - circleList[i].r && circleList[i + 1].x - circleList[i + 1].r <= circleList[i].x + circleList[i].r &&
				circleList[i + 1].y + circleList[i + 1].y >= circleList[i].y - circleList[i].y && circleList[i + 1].y - circleList[i + 1].r <= circleList[i].y + circleList[i].y)
				return 0;
		}
	return 1;
}

void CGameDmtrDoc::win(CRect* rect, CPlayer& player) {
	int countCircleDis = 0;
	for (int i = 0; i < circleList.size(); i++) {
		if (circleList[i].y - circleList[i].r > rect->Height())
			countCircleDis++;
	}
	if (countCircleDis == circleList.size())
		player.isGameWin = true;
		
}



// Создание или уничтожение CGameDmtrDoc

CGameDmtrDoc::CGameDmtrDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CGameDmtrDoc::~CGameDmtrDoc()
{
}

BOOL CGameDmtrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_pTreeView->FillTree();
	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CGameDmtrDoc

void CGameDmtrDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CGameDmtrDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CGameDmtrDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CGameDmtrDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CGameDmtrDoc

#ifdef _DEBUG
void CGameDmtrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameDmtrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CGameDmtrDoc




void CGameDmtrDoc::OnSettingColorBlack()
{
	// TODO: добавьте свой код обработчика команд
	for (int i = 0; i < circleList.size(); i++) {
		circleList[i].color = RGB(0, 0, 0);
	}
}


void CGameDmtrDoc::OnSettingColorBlue()
{
	// TODO: добавьте свой код обработчика команд
	for (int i = 0; i < circleList.size(); i++) {
		circleList[i].color = RGB(0, 0, 255);
	}
}


void CGameDmtrDoc::OnSettingColorGreen()
{
	// TODO: добавьте свой код обработчика команд
	for (int i = 0; i < circleList.size(); i++) {
		circleList[i].color = RGB(0, 255, 0);
	}
}


void CGameDmtrDoc::OnSettingColorRed()
{
	// TODO: добавьте свой код обработчика команд
	for (int i = 0; i < circleList.size(); i++) {
		circleList[i].color = RGB(255, 0, 0);
	}
}

void CGameDmtrDoc::OnSettingMyColor()
{
	if (!colorDlg)
		colorDlg.Create(IDD_DLG_COLOR, AfxGetMainWnd());

	/*colorDlg.pDoc = this;
	colorDlg.myColor.SetColor(circleList[0].color);*/
	//OnSettingsColor();

	colorDlg.ShowWindow(SW_SHOW);
}


//void CGameDmtrDoc::OnBnClickedMfccolorbutton1()
//{
//	// TODO: добавьте свой код обработчика уведомлений
//}
