#include "stdafx.h"
#include "MyMenu.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	// 여기서 부터 하면 됨
}

void CMyMenu::Release()
{
}

int CMyMenu::Update()
{
	return 0;
}

void CMyMenu::Late_Update()
{
}

void CMyMenu::Render(HDC hDC)
{
}
