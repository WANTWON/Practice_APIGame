#include "stdafx.h"
#include "TurtleBack.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "BlockMgr.h"


CTurtleBack::CTurtleBack()
{
}


CTurtleBack::~CTurtleBack()
{
	Release();
}

void CTurtleBack::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 40.f, 30.f };
	m_fSpeed = 5.f;

	m_iType = MONSTER_TURTLEBACK;
}
int  CTurtleBack::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (false == m_bEditMode)
	{
		Gravity();
		Move();
	}



	Update_Rect();

	return OBJ_NOEVENT;
}

void CTurtleBack::Late_Update(void)
{
/*
	if (m_tRect.right > WINCX - 50 || m_tRect.left < 50)
	{
		m_fSpeed *= -1.f;
	}

	if (m_tRect.bottom > WINCY - 50 || m_tRect.top < 50)
	{
		m_fSpeed *= -1.f;
	}
*/
	if (m_bGet_Attacked)
		m_bDead = true;


}

void CTurtleBack::Release(void)
{

}

void CTurtleBack::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	HBRUSH myBrush = nullptr;
	HBRUSH oldBrush = nullptr;

	myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 200, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

}


void CTurtleBack::Move(void)
{
	float fY = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);


	//	ColWithBlock
	float fYDest = 0.f;
	float fYTemp = 0.f;

	//	Collision Up with block
	if (CBlockMgr::Get_Instance()->CollisionBlock_Ex(m_tInfo, &fYDest))
	{
		Set_PosY(-fYDest);
	}
	// Collision L, R with block ( except Up, Down )

	DIRECTION Dir = CBlockMgr::Get_Instance()->Col_ReturnDir_RecLR(m_tInfo);
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
		}
		else
		{
			m_tInfo.fX += m_fSpeed;
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
		}
		
	}
	else
	{
		//m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}


}


void CTurtleBack::Gravity(void)
{
	m_fTime += 0.05f;

	if (m_fTime >= 2.3f)
		m_fTime = 2.3f;

	m_tInfo.fY += 4.f * m_fTime * m_fTime;
}
