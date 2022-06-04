#include "stdafx.h"
#include "Star.h"


CStar::CStar()
{

}

CStar::~CStar()
{
	Release();
}

void CStar::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;
}

void CStar::Release()
{

}

int CStar::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Animate();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CStar::Late_Update()
{

}

void CStar::Render(HDC hDC)
{

}

void CStar::Animate()
{

}