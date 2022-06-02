#pragma once
#include "Struct.h"
#include "Define.h"
#include "Function.h"
#include "Enum.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize(void) PURE;
	virtual int Update(void)	PURE;
	virtual void Late_Update(void) PURE;
	virtual void Release(void)	PURE;
	virtual void Render(HDC hDC)	PURE;

public:
	void Update_Rect(void);
	void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void Set_Angle(int angle) { m_fAngle = float(angle); }
	void Set_Rect(float _left, float _top, float _right, float _bottom) { m_tRect.left = int(_left); m_tRect.top = int(_top); m_tRect.right = int(_right); m_tRect.bottom = int(_bottom); }
	void Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void Set_bDead(bool _dead) { m_bDead = _dead; }
	void Set_Target(CObj* temp) { m_pTarget = temp;; }
	const RECT& Return_Rect(void) const { return m_tRect; }
	const INFO& Get_Info(void) const { return m_tInfo; }
	const DIRECTION& Return_Dir(void) const { return m_eDir; }

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	float  m_fSpeed;
	float m_fAngle;
	DIRECTION m_eDir;
	CObj* m_pTarget;
	bool m_bDead;

};

