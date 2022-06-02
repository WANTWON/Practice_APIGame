#include "stdafx.h"
#include "MainGame.h"


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

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}
}


void CMainGame::Update(void)
{
	m_pPlayer->Update();
}


void CMainGame::Release(void)
{
	Safe_Delete<CObj*>(m_pPlayer);


	ReleaseDC(g_hWnd, m_HDC);
}


void CMainGame::Render(void)
{
	Rectangle(m_HDC, 0, 0, WINCX, WINCY);

	m_pPlayer->Render(m_HDC);
}