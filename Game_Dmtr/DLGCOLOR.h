#pragma once
#include "afxdialogex.h"


// Диалоговое окно CDLGCOLOR

class CGameDmtrDoc;

class CDLGCOLOR : public CDialogEx
{
	DECLARE_DYNAMIC(CDLGCOLOR)

public:
	CDLGCOLOR(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CDLGCOLOR();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_COLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CMFCColorButton myColor;
	afx_msg void OnBnClickedMfccolorbutton1();
	CGameDmtrDoc* pDoc;
};
