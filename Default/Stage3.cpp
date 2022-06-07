#include "stdafx.h"
#include "Stage3.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"
#include "FlagBlock.h"
#include "NormalBlock.h"
#include "UIMgr.h"
#include "Flower.h"

CStage3::CStage3()
{
}


CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize(void)
{

	CLineMgr::Get_Instance()->Initialize(3);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(50.f, 460.f));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(600, 200));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_FLAG, CAbstractFactory<CFlagBlock>::Create(550, 445, false));
	CBlockMgr::Get_Instance()->Add_Object(BLOCK_FLAG, CAbstractFactory<CFlagBlock>::Create(535, 100, true));

	/*CObjMgr::Get_Instance()->Load_File(3);
	CBlockMgr::Get_Instance()->Load_File(3);
	CLineMgr::Get_Instance()->Load_File(3);*/
	CBlockMgr::Get_Instance()->Initialize();
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

void CStage3::Render(HDC hDc)
{
	Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
	CBlockMgr::Get_Instance()->Render(hDc);
}

void CStage3::Release(void)
{
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
}