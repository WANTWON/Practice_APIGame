#pragma once
#include "Define.h"
#include "Player.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

	void Initialize();
	void Release();

	// 프레임마다 실행되는 함수 
	void Update();
	void Late_Update();
	void Render();

private:
	HDC m_HDC;
	CObj* m_pPlayer;
	DIRECTION eDir;
};

