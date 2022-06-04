#pragma once
#include "Obj.h"


class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual~CPlayer();
public:
	void Initialize(void)  override;
	int Update(void) override;
	void Late_Update(void) override;
	void Release(void) override;
	void Render(HDC hDC) override;
	void Set_bJump(bool temp) { m_bJump = temp; }
	void Set_StepMonster(bool temp) { m_bStep_Monster = temp; }

	bool Get_bJump(void) { return m_bJump; }
	void Set_JumpingTime(void) { Jumping_Time = GetTickCount(); }

private:
	void Key_Input(void);
	void Jumping(void);
	void Steping(void);

private:
	float m_pShield_Angle;
	float m_fTime;
	float m_fJumpPower;
	bool m_bJump;
	bool m_bFalling;

	float m_fkg;

	bool m_bStep_Monster;

	float fY;
	float fY2;


	DWORD Jumping_Time;
	POINT m_pGUIDE;
};

