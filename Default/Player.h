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

	void Set_FixPoint( float _fY) {  m_fFixPointY = _fY; }
	void Set_bJump(bool temp) { m_bJump = temp; }
	void Set_StepBlock(bool temp) { m_bStep_Block = temp; }

	float	Get_Gravity(void){ return (m_fJumpPower*m_fTime - (9.8*m_fTime*m_fTime*0.5f)); }

private:
	void Key_Input(void);
	void Jumping(void);
	void Check_ActiveBuff(void);
	void Coin_Pickup();
	void Buff_Mushroom();
	void Buff_Star(bool bActive);
	void Buff_Flower(bool bActive);

private:
	float m_pShield_Angle;
	float m_fTime;
	float m_fJumpPower;
	bool m_bJump;
	bool m_bFalling;

	ITEM_TYPE m_iActiveBuff;
	DWORD m_dwBuffTime;
	bool m_bIsBuffActive;

	float m_fkg;

	float m_fFixPointY;
	bool m_bStep_Block;

	float fY;
	float fY2;

	POINT m_pGUIDE;
};

