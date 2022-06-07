#pragma once
#include "Scene.h"
class CMyMenu :
	public CScene
{
public:
	CMyMenu();
	~CMyMenu();
public:
	virtual void Initialize();
	virtual void Release();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
};

