#pragma once
#include "Monster.h"
class CTurtleMonster :
	public CMonster
{
public:
	CTurtleMonster();
	virtual ~CTurtleMonster();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);

	void Move(void);

public:
	void		Gravity(void);

private:
	

};

