#pragma once
#include "Player.h"
#include "Mouse.h"
#include "Stage.h"

class CStage2 : public CStage
{
public:
	CStage2();
	~CStage2();


public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);

};

