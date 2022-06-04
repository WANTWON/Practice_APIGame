#pragma once
#include "Monster.h"
class CFlyingMonster :
	public CMonster
{
public:
	CFlyingMonster();
	virtual ~CFlyingMonster();

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

