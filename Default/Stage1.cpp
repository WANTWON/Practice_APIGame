#include "stdafx.h"
#include "Stage1.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "StageMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "UIMgr.h"
#include "MushroomMonster.h"
#include "TurtleMonster.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Star.h"
#include "Flower.h"
#include "JumpingMonster.h"
#include "FlyingMonster.h"
#include "BossMonster.h"
#include "Item.h"
#include "Block.h"
#include "BlockMgr.h"
#include "NormalBlock.h"

CStage1::CStage1()
{

}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(m_iCount));
	
	// Test Monster
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(600, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(500, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CJumpingMonster>::Create_with_Target(300, 300, CObjMgr::Get_Instance()->Get_Player()));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMonster>::Create(100, 300));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBossMonster>::Create_with_Target(300, 300, CObjMgr::Get_Instance()->Get_Player()));

	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(550, 150));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(500, 150));

	// Test Coin
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(200, 300, ITEM_COIN));

	// Test Mushroom
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(200, 300, ITEM_MUSHROOM));

	// Test Star
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create(150, 450, ITEM_STAR));

	// Test Flower
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(200, 300, ITEM_FLOWER));

	CLineMgr::Get_Instance()->Initialize();
	CBlockMgr::Get_Instance()->Initialize();
	
	m_dwView = GetTickCount();
}

int CStage1::Update(void)
{
	if (m_bClear)
		return STAGE_CLEAR;

	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage1::Late_Update(void)
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

	CUIMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();
}

void CStage1::Render(HDC hDC)
{
	//Rectangle(hDC, 0, 0, WINCX, WINCY);
	
	CUIMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->Render(hDC);

	if (m_bView)
	{
		m_bView = false;
		m_dwView = GetTickCount();
		TCHAR szBuff[32] = L"";
		TCHAR szBuff1[32] = L"";
		Rectangle(hDC, 0, 0, WINCX, WINCY);
		Rectangle(hDC, 340, 250, 370, 280);
		while (m_dwView + 5000 > GetTickCount())
		{
			wsprintf(szBuff, L"WORLD  1-%d", 1);
			TextOut(hDC, 350, 200, szBuff, lstrlen(szBuff));
			swprintf_s(szBuff1, L"x       %d", dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Life());
			TextOut(hDC, 390, 260, szBuff1, lstrlen(szBuff1));
		}
	}
	else if (m_bClear)
	{
		m_dwView = GetTickCount();
		TCHAR szBuff[32] = L"";
		TCHAR szBuff1[32] = L"";
		Rectangle(hDC, 0, 0, WINCX, WINCY);
		while (m_dwView + 3000 > GetTickCount())
		{
			wsprintf(szBuff, L"GAME OVER", nullptr);
			TextOut(hDC, 350, 250, szBuff, lstrlen(szBuff));
		}
	}
}

void CStage1::Release(void)
{
	CUIMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
}