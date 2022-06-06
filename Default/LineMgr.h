#pragma once
#include "Line.h"
#include "Obj.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Add_Line(float _fX, float _fY);
	void		Edit_NULL(float _fX, float _fY);
	void		Initialize(int _Number);
	void		Render(HDC hDC);
	void		Release(void);

	//bool		CollisionLine(CObj* _pObj, float* _fY); 
	bool        CollisionLine(float	_fX, float _fY, float* _fYOut);
	CLine*		CollisionLine_Bullet(float _fX, float * _OutY);

	//bool		CollisionLine(float _fX, float* _fY);
	bool		CollisionFlag(RECT rc, float* _fY);

	void		Save_File(void);
	void		Load_File(int _iStage);

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
	list<CLine*>		m_Flagline;

	LINEPOINT					m_tLinePoint[END];
};


