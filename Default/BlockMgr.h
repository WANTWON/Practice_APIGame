#pragma once
#include "Block.h"

class CBlockMgr
{
public:
	CBlockMgr();
	~CBlockMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	bool		CollisionBlock(RECT Player, float _fX, float * Change_fY); //X값은 값을 받기 위한 것. Y값은 좌표값 변경을 위해서
	void		Add_Object(OBJ_LIST _ID, CObj* pObj);
	int			Check_Rect(INFO Player, INFO pTarget, float* _pX, float* _pY);
	bool		Collision_with_Direction(CObj* _Sour);

public:
	static CBlockMgr* Get_Instance(void)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CBlockMgr;

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
	static CBlockMgr* m_pInstance;
	list<CObj*>		m_Blocklist;
};

