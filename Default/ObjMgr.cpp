#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Monster.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr() : m_iScore(0)
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

void CObjMgr::Add_Object(OBJ_LIST _ID, CObj* pObj)
{
	if (_ID == OBJ_END || nullptr == pObj)
		return;

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
	
	CCollisionMgr::Step_on_Mushroom(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_MONSTER]);
	//CCollisionMgr::Collision_Rect_Ex(Get_Monsters(), m_pObjList[OBJ_PLAYER]);
	CCollisionMgr::Collision_Item(Get_Player(), Get_Items());
	CCollisionMgr::Collision_Rect_Ex(m_pObjList[OBJ_MONSTER], m_pObjList[OBJ_PLAYER]);
	CCollisionMgr::Collision_Rect(Get_Bullets(), Get_Monsters());
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


	TCHAR sztScore[32] = L"";
	swprintf_s(sztScore, L"ÄÚ?Î : %d", m_iScore);
	TextOut(hDC, 650, 30, sztScore, lstrlen(sztScore));

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
