#pragma once

#include "Obj.h"

class CMouse : public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	void Initialize(void)  override;
	int Update(void) override;
	void Late_Update(void) override;
	void Release(void) override;
	void Render(HDC hDC) override;

public:
	void Set_Radius(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}

private:
	int angle = 0;
};

