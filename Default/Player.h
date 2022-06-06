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
	void Set_bJumpFalse(void) { m_bJump = false; }

	ITEM_TYPE Get_ActiveBuff() { return m_iActiveBuff; }
	void Set_ActiveBuff(ITEM_TYPE iBuff) { m_iActiveBuff = iBuff; }
	void Set_BuffTime(DWORD dwTime) { m_dwBuffTime = dwTime; }
	void Set_IsBuffActive(bool bIsBuffActive) { m_bIsBuffActive = bIsBuffActive; }
	void Remove_Buff(ITEM_TYPE iBuff);

	void Set_bJump(bool temp) { m_bJump = temp; }
	void Set_StepMonster(bool temp) { m_bStep_Monster = temp; }

	bool Get_bJump(void) { return m_bJump; }
	void Set_JumpingTime(void) { Jumping_Time = GetTickCount(); }
		
	

	float	Get_Gravity(void){ return (m_fJumpPower*m_fTime - (4.f*m_fTime*m_fTime*0.5f)); }

	void Set_Dead_Moment(void);
	void Set_Dead_Count(void) { m_bDead_Count = true; }
	bool Get_Count(void) { return m_bDead_Count; }
	bool Get_Buff(void) { return m_bIsBuffActive; }
	void Get_Active(bool bActive) { m_bActive = bActive; }
	void Set_Item(bool _bItem) { m_bItem = _bItem; }
	int Get_Life(void) { return m_iLife; }
	void Set_Life(int _Life) { m_iLife = _Life; }
	int Get_Level(void) { return m_iLevel; }

	const float Get_Time(void) const { return m_fTime; }
	const PLAYER_LIST& Get_PlayerType(void) { return m_eType; }
	void Offset(void);
	

	//New
public:
	void	Gravity(void);
	void	Set_Flying(bool _fly) { m_bFlying = _fly; }


private:
	void Key_Input(void);
	void Jumping(void);
	void Check_ActiveBuff(void);
	void Coin_Pickup();
	void Buff_Mushroom();
	void Buff_Star();
	void Buff_Flower();

private:
	float m_pShield_Angle;
	bool m_bFalling;

	ITEM_TYPE m_iActiveBuff;
	DWORD m_dwBuffTime;
	bool m_bIsBuffActive;
	bool m_bIsInvincible;
	bool m_bColorSwitch;
	bool m_bCanShoot;
	DIRECTION m_iLastDir;

	float m_fkg;

	bool m_bStep_Monster;

	float fY;
	float fY2;

	DWORD m_dwTime;
	DWORD Jumping_Time;
	POINT m_pGUIDE;
	PLAYER_LIST m_eType;
	
	int	m_iLevel;
	bool m_bPlay;
	float m_fPTime;
	bool m_bActive;
	bool m_bItem;
	int m_iLife;
	bool m_bFirst;
	bool m_bLineCol;
	bool m_bBlock;
	bool m_bFlag;


private:
	bool	m_bJump;
	float m_fJumpPower;

	bool m_bFlying;



};

