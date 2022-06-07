#include "stdafx.h"
#include "Stage3.h"
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
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "CoinBlock.h"

CStage3::CStage3()
{
}


CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize(void)
{
	CObjMgr::Get_Instance()->Load_File(3);
	CLineMgr::Get_Instance()->Load_File(3);
	CBlockMgr::Get_Instance()->Load_File(3);
	CBlockMgr::Get_Instance()->Initialize();
	m_bClear = false;
}

int CStage3::Update(void)
{
	if (m_bClear)
		return STAGE_CLEAR;

	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage3::Late_Update(void)
{
	CUIMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();
}

void CStage3::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CUIMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->Render(hDC);
}

void CStage3::Release(void)
{
	CUIMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
}