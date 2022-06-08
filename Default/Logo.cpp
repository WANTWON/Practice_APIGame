#include "stdafx.h"
#include "Logo.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
}



int CLogo::Update()
{
	return OBJ_NOEVENT;
}

void CLogo::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}
}

void CLogo::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);
}


void CLogo::Release()
{
}