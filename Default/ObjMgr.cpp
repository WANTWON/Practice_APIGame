#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"

CObjMgr*		CObjMgr::m_pInstance = nullptr;

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

void CObjMgr::Add_Object(OBJ_LIST _ID, CObj* pObj)
{
	if (_ID == OBJ_END || nullptr == pObj)
		return;

	m_pObjList[_ID].push_back(pObj);

}

int CObjMgr::Update(void)
{
	int iEvent = 0;
	for (size_t i = 0; i != OBJ_END; ++i)
	{

		for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); )
		{
			iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
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

void CObjMgr::Late_Update(void)
{
	m_iScore = 0;

	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter : m_pObjList[i])
		{
			iter->Late_Update();
		}
	}

	CCollisionMgr::Collision_Rect(m_pObjList[OBJ_BULLET], m_pObjList[OBJ_MONSTER]);
	m_iScore += CCollisionMgr::Collision_Sphere(m_pObjList[OBJ_BULLET], m_pObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Wall_Player(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_WALL]);

	CCollisionMgr::Collision_Sphere(m_pObjList[OBJ_SHIELD], m_pObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Rect_Ex(m_pObjList[OBJ_MONSTER], m_pObjList[OBJ_PLAYER]);
}

void CObjMgr::Render(HDC hDC)
{

	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter : m_pObjList[i])
		{
			iter->Render(hDC);
		}
	}

	TCHAR  szBuff[32] = L"";
	swprintf_s(szBuff, L"몬스터 수 : %d", m_pObjList[OBJ_MONSTER].size());
	TextOut(hDC, 50, 30, szBuff, lstrlen(szBuff));

	TCHAR sztScore[32] = L"";
	swprintf_s(sztScore, L"점수 : %d", m_iScore);

	//Dc, 위치, 출력
	TextOut(hDC, 650, 30, sztScore, lstrlen(sztScore));
}

void CObjMgr::Release(void)
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
