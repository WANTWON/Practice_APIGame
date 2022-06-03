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

private:
	HDC m_hDc;

};

