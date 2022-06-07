#include "stdafx.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Editor.h"

CStageMgr* CStageMgr::m_pInstance = nullptr;

CStageMgr::CStageMgr() : m_dwTime(GetTickCount()), m_eChoice_Stage(STAGE_END), m_bNewGame(false), m_iScore(0), m_iCoins(0)
{
	for (size_t i = 0; i != STAGE_END; ++i)
	{
		m_pStage[i] = nullptr;
	}
	m_Mouse = new CMouse;
}

CStageMgr::~CStageMgr()
{
	Release();
}

void CStageMgr::Initialize(void)
{
	int Temp = 0;
	for (size_t i = 0; i != STAGE_END; ++i)
	{
		m_tRect[i] = { 100 + Temp * 100 , 100, 150 + Temp * 100, 150 };
		++Temp;
	}

	m_Mouse->Initialize();
}

void CStageMgr::Update(void)
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
	{	
		if (m_bNewGame)
		{
			m_bNewGame = false;
		}
		m_Mouse->Update();
	}
}

void CStageMgr::Late_Update(void)
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
					m_pStage[STAGE_1]->Set_View();
					m_eChoice_Stage = STAGE_1;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_2:
					m_pStage[STAGE_2] = new CStage2;
					m_pStage[STAGE_2]->Initialize();
					m_pStage[STAGE_2]->Set_View();
					m_eChoice_Stage = STAGE_2;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_3:
					m_pStage[STAGE_3] = new CStage3;
					m_pStage[STAGE_3]->Initialize();
					m_pStage[STAGE_3]->Set_View();
					m_eChoice_Stage = STAGE_3;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_4:
					m_pStage[STAGE_4] = new CStage4;
					m_pStage[STAGE_4]->Initialize();
					m_pStage[STAGE_4]->Set_View();
					m_eChoice_Stage = STAGE_4;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_EDITOR:
					m_pStage[STAGE_EDITOR] = new CEditor;
					m_pStage[STAGE_EDITOR]->Initialize();
					m_eChoice_Stage = STAGE_EDITOR;
					break;
				default:
					break;
				}

			}
		}
	}
}

void CStageMgr::Render(HDC hDC)
{
	if (m_eChoice_Stage != STAGE_END)
	{
		//m_Mouse->Render(m_hDc);
		m_pStage[m_eChoice_Stage]->Render(hDC);
	}
	else if (m_eChoice_Stage == STAGE_END)
	{
		Rectangle(hDC, 0, 0, WINCX, WINCY);
		for (size_t i = 0; i< STAGE_END; ++i)
			Rectangle(hDC, m_tRect[i].left, m_tRect[i].top, m_tRect[i].right, m_tRect[i].bottom);

		m_Mouse->Render(hDC);
	}

	Render_Points_Total(hDC);
}

void CStageMgr::Render_Points_Total(HDC hDC)
{
	TCHAR sztScore[32] = L"";
	swprintf_s(sztScore, L"점수 : %d", m_iScore);
	TextOut(hDC, 30, 30, sztScore, lstrlen(sztScore));

	TCHAR sztCoins[32] = L"";
	swprintf_s(sztCoins, L"코인 : %d", m_iCoins);
	TextOut(hDC, 170, 30, sztCoins, lstrlen(sztCoins));
}

void CStageMgr::Release(void)
{
	Safe_Delete<CObj*>(m_Mouse);

	for (auto& iter : m_pStage)
		Safe_Delete<CStage*>(iter);
}