#include "stdafx.h"
#include "Stage2.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
}

void CStage2::Initialize(void)
{

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());


	CLineMgr::Get_Instance()->Initialize();

}

int CStage2::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage2::Late_Update(void)
{


	CObjMgr::Get_Instance()->Late_Update();


}

void CStage2::Render(HDC hDc)
{
	//Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
}

void CStage2::Release(void)
{

	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
}