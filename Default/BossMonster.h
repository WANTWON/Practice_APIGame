#pragma once
#include "Monster.h"
class CBossMonster :
	public CMonster
{
public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);

	void Move(void);
	void Set_bMove(void) { if (m_bMove == true) m_bMove = false; else m_bMove = true; }
	void Make_Bullet(void);
	void Set_TargetAngle(void);

	void Attack_Pattern(void);

private:
	float fY;
	DWORD m_dwMoveTime;
	DWORD m_dwCreateBulletTime;

	bool m_bMove;


	BOSS_STATE m_eState;

	float m_fTargetPosX;
	float m_fTargetPosY;
	float m_fDistance;
};

