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
	virtual void Update(void)	PURE;
	virtual void Release(void)	PURE;
	virtual void Render(HDC hDC)	PURE;

protected:
	void Update_Rect(void);
	void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	float  m_fSpeed;

};

