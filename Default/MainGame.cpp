#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "StageMgr.h"
#include "SceneMgr.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDc = GetDC(g_hWnd);


	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	//CStageMgr::Get_Instance()->Initialize();
}

void CMainGame::Update(void)
{
	//CStageMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
	//CStageMgr::Get_Instance()->Late_Update();
} 

void CMainGame::Render(void)
{
	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	CSceneMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDc, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	//CStageMgr::Get_Instance()->Render(m_hDc);
}

void CMainGame::Release(void)
{
	CStageMgr::Get_Instance()->Release();
	CStageMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDc);
}