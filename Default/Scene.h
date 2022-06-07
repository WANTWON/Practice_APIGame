#pragma once
#include "Include.h"
#include "BmpMgr.h"
class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual void Initialize() PURE;
	virtual void Release() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
};

