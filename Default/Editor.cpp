#include "stdafx.h"
#include "Editor.h"
#include "ScrollMgr.h"

/*
/////////////////////////////////////
////////////   READ ME   ////////////
/////////////////////////////////////

Editor version 0.01
How to Use Editor
First
	Left top 1 Block = Player
	You can Only One Chance ( If you want to delete Player or Move Player Position, Close and Open File )
	if you set Boss or Chasing Monster, It would be Error and close. ( Player = nullptr )


Warning.
	Choice class( Object ) by Left Click
	if you want to set other class, you can change your mouse to NULL by Right Click

	if you wrong set Object, Plz close and open file. ( DEBUGING . . . )

	if you Save and load file, you can Overlap Object. so that don't set Object if there have object.



Save & Load
	In EditorMode, Save by 'S' on keyboard
	File save on "../Data/SaveTemp/Obj~~.dat"
	you must move that file on your Stage.
	1 stage : Hyeyeon
	2 stage : Seongjun
	3 stage : Taekyung
	4 stage : Gioi



Choice Class ( Left top )
from the Top,
Player 1 ps

Monster 6 ps / Monster Order by right Folder( 01. Monster )
//	1	2	3
//	4	5	6
1. Mushroom
2. Turtle
3. TurtleBack
4. Jumping
5. Flying
6. Boss

Block 3 ps
//	1	2	3
1. Normal
2. Coin
3. Item

Item 4 ps
//	1	2	3
//	4
1. Coin	- Don't Use. It would be delete soon.
2. Mushroom
3. Star
4. Flower


*/
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
	static_cast<CMouse*>(m_ObjMouse)->Set_Radius(5.f, 5.f);

	for (size_t i = 0; i < 12; ++i)
	{
		for (size_t j = 0; j < 80; ++j)
		{
			m_mapObj.emplace(((i * 80) + j), CAbstractFactory<CBlockNull>::Create(
				200.f + 25.f + (50.f * j),
				25.f + (50.f * i)));
		}
	}

	//	Player 1
	for (size_t i = 0; i < 1; ++i)
	{
		m_mapChoiceObj.emplace(i, CAbstractFactory<CBlockNull>::Create(
			25.f + (50.f * i),
			25.f + (50.f * i)));
	}
	//	Monster 6
	for (size_t i = 0; i < int(MONSTER_END); ++i)
	{
		m_mapChoiceObj.emplace(i + 1, CAbstractFactory<CBlockNull>::Create(
			25.f + (50.f * float(i % 3)),
			125.f + (50.f * float(i / 3))));
	}
	//	Block 3  /  except Flag
	for (size_t i = 0; i < BLOCK_END - 1; ++i)
	{
		m_mapChoiceObj.emplace(i + 7, CAbstractFactory<CBlockNull>::Create(
			25.f + (50.f * float(i % 3)),
			275.f + (50.f * float(i / 3))));
	}
	//	Item 4
	for (size_t i = 0; i < ITEM_END; ++i)
	{
		m_mapChoiceObj.emplace(i + 11, CAbstractFactory<CBlockNull>::Create(
			25.f + (50.f * float(i % 3)),
			425.f + (50.f * float(i / 3))));
	}

	//	Line 1
	for (size_t i = 0; i < 1; ++i)
	{
		m_mapChoiceObj.emplace(i + 15, CAbstractFactory<CBlockNull>::Create(
			25.f + (50.f * i),
			75.f + (50.f * i)));
	}
}

int CEditor::Update(void)
{

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);


	m_ObjMouse->Update();

	if (false == Choice_Class())
		Choice_Tile();

	for (auto& iter : m_mapObj)
	{
		iter.second->Update();
	}
	for (auto& iter : m_mapChoiceObj)
	{
		iter.second->Update();
	}
	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();


	Save_File();
	CObjMgr::Get_Instance()->Set_EditorMode();
	return 0;
}

void CEditor::Late_Update(void)
{
	m_ObjMouse->Late_Update();

	for (auto& iter : m_mapObj)
	{
		iter.second->Late_Update();
	}
	for (auto& iter : m_mapChoiceObj)
	{
		iter.second->Late_Update();
	}
	CUIMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();
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
		for_each(m_mapChoiceObj.begin(), m_mapChoiceObj.end(), CDeleteMap());
	}
	CUIMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CBlockMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Release();
}

void CEditor::Render(HDC hDC)
{
	
	
	Rectangle(hDC, 0, 0, 200, WINCY);


	for (auto& iter : m_mapChoiceObj)
	{
		iter.second->Render(hDC);

	}
	for (auto& iter : m_mapObj)
	{
		iter.second->Render(hDC);
	}
	CUIMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);


	m_ObjMouse->Render(hDC);
}

bool CEditor::Choice_Class(void)
{
	int i = 0;

	if (GetAsyncKeyState(VK_LBUTTON) && -1 == m_iChoiceNumber)
	{
		for (auto& iter : m_mapChoiceObj)
		{
			if (true == CCollisionMgr::Col_EditorClick(m_ObjMouse, iter.second))
			{
				m_iChoiceNumber = i;
				return true;
			}
			else
			{
				++i;
				m_iChoiceNumber = -1;
			}
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON))
		m_iChoiceNumber = -1;

	return false;

}

void CEditor::Choice_Tile(void)
{
	int i = 0;
	CObj* ObjTemp = nullptr;
	CLine*	LineTemp = nullptr;

	if (GetAsyncKeyState(VK_LBUTTON) && -1 != m_iChoiceNumber)
	{
		for (auto& iter : m_mapObj)
		{
			if (CCollisionMgr::Col_EditorClick(m_ObjMouse, iter.second))
			{
				switch (m_iChoiceNumber)
				{
				case 0:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check()
						&& (true == CObjMgr::Get_Instance()->Get_listPlayer().empty()))
					{
						ObjTemp = CAbstractFactory<CPlayer>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 1:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CMushroomMonster>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 2:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CTurtleBack>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 3:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CTurtleMonster>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 4:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CJumpingMonster>::Create_with_Target(iter.second->Get_Info().fX, iter.second->Get_Info().fY, CObjMgr::Get_Instance()->Get_Player());
						CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 5:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CFlyingMonster>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 6:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CBossMonster>::Create_with_Target(iter.second->Get_Info().fX, iter.second->Get_Info().fY, CObjMgr::Get_Instance()->Get_Player());
						CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 7:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CNormalBlock>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CBlockMgr::Get_Instance()->Add_Object(BLOCK_NORMAL, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 8:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CCoinBlock>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CBlockMgr::Get_Instance()->Add_Object(BLOCK_COIN, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 9:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CItemBlock>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CBlockMgr::Get_Instance()->Add_Object(BLOCK_ITEM, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 10:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CCoin>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 11:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CMushroom>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 12:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CStar>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 13:
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						ObjTemp = CAbstractFactory<CFlower>::Create(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, ObjTemp);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				case 14:	//Line
					if (false == static_cast<CBlockNull*>(iter.second)->Get_Check())
					{
						CLineMgr::Get_Instance()->Add_Line(iter.second->Get_Info().fX, iter.second->Get_Info().fY);
						static_cast<CBlockNull*>(iter.second)->Set_Check(true);
						return;
					}
					break;
				default:
					break;
				}
			}

			++i;
		}
	}

	return;
}

void CEditor::Save_File(void)
{
	if (GetAsyncKeyState('S'))
	{
		CObjMgr::Get_Instance()->Save_File();
		CBlockMgr::Get_Instance()->Save_File();
		CLineMgr::Get_Instance()->Save_File();
	}
}

