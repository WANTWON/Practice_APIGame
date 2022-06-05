#pragma once
#include "Bullet.h"
class CMonsterBullet :
	public CBullet
{
public:
	CMonsterBullet();
	virtual ~CMonsterBullet();

public:
	void Initialize() override;
	void Release() override;

	// 프레임마다 실행되는 함수
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;

	void Set_StartPos(float _fX, float _fY) { m_fBulletStartPosX = _fX; m_fBulletStartPosY = _fY; }

};

