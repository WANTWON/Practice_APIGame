#include "stdafx.h"
#include "LineMgr.h"
#include "MushroomMonster.h"
#include "BlockMgr.h"
#include "ScrollMgr.h"

CMushroomMonster::CMushroomMonster() : Direction_time(GetTickCount())
{
}


CMushroomMonster::~CMushroomMonster()
{
	Release();
}



void CMushroomMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 40.f, 40.f };
	m_fSpeed = 1.f;

	m_iType = MONSTER_MUSHROOM;

}
int  CMushroomMonster::Update(void)
{

	if (false == m_bEditMode)
	{
		Gravity();

		if (m_bDead)
			return OBJ_DEAD;

		if (m_bGet_Attacked)
		{
			m_iMonsterNumber = 1;
			m_bDead = true;

			/*	if (!m_bCount)
				{
					m_dwTime = GetTickCount();
					m_bCount = true;
				}*/
		}
		Move();
	}



	Update_Rect();

	return OBJ_NOEVENT;
}

void CMushroomMonster::Late_Update(void)
{
	/*if (m_bGet_Attacked && m_dwTime + 500 < GetTickCount())
		m_bDead = true;*/

	CBlockMgr::Get_Instance()->Collision_with_Direction(this);
	CCollisionMgr::Collision_Bullet(this, CObjMgr::Get_Instance()->Get_Bullets());

}

void CMushroomMonster::Release(void)
{

}

void CMushroomMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}


void CMushroomMonster::Move(void)
{
	float fY = 0.f;
	float fY2 = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, m_tInfo.fY, &fY);
	bool b_BlockCol = CBlockMgr::Get_Instance()->CollisionBlock(m_tRect, m_tInfo.fX, &fY2);



	//	ColWithBlock
	float fYDest = 0.f;
	float fYTemp = 0.f;

	//	Collision Up with block
	if (CBlockMgr::Get_Instance()->CollisionBlock_Ex(m_tInfo, &fYDest))
	{
		Set_PosY(-fYDest);
	}
	// Collision L, R with block ( except Up, Down )

	DIRECTION Dir = CBlockMgr::Get_Instance()->Col_ReturnDir_LR(m_tInfo);
	switch (Dir)
	{
	case DIR_LEFT:
		m_fSpeed *= -1;
		break;

	case DIR_RIGHT:
		m_fSpeed *= -1;
		break;

	default:
		break;
	}


	if (b_LineCol)
	{

		if (m_bFalling)
		{
			m_tInfo.fY += m_fSpeed;
			if (m_tInfo.fY >= fY - m_tInfo.fCY*0.5f)
				m_bFalling = false;
		}*/
		//else
		}
		else
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;

		m_tInfo.fX += m_fSpeed;

	}/*
	else
	{
		m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}*/
	/*
		if (b_BlockCol && m_tInfo.fY < fY2)
		{
			m_tInfo.fY = fY2 - m_tInfo.fCY*0.5f;
		}
		else
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
	*/


	m_tInfo.fX += m_fSpeed;

}

void CMushroomMonster::Gravity(void)
{
	m_fTime += 0.05f;

	if (m_fTime >= 2.3f)
		m_fTime = 2.3f;

	m_tInfo.fY += 4.f * m_fTime * m_fTime;
}
