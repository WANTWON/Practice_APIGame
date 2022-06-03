#pragma once
#include "Define.h"
#include "Struct.h"
#include "Function.h"
#include "Enum.h"

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

	static CObjMgr* m_pInstance;

	list<CObj*> m_pObjList[OBJ_END];
	int m_iScore;

public:
	void Release();

	// 프레임마다 실행되는 함수 
	int Update();
	void Late_Update();
	void Render(HDC hDC);
	
	void Add_Object(OBJ_LIST _ID, CObj* pObj);

	// 게터와 세터
	static CObjMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	CObj* Get_Player() { return m_pObjList[OBJ_PLAYER].front(); }
	list<CObj*> Get_Monsters() { return m_pObjList[OBJ_MONSTER]; }
	list<CObj*> Get_Blocks() { return m_pObjList[OBJ_BLOCK]; }
	list<CObj*> Get_Items() { return m_pObjList[OBJ_ITEM]; }

	CObj* Get_Target(OBJ_LIST _ID, CObj* pObj);

	static void Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
};

