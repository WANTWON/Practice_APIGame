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
}

void CStage1::Initialize(void)
{

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());


	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMonster>::Create(100, 300));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(600, 200));

	/*CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(600, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(500, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CJumpingMonster>::Create_with_Target(300, 300, CObjMgr::Get_Instance()->Get_Player()));*/

	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(550, 150));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, CAbstractFactory<CNormalBlock>::Create(500, 150));


	// Test Coin
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(200, 300, ITEM_COIN));

	// Test Mushroom
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(200, 300, ITEM_MUSHROOM));

	// Test Star
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create(200, 300, ITEM_STAR));

	// Test Flower
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(200, 300, ITEM_FLOWER));

	CLineMgr::Get_Instance()->Initialize();
	CBlockMgr::Get_Instance()->Initialize();
	

}

int CStage1::Update(void)
{
		
	CObjMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage1::Late_Update(void)
{


	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();

}

void CStage1::Render(HDC hDc)
{
	//Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
	CBlockMgr::Get_Instance()->Render(hDc);
}

void CStage1::Release(void)
{

	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
}