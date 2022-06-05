#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Monster.h"
#include "AbstractFactory.h"

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

void CObjMgr::Save_File(void)
{
	HANDLE hFile = CreateFile(L"../Data/Save1/ObjPlayer.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save File", L"Error", MB_OK);
		return;
	}

	DWORD dwByte = 0;
	for (auto& iter : m_pObjList[OBJ_PLAYER])
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);

#ifdef _DEBUG
	MessageBox(g_hWnd, L"Save 성공", L"성공", MB_OK);
#endif	//_DEBUG
}

void CObjMgr::Load_File(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Save1/ObjPlayer.dat",
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

	DWORD	dwByte = 0;

	INFO	tTemp{};

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_pObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create(tTemp.fX, tTemp.fY));
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

	//CCollisionMgr::Step_on_Mushroom(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_MONSTER]);
	//CCollisionMgr::Collision_Item(Get_Player(), Get_Items());
	//CCollisionMgr::Collision_Rect(Get_Bullets(), Get_Monsters());
	//CCollisionMgr::Collision_Rect_Ex(m_pObjList[OBJ_MONSTER], m_pObjList[OBJ_PLAYER]);
	CCollisionMgr::Step_on_Mushroom(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_MONSTER]);
	//CCollisionMgr::Collision_Rect_Ex(Get_Monsters(), m_pObjList[OBJ_PLAYER]);
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
