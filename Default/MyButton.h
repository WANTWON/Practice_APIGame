#pragma once
#include "Obj.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

class CMyButton :
	public CObj
{
public:
	CMyButton();
	~CMyButton();
public:
	void Initialize(void)  override;
	int Update(void) override;
	void Late_Update(void) override;
	void Release(void) override;
	void Render(HDC hDC) override;
private:
	int		m_iDrawID = 0;
};

