#pragma once
#include "Line.h"
#include "Obj.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Render(HDC hDC);
	void		Release(void);

	bool		CollisionLine(CObj* _pObj, float* _fY); //X��� ��� �ޱ� ��� ��. Y��� ��ǥ�� ����� ��ؼ�
	CLine*		CollisionLine_Bullet(float _fX, float * _OutY);

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