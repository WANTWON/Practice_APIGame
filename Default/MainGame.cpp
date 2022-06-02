#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"


CMainGame::CMainGame() : m_pPlayer(nullptr), eDir(DIR_END)
{

}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{

	m_HDC = GetDC(g_hWnd);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	
}


void CMainGame::Update(void)
{

	CObjMgr::Get_Instance()->Update();

}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}


void CMainGame::Release(void)
{
	
	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_HDC);
}


void CMainGame::Render(void)
{
	Rectangle(m_HDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(m_HDC);
}