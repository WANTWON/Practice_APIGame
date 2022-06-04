#pragma once
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "Stage.h"

class CStage3 : public CStage
{
public:
	CStage3();
	~CStage3();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);

};

