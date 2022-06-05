#pragma once 
#include "Obj.h"
class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

	void Initialize() override;
	void Release() override;

	// 프레임마다 실행되는 함수
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;

	void Set_StartPos(float _fX, float _fY) { m_fBulletStartPosX = _fX; m_fBulletStartPosY = _fY; }

	//added an ID to distinguish between the monster's bullet and the player's bullet
	void Set_ID(OBJ_LIST _eID) { m_eID = _eID; }
	const OBJ_LIST& Get_ID(void) const { return m_eID; }

protected:
	float m_fAnimSpeed;
	float m_fAnimTime;
	float m_fAnimAccel;

	float m_fBulletStartPosX;
	float m_fBulletStartPosY;

	OBJ_LIST  m_eID;
};

