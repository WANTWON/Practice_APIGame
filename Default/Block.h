#pragma once
#include "Obj.h"

class CBlock abstract :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		PURE;
	virtual void Late_Update(void)	PURE;
	virtual void Release(void)		PURE;
	virtual void Render(HDC hDC)	PURE;


private:
	bool	m_bCreate;


};

