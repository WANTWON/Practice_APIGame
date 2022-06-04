#pragma once
#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Render(HDC hDC);
	void		Release(void);
	bool		CollisionLine(float _fX, float* _fY); //X값은 값을 받기 위한 것. Y값은 좌표값 변경을 위해서
	bool		CollisionLine_Bullet(float _fX, float _fY, float * _OutY, CLine* _OutLine);

public:
	static CLineMgr* Get_Instance(void)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CLineMgr;

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
	static CLineMgr* m_pInstance;
	list<CLine*>		m_Linelist;
};

