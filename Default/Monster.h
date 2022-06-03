#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster() : m_bFalling(true), m_bGet_Attacked(false), m_bCount(false) {}
	virtual ~CMonster() {}

public:
	void Initialize(void) {}
	int Update(void) { return STAGE_NOEVENT; }
	void Late_Update(void) {}
	void Release(void) {}
	void Render(HDC hDC) {}

	virtual void Move(void) {}

public:
	void Be_Attacked(void) { m_bGet_Attacked = true; }


protected:
	bool m_bFalling;
	bool m_bGet_Attacked;
	bool m_bCount;
	DWORD m_dwTime;
};

