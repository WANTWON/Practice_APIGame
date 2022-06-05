#pragma once
#include "Player.h"
#include "Mouse.h"
#include "Stage.h"

class CStage1 : public CStage
{
public:
	CStage1();
	~CStage1();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);
};

