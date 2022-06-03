#include "stdafx.h"
#include "Stage3.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"

CStage3::CStage3()
{
}


CStage3::~CStage3()
{
}

void CStage3::Initialize(void)
{

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(600, 200));

	CLineMgr::Get_Instance()->Initialize();

}

int CStage3::Update(void)
{
	if (m_bClear)
		return STAGE_CLEAR;


	CObjMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage3::Late_Update(void)
{
	if (m_dwTime + 3000 < GetTickCount())
		m_bClear = true;

	CObjMgr::Get_Instance()->Late_Update();


}

void CStage3::Render(HDC hDc)
{
	//Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
}

void CStage3::Release(void)
{

	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
}