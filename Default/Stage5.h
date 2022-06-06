#pragma once
#include "Stage.h"
#include "Line.h"
#include "Obj.h"
#include "Player.h"
#include "MushroomMonster.h"
#include "TurtleMonster.h"
#include "JumpingMonster.h"
#include "FlyingMonster.h"
#include "BossMonster.h"
#include "NormalBlock.h"
#include "CoinBlock.h"
#include "ItemBlock.h"
#include "FlagBlock.h"
#include "Mouse.h"

class CStage5 :
	public CStage
{
public:
	CStage5();
	~CStage5();
public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Key_Input(void);
	void Render(HDC hDC);
public:
	void Save_File(void);
	void Load_File(void);
private:
	LINEPOINT m_tLinePoint[END];
	list<CLine*>				m_LineList;
	
	int m_iNumber;
	CObj*   m_Mouse;
};

