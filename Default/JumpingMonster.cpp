#include "stdafx.h"
#include "JumpingMonster.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "TurtleBack.h"
#include "TurtleMonster.h"



CJumpingMonster::CJumpingMonster() : m_fTime(0), m_bJump(true)
{
}


CJumpingMonster::~CJumpingMonster()
{
}

void CJumpingMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 40.f, 50.f };
	m_fSpeed = 2.f;
	m_fJumpPower = 12.f;
}

int CJumpingMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Attacked)
	{
		if (!m_bCount)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(m_tInfo.fX + 70, m_tInfo.fY));
			m_dwTime = GetTickCount();
			m_bCount = true;
		}

	}

	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CJumpingMonster::Late_Update(void)
{
	if (m_bGet_Attacked)
	{
		m_bDead = true;

	}
}

void CJumpingMonster::Release(void)
{
}

void CJumpingMonster::Render(HDC hDC)
{
	if (m_bGet_Attacked == false)
	{
		HBRUSH myBrush = nullptr;
		HBRUSH oldBrush = nullptr;

		myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 200, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);

		Rectangle(hDC, m_tRect.left-20, m_tRect.top+20, m_tRect.right-40, m_tRect.bottom-20);
		Rectangle(hDC, m_tRect.left + 40, m_tRect.top + 20, m_tRect.right + 20, m_tRect.bottom - 20);

	}
	else
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

}

void CJumpingMonster::Move(void)
{
	
	float fY = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);

	if (b_LineCol)
	{
		Jumping();

		if (m_tInfo.fY > fY)
		{
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
			m_fTime = 0.f;
			//m_bJump = false;
		}
			
		
	}
	else
	{
		m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}
}

void CJumpingMonster::Jumping(void)
{
	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower*m_fTime - (9.8f*m_fTime*m_fTime*0.5f);
		m_fTime += 0.10f;


		if (m_pTarget)
		{
			if (m_pTarget->Get_Info().fX > m_tInfo.fX)
				m_tInfo.fX += m_fSpeed;
			else
				m_tInfo.fX -= m_fSpeed;
		}
		else
			m_tInfo.fX += m_fSpeed;
		

	}
	
}