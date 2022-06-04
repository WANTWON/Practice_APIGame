#include "stdafx.h"
#include "BossMonster.h"
#include "LineMgr.h"


CBossMonster::CBossMonster() : fY(0)
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 100.f, 100.f };
	m_fSpeed = 5.f;
	m_iHp = 10;
}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	

	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update(void)
{
	if (m_bGet_Attacked)
	{
			m_bDead = true;
	}
}

void CBossMonster::Release(void)
{
}

void CBossMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBossMonster::Move(void)
{
	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);

	if (b_LineCol)
	{

		if (m_bFalling)
		{
			m_tInfo.fY += m_fSpeed*1.3f;
			if (m_tInfo.fY >= fY - m_tInfo.fCY*0.5f)
				m_bFalling = false;
		}
		else
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;

		m_tInfo.fX += m_fSpeed;

	}
	else
	{
		m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}
}
