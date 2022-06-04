#pragma once

#include "Obj.h"

class CItem abstract : public CObj
{
public:
	CItem();
	virtual ~CItem();

	// 게터와 세터
	ITEM_TYPE Get_Type() { return m_Type; }
	void Set_Type(ITEM_TYPE type) { m_Type = type; }

protected:
	ITEM_TYPE m_Type;

	DWORD m_dwTime;

	bool m_bIsSpawned;
	float m_fAnimSpeed;
	float m_fAnimTime;
	float m_fAnimAccel;

	virtual void Animate() PURE;
};