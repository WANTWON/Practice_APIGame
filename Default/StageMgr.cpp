#include "stdafx.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Editor.h"

CStageMgr* CStageMgr::m_pInstance = nullptr;

CStageMgr::CStageMgr() : m_dwTime(GetTickCount()), m_eChoice_Stage(STAGE_END), m_iScore(0), m_iCoins(0), m_iCount(3)
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
					m_pStage[STAGE_1]->Set_View(true);
					m_eChoice_Stage = STAGE_1;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_2:
					m_pStage[STAGE_2] = new CStage2;
					m_pStage[STAGE_2]->Initialize();
					m_pStage[STAGE_2]->Set_View(true);
					m_eChoice_Stage = STAGE_2;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_3:
					m_pStage[STAGE_3] = new CStage3;
					m_pStage[STAGE_3]->Initialize();
					m_pStage[STAGE_3]->Set_View(true);
					m_eChoice_Stage = STAGE_3;
					m_Mouse->Set_Pos(0.f, 0.f);
					break;
				case STAGE_4:
					m_pStage[STAGE_4] = new CStage4;
					m_pStage[STAGE_4]->Initialize();
					m_pStage[STAGE_4]->Set_View(true);
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
	Stage_View();
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
	View_End(hDC);
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





void CStageMgr::Stage_View(void)
{
	for (size_t i = 0; i != STAGE_END; ++i)
	{
		if (i == STAGE_EDITOR)
		{
			break;
		}
		else if (nullptr != m_pStage[i])
		{
			if (CObjMgr::Get_Instance()->Get_Player()->Get_Bye())
			{
				m_iCount -= 1;
				m_pStage[i]->Release();
				m_pStage[i]->Initialize();
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Life(m_iCount);
				CObjMgr::Get_Instance()->Get_Player()->Set_Bye();
				m_pStage[i]->Set_View(true);
			}
			else if (0 > dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Life())
			{
				m_pStage[i]->Set_Clear_true();
				m_pStage[i]->Set_View(false);
				CScrollMgr::Get_Instance()->Zero_Scroll();
			}
			else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Check())
			{
				m_pStage[i]->Set_Clear_true();
				m_pStage[i]->Set_View(false);
				CScrollMgr::Get_Instance()->Zero_Scroll();
			}
		}
	}
}

void CStageMgr::View_End(HDC hDC)
{
	for (size_t i = 0; i != STAGE_END; ++i)
	{
		if (nullptr != m_pStage[i])
		{
			if (m_pStage[i]->Get_View())
			{
				m_pStage[i]->Set_View(false);
				m_dwTime = GetTickCount();
				TCHAR szBuff[32] = L"";
				TCHAR szBuff1[32] = L"";
				Rectangle(hDC, 0, 0, WINCX, WINCY);
				Rectangle(hDC, 340, 250, 370, 280);
				while (m_dwTime + 3000 > GetTickCount())
				{
					wsprintf(szBuff, L"WORLD  1-%d", i+1);
					TextOut(hDC, 350, 200, szBuff, lstrlen(szBuff));
					swprintf_s(szBuff1, L"x       %d", dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Life());
					TextOut(hDC, 390, 260, szBuff1, lstrlen(szBuff1));
				}
				break;
			}
			else if (m_pStage[i]->Get_Clear() && (0 > dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Life()))
			{
				m_dwTime = GetTickCount();
				TCHAR szBuff[32] = L"";
				TCHAR szBuff1[32] = L"";
				Rectangle(hDC, 0, 0, WINCX, WINCY);
				while (m_dwTime + 3000 > GetTickCount())
				{
					wsprintf(szBuff, L"GAME OVER", nullptr);
					TextOut(hDC, 350, 250, szBuff, lstrlen(szBuff));
				}
				m_iCount = 3;
				break;
			}
			else if (m_pStage[i]->Get_Clear() && (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Check()))
			{
				m_dwTime = GetTickCount();
				TCHAR szBuff[32] = L"";
				TCHAR szBuff1[32] = L"";
				Rectangle(hDC, 0, 0, WINCX, WINCY);
				while (m_dwTime + 3000 > GetTickCount())
				{
					wsprintf(szBuff, L"GAME CLEAR", nullptr);
					TextOut(hDC, 350, 250, szBuff, lstrlen(szBuff));
				}
				
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Check(false);
				m_iCount = 3;
				break;
			}

		}
	}

}









void CStageMgr::Release(void)
{
	Safe_Delete<CObj*>(m_Mouse);

	for (auto& iter : m_pStage)
		Safe_Delete<CStage*>(iter);
}