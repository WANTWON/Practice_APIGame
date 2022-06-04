#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "StageMgr.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	
}

void CMainGame::Initialize(void)
{
	m_hDc = GetDC(g_hWnd);
	CStageMgr::Get_Instance()->Initialize();
}

void CMainGame::Update(void)
{
	CStageMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{

	CStageMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{

	Rectangle(m_hDc, 0, 0, WINCX, WINCY);

	CStageMgr::Get_Instance()->Render(m_hDc);


}

void CMainGame::Release(void)
{
	CStageMgr::Get_Instance()->Release();
	CStageMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDc);
}