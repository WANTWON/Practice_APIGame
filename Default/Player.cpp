#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BlockMgr.h"
#include "StageMgr.h"
#include "Stage.h"


CPlayer::CPlayer() : m_pShield_Angle(0), m_bJump(false), m_fJumpPower(0), m_fTime(0), m_bFalling(false), m_bStep_Block(false), fY(0), fY2(0), m_iLife(0), m_bPlay(true), m_fPTime(0.f)
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
	m_tInfo = { 400.f, 300.f, 30.f, 30.f }; //x좌표, y좌표, 가로길이, 세로길이
	m_fSpeed = 5.f;
	m_fJumpPower = 15.f;
	m_fkg = 9.8f;
	m_iLife = 3;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bJump)
		m_fTime = 0;

	
	Jumping();
	Key_Input();
	Update_Rect();


	return OBJ_NOEVENT;
}
void  CPlayer::Late_Update(void)
{
	if (m_tInfo.fY >= WINCY)
	{
		m_tInfo.fY = 0.f;
	}
	CBlockMgr::Get_Instance()->Collision_with_Direction(this);
	Set_Dead_Moment();
	
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
	{
		m_bJump = true;
	}
		
}

void CPlayer::Jumping(void)
{
	if (m_bPlay)
	{
		bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);

		bool b_BlockCol = CBlockMgr::Get_Instance()->CollisionBlock(m_tRect, m_tInfo.fX, &fY2);

		if (m_bJump)
		{
			m_tInfo.fY -= m_fJumpPower*m_fTime - (9.8*m_fTime*m_fTime*0.5f);
			m_fTime += 0.13f;
			if (m_fTime > 3.9f)
				m_fTime = 3.9f;

			if (b_BlockCol && m_tInfo.fY + m_tInfo.fCY*0.5f >= fY2) //플레이어의 Bottom 값이 블록의 Top이랑 미세하게 겹쳤을 때만 (즉 상단 접촉할 때)
			{
				m_fTime = 0.0f;
				m_bJump = false;
			}
			if (b_LineCol && m_tInfo.fY > fY) //땅보다 더 내려갈 수 있으니까
			{
				m_bJump = false;
				m_fTime = 0.0f;
				//m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
			}
		}
		else if (b_LineCol)
		{
			if (b_BlockCol)
			{
				m_tInfo.fY = fY2 - m_tInfo.fCY*0.5f;
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
}



void CPlayer::Set_Dead_Moment(void)
{
	if (m_bDead_Count)
	{
		m_bPlay = false;
		m_tInfo.fY -= m_fJumpPower*m_fPTime - (9.8*m_fPTime*m_fPTime*0.5f);
		m_fPTime += 0.13f;
		
		if (m_tInfo.fY > WINCY)
		{
			m_iLife -= 1;
			m_fPTime = 0.0f;
			m_bPlay = true;
			m_bJump = false;
			m_bBye = true;
			m_bDead_Count = false;
		}
	}
}
