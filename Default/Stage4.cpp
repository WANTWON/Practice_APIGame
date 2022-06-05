#include "stdafx.h"
#include "Stage4.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"

CStage4::CStage4()
{
}


CStage4::~CStage4()
{
}

void CStage4::Initialize(void)
{

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(600, 200));

	CLineMgr::Get_Instance()->Initialize(4);

}

int CStage4::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage4::Late_Update(void)
{


	CObjMgr::Get_Instance()->Late_Update();


}

void CStage4::Render(HDC hDc)
{
	//Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
}

void CStage4::Release(void)
{

	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
}