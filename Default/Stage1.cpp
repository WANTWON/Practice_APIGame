#include "stdafx.h"
#include "Stage1.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"
#include "MushroomMonster.h"
#include "TurtleMonster.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Star.h"
#include "Flower.h"
#include "JumpingMonster.h"
#include "FlyingMonster.h"
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
	



	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(600, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(500, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CJumpingMonster>::Create_with_Target(300, 300, CObjMgr::Get_Instance()->Get_Player()));


	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMonster>::Create(100, 300));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(600, 200));

	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(550, 150));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(500, 150));


	// Test Coin
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(200, 300, ITEM_COIN));

	// Test Mushroom
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(200, 300, ITEM_MUSHROOM));

	// Test Star
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create(200, 300, ITEM_STAR));

	//Test Flower
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(200, 300, ITEM_FLOWER));

	CLineMgr::Get_Instance()->Initialize();
	CBlockMgr::Get_Instance()->Initialize();
	
	m_dwView = GetTickCount();
}

int CStage1::Update(void)
{
	if (m_bClear)
		return STAGE_CLEAR;

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
		
		

	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();

}

void CStage1::Render(HDC hDc)
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
		while (m_dwView + 5000 > GetTickCount())
		{
			wsprintf(szBuff, L"WORLD  1-%d", 1);
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

void CStage1::Release(void)
{

	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
}