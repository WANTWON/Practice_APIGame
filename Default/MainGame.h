#pragma once
#include "Define.h"
#include "Player.h"



class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(void);
	void Update(void);
	void Release(void);
	void Render(void);

private:
	HDC  m_HDC;
	CObj* m_pPlayer;
	DIRECTION eDir;
};

