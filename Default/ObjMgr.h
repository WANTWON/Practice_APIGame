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

public:
	CObj* Get_Player(void) { return m_pObjList[OBJ_PLAYER].front(); }
	CObj* Get_Target(OBJ_LIST _ID, CObj* pObj);

public:
	void Add_Object(OBJ_LIST _ID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	static CObjMgr* Get_Instance(void)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	list<CObj*> m_pObjList[OBJ_END];
	int m_iScore;
	static		CObjMgr*		m_pInstance;
};

