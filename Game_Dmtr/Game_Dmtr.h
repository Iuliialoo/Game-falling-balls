
// Game_Dmtr.h: основной файл заголовка для приложения Game_Dmtr
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CGameDmtrApp:
// Сведения о реализации этого класса: Game_Dmtr.cpp
//

class CGameDmtrApp : public CWinApp
{
public:
	CGameDmtrApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGameDmtrApp theApp;
