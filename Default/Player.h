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
	void Set_FixPoint( float _fY) {  m_fFixPointY = _fY; }
	void Set_bJump(bool temp) { m_bJump = temp; }
	void Set_StepBlock(bool temp) { m_bStep_Block = temp; }
	void Set_Dead_Moment(void);
	void Set_Dead_Count(void) { m_bDead_Count = true; }

	
private:
	void Key_Input(void);
	void Jumping(void);

private:
	float m_pShield_Angle;
	float m_fTime;
	float m_fJumpPower;
	bool m_bJump;
	bool m_bFalling;

	float m_fkg;

	float m_fFixPointY;
	bool m_bStep_Block;

	float fY;
	float fY2;

	POINT m_pGUIDE;
	
	
	int m_iLife;
	bool m_bPlay;
	float m_fPTime;

	
};

