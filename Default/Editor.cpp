#include "stdafx.h"
#include "Editor.h"


CEditor::CEditor()
	:m_ObjMouse(nullptr), m_iChoiceNumber(-1)
{
}


CEditor::~CEditor()
{
	Release();
}

void CEditor::Initialize(void)
{
	m_ObjMouse = new CMouse;
	m_ObjMouse->Initialize();

	for (size_t i = 0; i < 12; ++i)
	{
		for (size_t j = 0; j < 80; ++j)
		{
			m_mapObj.emplace(((i * 80) + j), CAbstractFactory<CBlockNull>::Create(
				200.f + 25.f + (50.f * j),
				25.f + (50.f * i)));
		}
	}

	m_mapChoiceObj.emplace(0, OBJ_PLAYER);
	//	Monster
	m_mapChoiceObj.emplace(1, OBJ_MONSTER);
	m_mapChoiceObj.emplace(2, OBJ_MONSTER);
	m_mapChoiceObj.emplace(3, OBJ_MONSTER);
	m_mapChoiceObj.emplace(4, OBJ_MONSTER);
	m_mapChoiceObj.emplace(5, OBJ_MONSTER);
	m_mapChoiceObj.emplace(6, OBJ_MONSTER);
	//	Block
	m_mapChoiceObj.emplace(7, OBJ_BLOCK);
	m_mapChoiceObj.emplace(8, OBJ_BLOCK);
	m_mapChoiceObj.emplace(9, OBJ_BLOCK);
	//	Item
	m_mapChoiceObj.emplace(10, OBJ_ITEM);
	m_mapChoiceObj.emplace(11, OBJ_ITEM);
	m_mapChoiceObj.emplace(12, OBJ_ITEM);
	m_mapChoiceObj.emplace(13, OBJ_ITEM);
}

int CEditor::Update(void)
{
	m_ObjMouse->Update();

	if (false == Choice_Class())
		Choice_Tile();

	for (auto& iter : m_mapObj)
	{
		iter.second->Update();
	}

	return 0;
}

void CEditor::Late_Update(void)
{
	m_ObjMouse->Late_Update();

	for (auto& iter : m_mapObj)
	{
		iter.second->Late_Update();
	}
}

void CEditor::Release(void)
{
	Safe_Delete<CObj*>(m_ObjMouse);
	for (auto& iter : m_mapObj)
	{
		for_each(m_mapObj.begin(), m_mapObj.end(), CDeleteMap());
	}
	for (auto& iter : m_mapChoiceObj)
	{
		for_each(m_mapObj.begin(), m_mapObj.end(), CDeleteMap());
	}
}

void CEditor::Render(HDC hDC)
{
	for (auto& iter : m_mapObj)
	{
		iter.second->Render(hDC);
	}

	m_ObjMouse->Render(hDC);
}

bool CEditor::Choice_Class(void)
{
	int i = 0;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		for (auto& iter : m_mapChoiceObj)
		{
			if (CCollisionMgr::Col_EditorClick(m_ObjMouse, iter.second));
			{
				m_iChoiceNumber = i;
				return true;
			}

			++i;
		}
	}

	m_iChoiceNumber = -1;
	return false;

}

bool CEditor::Choice_Tile(void)
{
	int i = 0;

	if (GetAsyncKeyState(VK_LBUTTON) || -1 != m_iChoiceNumber)
	{
		for (auto& iter : m_mapObj)
		{
			if (CCollisionMgr::Col_EditorClick(m_ObjMouse, iter.second));
			{
				switch (m_iChoiceNumber)
				{
				case 0:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 1:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 2:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 3:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 4:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 5:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 6:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 7:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 8:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 9:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 10:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 11:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 12:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				case 13:
					CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
					return true;
					break;
				default:
					break;
				}
			}

			++i;
		}
	}

	m_iChoiceNumber = -1;
	return false;
}
