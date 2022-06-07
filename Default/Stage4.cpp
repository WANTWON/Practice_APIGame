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
	CObjMgr::Get_Instance()->Load_File(4);
	CBlockMgr::Get_Instance()->Load_File(4);
	CLineMgr::Get_Instance()->Load_File(4);
	CBlockMgr::Get_Instance()->Initialize();
}

int CStage4::Update(void)
{
	if (m_bClear)
		return STAGE_CLEAR;

	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();

	return STAGE_NOEVENT;
}

void CStage4::Late_Update(void)
{
	CUIMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();
}

void CStage4::Render(HDC hDc)
{
	Rectangle(hDc, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDc);
	CLineMgr::Get_Instance()->Render(hDc);
	CBlockMgr::Get_Instance()->Render(hDc);

}

void CStage4::Release(void)
{
	CObjMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
}