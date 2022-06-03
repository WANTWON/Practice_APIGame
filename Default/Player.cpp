#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"


CPlayer::CPlayer() : m_pShield_Angle(0), m_bJump(false), m_fJumpPower(0), m_fTime(0), m_bFalling(false)
{
	ZeroMemory(&m_pGUIDE, sizeof(POINT));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	//플레이어 네모의 크기를 정하는 것
	m_tInfo = { 400.f, 300.f, 50.f, 50.f }; //x좌표, y좌표, 가로길이, 세로길이
	m_fSpeed = 5.f;
	m_fJumpPower = 15.f;

}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Jumping();
	Key_Input();
	Update_Rect();


	return OBJ_NOEVENT;
}
void  CPlayer::Late_Update(void)
{
	if (m_tInfo.fY >= WINCY)
	{
		m_bFalling = true;
		m_tInfo.fY = 0.f;
	}

}

void CPlayer::Release(void)
{

}
void CPlayer::Render(HDC hDC)
{

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;
	else if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		m_bJump = true;
}

void CPlayer::Jumping(void)
{
	float fY = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower*m_fTime - (9.8f*m_fTime*m_fTime*0.5f);
		m_fTime += 0.13f;

		if (b_LineCol && m_tInfo.fY > fY) //땅보다 더 내려갈 수 있으니까
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
		}
	}
	else if (b_LineCol)
	{
		if (m_bFalling)
		{
			m_tInfo.fY += m_fSpeed;
			if (m_tInfo.fY >= fY - m_tInfo.fCY*0.5f)
				m_bFalling = false;
		}

		else
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
	}
	else
	{
		m_tInfo.fY += m_fSpeed;
		m_bFalling = true;
	}

}