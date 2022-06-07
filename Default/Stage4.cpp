#include "stdafx.h"
#include "Stage4.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include <time.h>
#include "ObjMgr.h"
#include "LineMgr.h"
#include "UIMgr.h"

CStage4::CStage4()
{

}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize(void)
{
	CObjMgr::Get_Instance()->Load_File(4);
	CLineMgr::Get_Instance()->Load_File(4);
	CBlockMgr::Get_Instance()->Load_File(4);

	CBlockMgr::Get_Instance()->Initialize();

	m_dwView = GetTickCount();
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
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Bye())
	{
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Life(-1);
		Release();
		Initialize();
		CObjMgr::Get_Instance()->Get_Player()->Set_Bye();
		m_bView = true;
	}

	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Life() < 0)
	{
		m_bClear = true;
		m_bView = false;
	}

	CUIMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();
}

void CStage4::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	CUIMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->Render(hDC);

	if (m_bView)
	{
		m_bView = false;
		m_dwView = GetTickCount();
		TCHAR szBuff[32] = L"";
		TCHAR szBuff1[32] = L"";

		Rectangle(hDC, 0, 0, WINCX, WINCY);
		Rectangle(hDC, 340, 250, 370, 280);

		while (m_dwView + 2000 > GetTickCount())
		{
			wsprintf(szBuff, L"WORLD  1-%d", 1);
			TextOut(hDC, 350, 200, szBuff, lstrlen(szBuff));
			swprintf_s(szBuff1, L"x       %d", dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Life());
			TextOut(hDC, 390, 260, szBuff1, lstrlen(szBuff1));
		}
	}
	else if (m_bClear)
	{
		m_dwView = GetTickCount();
		TCHAR szBuff[32] = L"";
		TCHAR szBuff1[32] = L"";
		Rectangle(hDC, 0, 0, WINCX, WINCY);
		while (m_dwView + 3000 > GetTickCount())
		{
			wsprintf(szBuff, L"GAME OVER", nullptr);
			TextOut(hDC, 350, 250, szBuff, lstrlen(szBuff));
		}
	}
}

void CStage4::Release(void)
{
	CUIMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
}