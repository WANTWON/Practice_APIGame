#pragma once
#include "Monster.h"
class CJumpingMonster :
	public CMonster
{
public:
	CJumpingMonster();
	~CJumpingMonster();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);

	void Move(void);

	void Jumping(void);

private:
	float m_fTime;
	float m_fJumpPower;
	bool m_bJump;
	float fY;
};

