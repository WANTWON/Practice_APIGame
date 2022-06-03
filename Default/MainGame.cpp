#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"



CMainGame::CMainGame() : m_dwTime(GetTickCount()), m_eChoice_Stage(STAGE_END), m_bNewGame(false)
{
	for (size_t i = 0; i != STAGE_END; ++i)
	{
		m_pStage[i] = nullptr;
	}
	m_Mouse = new CMouse;
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDc = GetDC(g_hWnd);
	int Temp = 0;
	for (size_t i = 0; i != STAGE_END; ++i)
	{
		m_tRect[i] = { 100 + Temp * 100 , 100, 150 + Temp * 100, 150 };
		++Temp;
	}

	m_Mouse->Initialize();
}

void CMainGame::Update(void)
{
	int iEvent = 0;

	if (m_eChoice_Stage != STAGE_END)
	{
		m_Mouse->Update();
		iEvent = m_pStage[m_eChoice_Stage]->Update();
		if (iEvent == STAGE_CLEAR)
		{
			Safe_Delete<CStage*>(m_pStage[m_eChoice_Stage]);
			Set_Stage(STAGE_END);
		}
	}
	else if (m_eChoice_Stage == STAGE_END)
		m_Mouse->Update();
}

void CMainGame::Late_Update(void)
{

	if (m_eChoice_Stage != STAGE_END)
	{
		m_Mouse->Late_Update();
		m_pStage[m_eChoice_Stage]->Late_Update();
	}
	else if (m_eChoice_Stage == STAGE_END)
	{
		m_Mouse->Late_Update();

		RECT rc_Temp = { 0,0,0,0 };

		for (size_t i = 0; i < STAGE_END; ++i)
		{
			if (IntersectRect(&rc_Temp, &m_Mouse->Get_Rect(), &m_tRect[i]))
			{
				switch (i)
				{
				case STAGE_1:
					m_pStage[STAGE_1] = new CStage1;
					m_pStage[STAGE_1]->Initialize();
					m_eChoice_Stage = STAGE_1;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_2:
					m_pStage[STAGE_2] = new CStage2;
					m_pStage[STAGE_2]->Initialize();
					m_eChoice_Stage = STAGE_2;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_3:
					m_pStage[STAGE_3] = new CStage3;
					m_pStage[STAGE_3]->Initialize();
					m_eChoice_Stage = STAGE_3;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_4:
					m_pStage[STAGE_4] = new CStage4;
					m_pStage[STAGE_4]->Initialize();
					m_eChoice_Stage = STAGE_4;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				default:
					break;
				}

			}
		}

	}
}

void CMainGame::Render(void)
{

	Rectangle(m_hDc, 0, 0, WINCX, WINCY);

	if (m_eChoice_Stage != STAGE_END)
	{
		//m_Mouse->Render(m_hDc);
		m_pStage[m_eChoice_Stage]->Render(m_hDc);
	}
	else if (m_eChoice_Stage == STAGE_END)
	{
		for (size_t i = 0; i< STAGE_END; ++i)
			Rectangle(m_hDc, m_tRect[i].left, m_tRect[i].top, m_tRect[i].right, m_tRect[i].bottom);
		m_Mouse->Render(m_hDc);
	}


}

void CMainGame::Release(void)
{

	Safe_Delete<CObj*>(m_Mouse);

	for (auto& iter : m_pStage)
		Safe_Delete<CStage*>(iter);

	ReleaseDC(g_hWnd, m_hDc);

}