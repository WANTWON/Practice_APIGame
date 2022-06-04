#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster() : m_bFalling(true), m_bGet_Attacked(false), m_bCount(false), iAttack_Count(0), m_iMonsterNumder(0) {}
	virtual ~CMonster() {}

public:
	void Initialize(void) {}
	int Update(void) { return STAGE_NOEVENT; }
	void Late_Update(void) {}
	void Release(void) {}
	void Render(HDC hDC) {}

	virtual void Move(void) {}

public:
	void Be_Attacked(void) { m_bGet_Attacked = true; iAttack_Count++; }
	int Get_Number(void) { return m_iMonsterNumder; }

protected:
	bool m_bFalling;
	bool m_bGet_Attacked;
	int  iAttack_Count;
	bool m_bCount;
	DWORD m_dwTime;
	int m_iMonsterNumder;
};

