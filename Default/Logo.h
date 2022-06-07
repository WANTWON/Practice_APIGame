#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	~CLogo();
public:
	virtual void Initialize();
	virtual void Release() ;
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
};

