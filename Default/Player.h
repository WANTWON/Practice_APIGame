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

	void Set_bJump(void) { m_bJump = true; }
	void Set_ActiveBuff(ITEM_TYPE iBuff) { m_iActiveBuff = iBuff; }
	void Set_BuffTime(DWORD dwTime) { m_dwBuffTime = dwTime; }
	void Set_IsBuffActive(bool bIsBuffActive) { m_bIsBuffActive = bIsBuffActive; }

	void Set_bJump(bool temp) { m_bJump = temp; }
	void Set_StepMonster(bool temp) { m_bStep_Monster = temp; }

	bool Get_bJump(void) { return m_bJump; }
	void Set_JumpingTime(void) { Jumping_Time = GetTickCount(); }

	

	float	Get_Gravity(void){ return (m_fJumpPower*m_fTime - (9.8*m_fTime*m_fTime*0.5f)); }
	void Set_StepBlock(bool temp) { m_bStep_Block = temp; }
	void Set_Dead_Moment(void);
	void Set_Dead_Count(void) { m_bDead_Count = true; }

	
private:
	void Key_Input(void);
	void Jumping(void);
	void Check_ActiveBuff(void);
	void Coin_Pickup();
	void Buff_Mushroom();
	void Buff_Star();
	void Buff_Flower();
	void Shoot();

private:
	float m_pShield_Angle;
	float m_fTime;
	float m_fJumpPower;
	bool m_bJump;
	bool m_bFalling;

	ITEM_TYPE m_iActiveBuff;
	DWORD m_dwBuffTime;
	bool m_bIsBuffActive;
	bool m_bCanShoot;
	DIRECTION m_iLastDir;

	float m_fkg;

	bool m_bStep_Monster;

	float fY;
	float fY2;

	DWORD m_dwTIme;
	DWORD Jumping_Time;
	POINT m_pGUIDE;
	
	
	int m_iLife;
	bool m_bPlay;
	float m_fPTime;

	
};

