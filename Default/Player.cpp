#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BlockMgr.h"
#include "Bullet.h"
#include "StageMgr.h"
#include "Stage.h"

CPlayer::CPlayer()
	: m_pShield_Angle(0), m_bJump(false), m_fJumpPower(0), m_fTime(0), m_bFalling(false),
	m_bStep_Monster(false), fY(0), fY2(0), m_iActiveBuff(ITEM_END), m_dwBuffTime(GetTickCount()),
	m_bIsBuffActive(false), m_bCanShoot(false), m_iLastDir(DIR_RIGHT), m_bPlay(true), m_fPTime(0.f), m_bActive(false), m_bItem(false), m_iLife(0), m_bFirst(false),
	m_bLineCol(false), m_bFlag(false), m_bBlock(false),
	m_bIsInvincible(false), m_bColorSwitch(false), m_iLevel(0)

{
	ZeroMemory(&m_pGUIDE, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 30.f, 30.f };
	m_fSpeed = 5.f;
	m_fJumpPower = 15.f;
	m_fkg = 9.8f;
	Jumping_Time = GetTickCount();
	m_dwTime = GetTickCount();
	m_iLife = 3;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bJump)
		m_fTime = 0;



	Check_ActiveBuff();
	Key_Input();
	Jumping();
	Update_Rect();


	return OBJ_NOEVENT;
}

void  CPlayer::Late_Update(void)
{
	if (m_tInfo.fY >= WINCY)
	{
		m_tInfo.fY = 0.f;
	}
	if (m_bPlay)
	{
		CBlockMgr::Get_Instance()->Collision_with_Direction(this);
	}

	if (m_bStep_Monster)
	{
		//m_bJump = false;
		if (Jumping_Time + 10 < GetTickCount())
		{
			m_bJump = true;
			m_bStep_Monster = false;
		}
	}

	Set_Dead_Moment();
}

void CPlayer::Release(void)
{

}

void CPlayer::Render(HDC hDC)
{
	if (m_bIsInvincible)
	{
		if (GetTickCount() > m_dwTime + 400)
		{
			m_bColorSwitch = !m_bColorSwitch;
			m_dwTime = GetTickCount();
		}
		else
		{
			HBRUSH myBrush = nullptr;
			HBRUSH oldBrush = nullptr;

			myBrush = m_bColorSwitch ? (HBRUSH)CreateSolidBrush(RGB(255, 255, 0)) : (HBRUSH)CreateSolidBrush(RGB(255, 215, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

			SelectObject(hDC, oldBrush);
			DeleteObject(myBrush);
		}
	}
	else if (m_bCanShoot)
	{
		HBRUSH myBrush = nullptr;
		HBRUSH oldBrush = nullptr;

		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
	else
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CPlayer::Check_ActiveBuff(void)
{
	switch (m_iActiveBuff)
	{
	case ITEM_COIN:
		Coin_Pickup();
		break;
	case ITEM_MUSHROOM:
		Buff_Mushroom();
		break;
	case ITEM_STAR:
		Buff_Star();
		break;
	case ITEM_FLOWER:
		Buff_Flower();
		break;
	}
}

void CPlayer::Coin_Pickup()
{
	// Increase Coin by 1
	// Increase Points by 200
}

void CPlayer::Buff_Mushroom()
{
	if (!m_bIsBuffActive)
	{
		// Activate Buff
		m_tInfo.fCX += m_tInfo.fCX;
		m_tInfo.fCY += m_tInfo.fCY;
		m_bIsBuffActive = true;
		m_iLevel = 1;
	}
}

void CPlayer::Buff_Star()
{
	if (GetTickCount() > m_dwBuffTime + 5000)
	{
		// De-activate Buff
		m_bIsInvincible = false;
		m_iActiveBuff = ITEM_END;
		m_bIsBuffActive = false;
	}
	else
	{
		// Activate Buff
		if (!m_bIsBuffActive)
		{
			m_bIsInvincible = true;
			m_bIsBuffActive = true;
			m_iLevel = 2;
		}
	}
}

void CPlayer::Buff_Flower()
{
	if (!m_bIsBuffActive)
	{
		// Activate Buff
		m_tInfo.fCX += m_tInfo.fCX;
		m_tInfo.fCY += m_tInfo.fCY;
		m_bCanShoot = true;
		m_bIsBuffActive = true;
	}
}

void CPlayer::Remove_Buff(ITEM_TYPE iBuff)
{
	m_iActiveBuff = ITEM_END;
	m_bIsBuffActive = false;

	switch (iBuff)
	{
	case ITEM_MUSHROOM:
	{
		m_tInfo.fCX -= m_tInfo.fCX * 0.5f;
		m_tInfo.fCY -= m_tInfo.fCY * 0.5f;
	}
	case ITEM_STAR:
	{
		m_bIsInvincible = false;
		break;
	}
	case ITEM_FLOWER:
	{
		m_tInfo.fCX -= m_tInfo.fCX * 0.5f;
		m_tInfo.fCY -= m_tInfo.fCY * 0.5f;
		m_bCanShoot = false;
	}
	}
}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_bPlay)
		{
			m_tInfo.fX += m_fSpeed;
			m_iLastDir = DIR_RIGHT;
		}

	}

	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_bPlay)
		{
			m_tInfo.fX -= m_fSpeed;
			m_iLastDir = DIR_LEFT;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		m_bJump = true;

	if (CKeyMgr::Get_Instance()->Key_Down('Z') && m_bCanShoot)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_iLastDir, OBJ_PLAYER));
	}
}

void CPlayer::Jumping(void)
{
	if (m_bFirst)
	{
		m_bBlock = CBlockMgr::Get_Instance()->CollisionBlock(m_tRect, m_tInfo.fX, &fY2);
		if (m_bBlock)
		{
			m_bFirst = false;
		}
		if (m_bFirst)
		{
			m_tInfo.fX = m_tRect.left + 15.f;
			m_tInfo.fY += 5.f;
		}
		for (auto& iter : CBlockMgr::Get_Instance()->Get_Flaglist())
		{
			if (true == dynamic_cast<CFlagBlock*>(iter)->Get_Number())
			{
				dynamic_cast<CFlagBlock*>(iter)->Set_Down(1);
			}
		}
	}
	if (m_bBlock)
	{
		m_tInfo.fX += 2.f;
		m_bBlock = CBlockMgr::Get_Instance()->CollisionBlock(m_tRect, m_tInfo.fX, &fY2);
		m_bLineCol = CLineMgr::Get_Instance()->CollisionLine(this, &fY);
		if (m_bLineCol)
		{
			m_tInfo.fY = fY2 - m_tInfo.fCY*0.5f;
		}
	}
	else if (m_bLineCol)
	{
		m_tInfo.fX += 0.5f;
		m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
	}
	//======================================================================================
		if (m_bPlay)
		{
			bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(this, &fY);
			bool b_BlockCol = CBlockMgr::Get_Instance()->CollisionBlock(m_tRect, m_tInfo.fX, &fY2);
			m_bFlag = CLineMgr::Get_Instance()->CollisionFlag(m_tRect, &fY);

			if (m_bFlag)
			{
				m_fTime = 0.0f;
				m_bJump = false;
				m_bPlay = false;
				m_bFirst = true;
			}
			else if (m_bStep_Monster)
			{
				m_fJumpPower = 10;
				m_tInfo.fY -= m_fJumpPower*m_fTime - (2.8f*m_fTime*m_fTime*0.5f);
				m_fTime += 0.09f;
				if (m_fTime > 1.2f)
					m_fTime = 1.2f;

				if (b_BlockCol && m_tInfo.fY + m_tInfo.fCY*0.5f >= fY2)
				{
					m_fTime = 0.0f;
				}
				if (b_LineCol && m_tInfo.fY > fY)
				{
					m_fTime = 0.0f;
				}
			}
			else if (m_bJump)
			{
				m_fJumpPower = 15;
				m_tInfo.fY -= m_fJumpPower*m_fTime - (9.8*m_fTime*m_fTime*0.5f);
				if ((m_fJumpPower*m_fTime) < (9.8*m_fTime*m_fTime*0.5f))
				{
					m_bJump = true;
				}
				m_fTime += 0.13f;
				if (m_fTime > 3.9f)
					m_fTime = 3.9f;

				if (b_BlockCol && m_tInfo.fY + m_tInfo.fCY*0.5f >= fY2)
				{
					m_fTime = 0.0f;
					m_bJump = false;
				}
				if (b_LineCol && m_tInfo.fY > fY)
				{
					m_bJump = false;
					m_fTime = 0.0f;
					m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
				}
			}
			else if (b_LineCol && m_tInfo.fY > fY)
			{
				m_bJump = false;
				m_fTime = 0.0f;

				m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
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