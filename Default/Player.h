#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void Initialize(void) override;
	void Late_Update(void) override;
	int Update(void) override;
	void Release(void) override;
	void Render(HDC hDC) override;

public:
	void Key_Down(void);
};

