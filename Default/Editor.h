#pragma once
//Design
#include "Stage.h"
#include "AbstractFactory.h"
#include "BlockMgr.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "StageMgr.h"

//Obj
#include "Player.h"
#include "MushroomMonster.h"
#include "TurtleBack.h"
#include "TurtleMonster.h"
#include "JumpingMonster.h"
#include "FlyingMonster.h"
#include "BossMonster.h"
#include "NormalBlock.h"
#include "CoinBlock.h"
#include "ItemBlock.h"
#include "BlockNull.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Star.h"
#include "Flower.h"
#include "Mouse.h"

//Header
#include "Enum.h"
#include "Function.h"

class CEditor :
	public CStage
{
public:
	CEditor();
	virtual ~CEditor();

public:
	void	Initialize(void)	override;
	int		Update(void)		override;
	void	Late_Update(void)	override;
	void	Release(void)		override;
	void	Render(HDC hDC)		override;



private:
	map<int, CObj*>		m_mapObj;
	map<int, CObj*>		m_mapChoiceObj;
	CObj*	m_ObjMouse;
	POINT	m_ePt;



};

