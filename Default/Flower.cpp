#include "stdafx.h"
#include "Flower.h"


CFlower::CFlower()
{

}

CFlower::~CFlower()
{
	Release();
}

void CFlower::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;
}

void CFlower::Release()
{

}

int CFlower::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Animate();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CFlower::Late_Update()
{

}

void CFlower::Render(HDC hDC)
{

}

void CFlower::Animate()
{

}