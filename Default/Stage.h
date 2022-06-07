#pragma once
#include "Include.h"
#include "BlockMgr.h"
#include "MushroomMonster.h"
#include "UIMgr.h"

class CStage
{
public:
	CStage() : m_dwTime(GetTickCount()), m_bClear(false), m_bView(false) {}
	virtual ~CStage() {}

	virtual void Initialize(void) PURE;
	virtual void Release(void) PURE;

	// 프레임마다 실행되는 함수 
	virtual int Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) PURE;

	// 게터와 세터
	void Set_Clear_true(void) { m_bClear = true; }
	void Set_View(bool _View) { m_bView = _View; }

	bool Get_Clear(void) { return m_bClear; }
	bool Get_View(void) { return m_bView; }

protected:
	DWORD  m_dwTime;
	bool m_bClear;
	bool m_bView;
};

