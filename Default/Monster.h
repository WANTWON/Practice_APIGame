#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	CMonster() : m_bFalling(true), m_bGet_Attacked(false), m_bCount(false), m_iHp(0), m_iMonsterNumber(0) { m_iPoints_Given = 100; }
	virtual ~CMonster() {}

public:
	void Initialize(void) {}
	int Update(void) { return STAGE_NOEVENT; }
	void Late_Update(void) {}
	void Release(void) {}
	void Render(HDC hDC) {}

	virtual void Move(void) {}

public:
	void Be_Attacked(void) { --m_iHp;  if (m_iHp <= 0)m_bGet_Attacked = true; }
	int Get_Number(void) { return m_iMonsterNumder; }
	int Get_Hp(void){ return m_iHp; }
	const MONSTER_LIST& Get_MonsterType(void) const { return m_iType; }



protected:
	bool m_bFalling;
	bool m_bGet_Attacked;
	int m_iHp;
	bool m_bCount;
	DWORD m_dwTime;
	int m_iMonsterNumber;

	MONSTER_LIST m_iType;
};

