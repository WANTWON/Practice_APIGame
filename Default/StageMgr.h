#pragma once
#include "Include.h"
#include "Mouse.h"

class CStage;

class CStageMgr
{
private:
	CStageMgr();
	~CStageMgr();

public:
	void Initialize(void);
	void Release(void);

	// 프레임마다 실행되는 함수 
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Render_Points_Total(HDC hDC);

	// 게터와 세터
	void Set_Stage(STAGE_LIST _Stage) { m_eChoice_Stage = _Stage; }
	void Set_NewGame(void) { m_bNewGame = true; }
	int Get_Score() { return m_iScore; }
	void Increment_Score(int iScore) { m_iScore += iScore; }
	int Get_Coins() { return m_iCoins; }
	void Increment_Coins(int iCoins) { m_iCoins += iCoins; }

	void	Load_File(void);

	static CStageMgr* Get_Instance(void)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CStageMgr;

		return m_pInstance;
	}

	static void Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CStageMgr* m_pInstance;
	CStage* m_pStage[STAGE_END];
	STAGE_LIST m_eChoice_Stage;

	CStage*	m_pEditor;

	CObj*   m_Mouse;
	DWORD  m_dwTime;

	RECT m_tRect[4];
	RECT m_tEditRect;

	bool m_bNewGame;

	int m_iScore;
	int m_iCoins;
};

