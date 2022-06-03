#pragma once
#include "Obj.h"
class CBlock :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	void Initialize(void) override;
	int Update(void) override;
	void Late_Update(void) override;
	void Release(void) override;
	void Render(HDC hDC) override;


private:
	bool m_bCreate;
};

