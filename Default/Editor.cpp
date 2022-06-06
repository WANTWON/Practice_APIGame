#include "stdafx.h"
#include "Editor.h"
#include "KeyMgr.h"
#include "ObjMgr.h"


RECT Temp = {};

CEditor::CEditor()
	:m_ObjMouse(nullptr)
{
	ZeroMemory(&m_ePt, sizeof(POINT));
}


CEditor::~CEditor()
{
	Release();
}

void CEditor::Initialize(void)
{
	m_ObjMouse = new CMouse;
	m_ObjMouse->Initialize();

	m_mapChoiceObj.emplace(1, CAbstractFactory<CPlayer>::Create(25.f, 75.f));
	//	Monster
	m_mapChoiceObj.emplace(2, CAbstractFactory<CMushroomMonster>::Create(m_ObjMouse->Get_Info().fX, m_ObjMouse->Get_Info().fY, DIR_END, OBJ_MONSTER));
	m_mapChoiceObj.emplace(3, CAbstractFactory<CTurtleMonster>::Create(75.f, 150.f));
	m_mapChoiceObj.emplace(4, CAbstractFactory<CTurtleBack>::Create(125.f, 150.f));
	//m_mapChoiceObj.emplace(5, CAbstractFactory<CJumpingMonster>::Create_with_Target(25.f, 200.f, m_mapChoiceObj.find(1));
	m_mapChoiceObj.emplace(6, CAbstractFactory<CFlyingMonster>::Create(75.f, 200.f));
	//m_mapChoiceObj.emplace(7, CAbstractFactory<CBossMonster>::Create_with_Target(125.f, 200.f, CObjMgr::Get_Instance()->Get_Player()));
	//	Block
	m_mapChoiceObj.emplace(8, CAbstractFactory<CNormalBlock>::Create(25.f, 275.f));
	m_mapChoiceObj.emplace(9, CAbstractFactory<CCoinBlock>::Create(75.f, 275.f));
	m_mapChoiceObj.emplace(10, CAbstractFactory<CItemBlock>::Create(125.f, 275.f));
	//	Item
	m_mapChoiceObj.emplace(11, CAbstractFactory<CCoin>::Create(25.f, 350.f));
	m_mapChoiceObj.emplace(12, CAbstractFactory<CMushroom>::Create(75.f, 350.f, ITEM_MUSHROOM));
	m_mapChoiceObj.emplace(13, CAbstractFactory<CStar>::Create(125.f, 350.f, ITEM_STAR));
	m_mapChoiceObj.emplace(14, CAbstractFactory<CFlower>::Create(25.f, 425.f, ITEM_FLOWER));



}

int CEditor::Update(void)
{
	GetCursorPos(&m_ePt);
	ScreenToClient(g_hWnd, &m_ePt);

	m_ObjMouse->Update();

	
	for (auto& iter : m_mapChoiceObj)
	{
		iter.second->Set_Pos(m_ObjMouse->Get_Info().fX, m_ObjMouse->Get_Info().fY);
		iter.second->Update_Rect();
	}

	CObjMgr::Get_Instance()->Update_rect();

	return 0;
}

void CEditor::Late_Update(void)
{
	m_ObjMouse->Late_Update();

	int iInput;
	scanf_s("%d", &iInput);

	
		if (CKeyMgr::Get_Instance()->Key_Up('2'))
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(m_ObjMouse->Get_Info().fX, m_ObjMouse->Get_Info().fY, DIR_END, OBJ_MONSTER));

		}

		
	
}

void CEditor::Release(void)
{
	Safe_Delete<CObj*>(m_ObjMouse);
	
	for (auto& iter : m_mapChoiceObj)
	{
		for_each(m_mapObj.begin(), m_mapObj.end(), CDeleteMap());
	}
}

void CEditor::Render(HDC hDC)
{
	
	TCHAR eiditor[100] = L"";
	swprintf_s(eiditor, L"1.플레이어\n2.머쉬룸");
	TextOut(hDC, 30, 30, eiditor, lstrlen(eiditor));



	/*for (auto& iter : m_mapChoiceObj)
	{
		iter.second->Render(hDC);
	}*/

	CObjMgr::Get_Instance()->Render(hDC);

	m_ObjMouse->Render(hDC);
}
