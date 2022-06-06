#include "stdafx.h"
#include "Stage2.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"
#include "MushroomMonster.h"
#include "TurtleMonster.h"
#include "JumpingMonster.h"
#include "Item.h"
#include "Block.h"
#include "BlockMgr.h"
#include "NormalBlock.h"
#include "CoinBlock.h"
#include "Flower.h"

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
}

void CStage2::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(200, 300, ITEM_FLOWER));

	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(550, 150));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(500, 150));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(500, 100));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(500, 50));

	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(200, 350));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CCoinBlock>::Create(250, 350));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CCoinBlock>::Create(300, 350));

	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(350, 200));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(300, 250));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(250, 300));

	CLineMgr::Get_Instance()->Initialize(2);
	CBlockMgr::Get_Instance()->Initialize();

	CObjMgr::Get_Instance()->Load_File(2);
	CBlockMgr::Get_Instance()->Load_File(2);
	CLineMgr::Get_Instance()->Load_File(2);
	CBlockMgr::Get_Instance()->Initialize();
}

int CStage2::Update(void)
{
	if (m_bClear)
		return STAGE_CLEAR;

	CObjMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage2::Late_Update(void)
{


	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();


}

void CStage2::Render(HDC hDc)
{
	//Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
	CBlockMgr::Get_Instance()->Render(hDc);
}

void CStage2::Release(void)
{
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
}