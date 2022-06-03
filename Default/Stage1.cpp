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

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Initialize(void)
{

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(600, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(500, 200));

	// Test Coin
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(200, 300, ITEM_COIN));

	// Test Mushroom
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(200, 300, ITEM_MUSHROOM));

	CLineMgr::Get_Instance()->Initialize();

}

int CStage1::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage1::Late_Update(void)
{


	CObjMgr::Get_Instance()->Late_Update();


}

void CStage1::Render(HDC hDc)
{
	//Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
}

void CStage1::Release(void)
{

	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
}