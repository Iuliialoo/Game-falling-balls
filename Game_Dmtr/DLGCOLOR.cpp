// DLGCOLOR.cpp: файл реализации
//

#include "pch.h"
#include "Game_Dmtr.h"
#include "afxdialogex.h"
#include "DLGCOLOR.h"
#include "Game_DmtrDoc.h"


// Диалоговое окно CDLGCOLOR

IMPLEMENT_DYNAMIC(CDLGCOLOR, CDialogEx)

CDLGCOLOR::CDLGCOLOR(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_COLOR, pParent)
{

}

CDLGCOLOR::~CDLGCOLOR()
{
}

void CDLGCOLOR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, myColor);
}


BEGIN_MESSAGE_MAP(CDLGCOLOR, CDialogEx)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CDLGCOLOR::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// Обработчики сообщений CDLGCOLOR


void CDLGCOLOR::OnBnClickedMfccolorbutton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);

	pDoc->getColor(myColor.GetColor());
}
