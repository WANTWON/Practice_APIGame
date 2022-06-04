#pragma once
#include "Include.h"
class CStage
{
public:

	CStage() : m_dwTime(GetTickCount()), m_bClear(false)
	{
	}

	virtual ~CStage()
	{
	}

public:
	virtual void Initialize(void) PURE;
	virtual int Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Release(void) PURE;
	virtual void Render(HDC hDC) PURE;
public:
	void	Set_Clear_true(void) { m_bClear = true; }

protected:
	DWORD  m_dwTime;

	bool m_bClear;
	int m_iScore;
	

};

