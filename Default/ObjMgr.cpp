#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Monster.h"
#include "AbstractFactory.h"

#include "Item.h"
//	Monster
#include "MushroomMonster.h"
#include "TurtleMonster.h"
#include "TurtleBack.h"
#include "JumpingMonster.h"
#include "FlyingMonster.h"
#include "BossMonster.h"
//iTem
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Star.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{

}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJ_LIST _ID, CObj* pObj)
{
	return nullptr;
}

void CObjMgr::Set_EditorMode(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_pObjList[i])
		{
			iter->Set_EditorMode();
		}
	}
}

void CObjMgr::Set_PlayMode(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_pObjList[i])
		{
			iter->Set_PlayMode();
		}
	}
}

void CObjMgr::Add_Object(OBJ_LIST _ID, CObj* pObj)
{
	if (_ID == OBJ_END || nullptr == pObj)
		return;

	if (_ID == OBJ_BULLET)
	{
		OBJ_LIST Bullet_ID = pObj->Get_ID();
		pObj->Set_ID(Bullet_ID);
	}
	else
		pObj->Set_ID(_ID);

	m_pObjList[_ID].push_back(pObj);
}

int CObjMgr::Update()
{
	int iEvent = 0;
	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); )
		{
			iEvent = (*iter)->Update();

			if (iEvent == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_pObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}


	return iEvent;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter : m_pObjList[i])
			iter->Late_Update();
	}

	CObjMgr* ObjMgr = CObjMgr::Get_Instance();

	//CCollisionMgr::Collision_Rect(Get_Bullets(), Get_Monsters());
	//CCollisionMgr::Collision_Rect_Ex(m_pObjList[OBJ_MONSTER], m_pObjList[BLOCK_NORMAL]);
	CCollisionMgr::Step_on_Mushroom(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_MONSTER]);
	
	if (false == m_pObjList[OBJ_PLAYER].empty())
		CCollisionMgr::Collision_Item(Get_Player(), Get_Items());

	//m_iScore += CCollisionMgr::Collision_Rect(Get_Bullets(), Get_Monsters());
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter : m_pObjList[i])
			iter->Render(hDC);
	}

	for (auto& iter : m_pObjList[OBJ_MONSTER])
	{
		RECT rc = {};
		rc = iter->Get_Rect();
		int Number = dynamic_cast<CMonster*>(iter)->Get_Number();

		if (1 == Number)
		{
			Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
		}
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); )
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_pObjList[i].erase(iter);
		}
		m_pObjList[i].clear();
	}
}

void CObjMgr::Save_File(void)
{
	//	Player
	HANDLE hFile = CreateFile(L"../Data/SaveTemp/ObjPlayer.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save Player", L"Error", MB_OK);
		return;
	}

	DWORD	dwByte = 0;
	DWORD	dwTypeByte = 0;

	for (auto& iter : m_pObjList[OBJ_PLAYER])
	{
		SAVEOBJ  Temp = { iter->Get_Info(), iter->Get_Rect() , iter->Get_Dir(), iter->Get_Speed(),
			iter->Get_bDead(), iter->Get_Angle(), iter->Get_Target(), iter->Get_ID() };

		WriteFile(hFile, &(Temp), sizeof(SAVEOBJ), &dwByte, nullptr);
		WriteFile(hFile, &(static_cast<CPlayer*>(iter)->Get_PlayerType()), sizeof(int), &dwTypeByte, nullptr);
	}
	CloseHandle(hFile);



	//	Monster
	hFile = CreateFile(L"../Data/SaveTemp/ObjMonster.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save Monster", L"Error", MB_OK);
		return;
	}


	

	
	for (auto& iter : m_pObjList[OBJ_MONSTER])
	{
		SAVEOBJ  Temp = { iter->Get_Info(), iter->Get_Rect() , iter->Get_Dir(), iter->Get_Speed(), 
			iter->Get_bDead(), iter->Get_Angle(), iter->Get_Target(), iter->Get_ID() };

		WriteFile(hFile, &(Temp), sizeof(SAVEOBJ), &dwByte, nullptr);
		WriteFile(hFile, &(static_cast<CMonster*>(iter)->Get_MonsterType()), sizeof(int), &dwTypeByte, nullptr);
	}
	CloseHandle(hFile);



	//	Item
	hFile = CreateFile(L"../Data/SaveTemp/ObjItem.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save Item", L"Error", MB_OK);
		return;
	}

	for (auto& iter : m_pObjList[OBJ_ITEM])
	{
		SAVEOBJ  Temp = { iter->Get_Info(), iter->Get_Rect() , iter->Get_Dir(), iter->Get_Speed(),
			iter->Get_bDead(), iter->Get_Angle(), iter->Get_Target(), iter->Get_ID() };

		WriteFile(hFile, &(Temp), sizeof(SAVEOBJ), &dwByte, nullptr);
		WriteFile(hFile, &(static_cast<CItem*>(iter)->Get_Type()), sizeof(int), &dwTypeByte, nullptr);
	}
	CloseHandle(hFile);



#ifdef _DEBUG
	MessageBox(g_hWnd, L"Object Save 성공", L"성공", MB_OK);
#endif	//_DEBUG

	return;
}

void CObjMgr::Load_File(int _iStage)
{
	HANDLE	hFile = nullptr;
	DWORD	dwByte = 0;
	DWORD	dwTypeByte = 0;
	INFO	tTemp{};
	int		iTypeTemp = 0;

	switch (_iStage)
	{
	case 1:
		//	Player
		hFile = CreateFile(L"../Data/Save1/ObjPlayer.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Player", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iTypeTemp = 0;

		while (true)
		{
			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iTypeTemp)
			{
			case PLAYER_NORMAL:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(m_tInfo));
				break;

			default:
				break;
			}
		}
		CloseHandle(hFile);



		//	Monster
		hFile = CreateFile(L"../Data/Save1/ObjMonster.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Monster", L"Error", MB_OK);
			return;
		}
		while (true)
		{

			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;


			switch (iTypeTemp)
			{
			case MONSTER_MUSHROOM:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(m_tInfo));
				break;

			case MONSTER_TURTLE:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(m_tInfo));
				break;

			case MONSTER_TURTLEBACK:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleBack>::Create(m_tInfo));
				break;

			case MONSTER_JUMPING:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CJumpingMonster>::Create(m_tInfo));
				CObjMgr::Get_Instance()->Get_Monsters().back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				break;

			case MONSTER_FLYING:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMonster>::Create(m_tInfo));
				break;
			case MONSTER_BOSS:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBossMonster>::Create(m_tInfo));
				CObjMgr::Get_Instance()->Get_Monsters().back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				break;

			default:
				break;
			}
		}
		CloseHandle(hFile);

		//Item
		hFile = CreateFile(L"../Data/Save1/ObjItem.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Player", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iTypeTemp = 0;

		while (true)
		{
			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iTypeTemp)
			{
			case ITEM_COIN:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_COIN);
				break;
			case ITEM_MUSHROOM:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_MUSHROOM);
				break;
			case ITEM_STAR:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_STAR);
				break;
			case ITEM_FLOWER:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_FLOWER);
				break;
			default:
				break;
			}
		}
		CloseHandle(hFile);

		return;
	case 2:
		//	Player
		hFile = CreateFile(L"../Data/Save2/ObjPlayer.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Player", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iTypeTemp = 0;

		while (true)
		{
			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iTypeTemp)
			{
			case PLAYER_NORMAL:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(m_tInfo));
				break;

			default:
				break;
			}
		}
		CloseHandle(hFile);



		//	Monster
		hFile = CreateFile(L"../Data/Save2/ObjMonster.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Monster", L"Error", MB_OK);
			return;
		}
		while (true)
		{

			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;


			switch (iTypeTemp)
			{
			case MONSTER_MUSHROOM:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(m_tInfo));
				break;

			case MONSTER_TURTLE:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(m_tInfo));
				break;

			case MONSTER_TURTLEBACK:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleBack>::Create(m_tInfo));
				break;

			case MONSTER_JUMPING:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CJumpingMonster>::Create(m_tInfo));
				CObjMgr::Get_Instance()->Get_Monsters().back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				break;

			case MONSTER_FLYING:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMonster>::Create(m_tInfo));
				break;
			case MONSTER_BOSS:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBossMonster>::Create(m_tInfo));
				CObjMgr::Get_Instance()->Get_Monsters().back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				break;

			default:
				break;
			}
		}
		CloseHandle(hFile);

		//Item
		hFile = CreateFile(L"../Data/Save2/ObjItem.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Player", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iTypeTemp = 0;

		while (true)
		{
			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iTypeTemp)
			{
			case ITEM_COIN:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_COIN);
				break;
			case ITEM_MUSHROOM:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_MUSHROOM);
				break;
			case ITEM_STAR:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_STAR);
				break;
			case ITEM_FLOWER:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_FLOWER);
				break;
			default:
				break;
			}
		}
		CloseHandle(hFile);

		return;
	case 3:
		//	Player
		hFile = CreateFile(L"../Data/Save3/ObjPlayer.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Player", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iTypeTemp = 0;

		while (true)
		{
			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iTypeTemp)
			{
			case PLAYER_NORMAL:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(m_tInfo));
				break;

			default:
				break;
			}
		}
		CloseHandle(hFile);



		//	Monster
		hFile = CreateFile(L"../Data/Save3/ObjMonster.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Monster", L"Error", MB_OK);
			return;
		}
		while (true)
		{

			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;


			switch (iTypeTemp)
			{
			case MONSTER_MUSHROOM:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(m_tInfo));
				break;

			case MONSTER_TURTLE:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(m_tInfo));
				break;

			case MONSTER_TURTLEBACK:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleBack>::Create(m_tInfo));
				break;

			case MONSTER_JUMPING:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CJumpingMonster>::Create(m_tInfo));
				CObjMgr::Get_Instance()->Get_Monsters().back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				break;

			case MONSTER_FLYING:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMonster>::Create(m_tInfo));
				break;
			case MONSTER_BOSS:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBossMonster>::Create(m_tInfo));
				CObjMgr::Get_Instance()->Get_Monsters().back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				break;

			default:
				break;
			}
		}
		CloseHandle(hFile);

		//Item
		hFile = CreateFile(L"../Data/Save3/ObjItem.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Player", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iTypeTemp = 0;

		while (true)
		{
			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iTypeTemp)
			{
			case ITEM_COIN:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_COIN);
				break;
			case ITEM_MUSHROOM:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_MUSHROOM);
				break;
			case ITEM_STAR:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_STAR);
				break;
			case ITEM_FLOWER:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_FLOWER);
				break;
			default:
				break;
			}
		}
		CloseHandle(hFile);

		return;
	case 4:
		//	Player
		hFile = CreateFile(L"../Data/Save4/ObjPlayer.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Player", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iTypeTemp = 0;

		while (true)
		{
			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iTypeTemp)
			{
			case PLAYER_NORMAL:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(m_tInfo));
				break;

			default:
				break;
			}
		}
		CloseHandle(hFile);



		//	Monster
		hFile = CreateFile(L"../Data/Save4/ObjMonster.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Monster", L"Error", MB_OK);
			return;
		}
		while (true)
		{

			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;


			switch (iTypeTemp)
			{
			case MONSTER_MUSHROOM:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(m_tInfo));
				break;

			case MONSTER_TURTLE:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(m_tInfo));
				break;

			case MONSTER_TURTLEBACK:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleBack>::Create(m_tInfo));
				break;

			case MONSTER_JUMPING:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CJumpingMonster>::Create(m_tInfo));
				CObjMgr::Get_Instance()->Get_Monsters().back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				break;

			case MONSTER_FLYING:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMonster>::Create(m_tInfo));
				break;
			case MONSTER_BOSS:
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBossMonster>::Create(m_tInfo));
				CObjMgr::Get_Instance()->Get_Monsters().back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				break;

			default:
				break;
			}
		}
		CloseHandle(hFile);

		//Item
		hFile = CreateFile(L"../Data/Save4/ObjItem.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Player", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iTypeTemp = 0;

		while (true)
		{
			SAVEOBJ m_tInfo;

			ReadFile(hFile, &m_tInfo, sizeof(SAVEOBJ), &dwByte, nullptr);
			ReadFile(hFile, &iTypeTemp, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iTypeTemp)
			{
			case ITEM_COIN:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_COIN);
				break;
			case ITEM_MUSHROOM:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_MUSHROOM);
				break;
			case ITEM_STAR:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_STAR);
				break;
			case ITEM_FLOWER:
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(m_tInfo));
				dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Items().back())->Set_Type(ITEM_FLOWER);
				break;
			default:
				break;
			}
		}
		CloseHandle(hFile);

		return;
	}
}