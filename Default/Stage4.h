#pragma once
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "Stage.h"

class CStage4 : public CStage
{
public:
	CStage4();
	~CStage4();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);
};

