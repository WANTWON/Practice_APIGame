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
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Set_Stage(STAGE_LIST _Stage) { m_eChoice_Stage = _Stage; }
	void Release(void);
	void Set_NewGame(void) { m_bNewGame = true; }
	

public:
	static CStageMgr* Get_Instance(void)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CStageMgr;

		return m_pInstance;
	}
	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CStageMgr* m_pInstance;
	STAGE_LIST m_eChoice_Stage;

	CStage*  m_pStage[STAGE_END];

	CObj*   m_Mouse;
	DWORD  m_dwTime;
	RECT m_tRect[4];

	bool m_bNewGame;


};

