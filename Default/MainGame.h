#pragma once
#include "Define.h"
#include "Mouse.h"
#include "Stage.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();


public:
	void Initialize	(void);
	void Update		(void);
	void Late_Update(void);
	void Release	(void);
	void Render		(void);

	void Set_Stage(STAGE_LIST _Stage) { m_eChoice_Stage = _Stage; }

private:
	HDC m_hDc;

	STAGE_LIST m_eChoice_Stage;

	CStage*  m_pStage[STAGE_END];

	CObj*   m_Mouse;
	DWORD  m_dwTime;
	RECT m_tRect[4];

	bool m_bNewGame;
};

