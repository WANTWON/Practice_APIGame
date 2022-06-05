#include "stdafx.h"
#include "Stage3.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"
#include "FlagBlock.h"
#include "NormalBlock.h"

CStage3::CStage3()
{
}


CStage3::~CStage3()
{
}

void CStage3::Initialize(void)
{
	CBlockMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize(3);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(50.f, 460.f,m_iCount));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(600, 200));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_FLAG, CAbstractFactory<CFlagBlock>::Create(550, 445, false));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_FLAG, CAbstractFactory<CFlagBlock>::Create(535, 100, true));

	m_dwView = GetTickCount();
} 

int CStage3::Update(void)
{
	if (m_bClear)
		return STAGE_CLEAR;

	CObjMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage3::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Bye())
	{
		m_iCount -= 1;
		Release();
		Initialize();
		CObjMgr::Get_Instance()->Get_Player()->Set_Bye();
		m_bView = true;

		if (m_iCount == -1)
		{
			m_bClear = true;
			m_bView = false;
		}
	}

	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();
}

void CStage3::Render(HDC hDc)
{
	//Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
	CBlockMgr::Get_Instance()->Render(hDc);

	if (m_bView)
	{
		m_bView = false;
		m_dwView = GetTickCount();
		TCHAR szBuff[32] = L"";
		TCHAR szBuff1[32] = L"";
		Rectangle(hDc, 0, 0, WINCX, WINCY);
		Rectangle(hDc, 340, 250, 370, 280);
		while (m_dwView + 3000 > GetTickCount())
		{
			wsprintf(szBuff, L"WORLD  1-%d", 3);
			TextOut(hDc, 350, 200, szBuff, lstrlen(szBuff));
			swprintf_s(szBuff1, L"x       %d", dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Life());
			TextOut(hDc, 390, 260, szBuff1, lstrlen(szBuff1));
		}
	}
	else if (m_bClear)
	{
		m_dwView = GetTickCount();
		TCHAR szBuff[32] = L"";
		TCHAR szBuff1[32] = L"";
		Rectangle(hDc, 0, 0, WINCX, WINCY);
		while (m_dwView + 3000 > GetTickCount())
		{
			wsprintf(szBuff, L"GAME OVER", nullptr);
			TextOut(hDc, 350, 250, szBuff, lstrlen(szBuff));
		}
	}
}

void CStage3::Release(void)
{
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
}