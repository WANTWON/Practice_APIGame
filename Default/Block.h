#pragma once
#include "Obj.h"

class CBlock abstract :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	virtual void Initialize(void)	PURE;
	virtual int  Update(void)		PURE;
	virtual void Late_Update(void)	PURE;
	virtual void Release(void)		PURE;
	virtual void Render(HDC hDC)	PURE;

public:
	bool	Get_IsItem(void) { return m_bItem; }


protected:
	bool	m_bItem;


private:
	bool	m_bCreate;

};

