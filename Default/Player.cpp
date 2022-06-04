#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BlockMgr.h"
#include "Bullet.h"


CPlayer::CPlayer() 
	: m_pShield_Angle(0), m_bJump(false), m_fJumpPower(0), m_fTime(0), m_bFalling(false), 
	m_bStep_Monster(false), fY(0), fY2(0), m_iActiveBuff(ITEM_END), m_dwBuffTime(GetTickCount()),
	m_bIsBuffActive(false), m_bCanShoot(false), m_iLastDir(DIR_RIGHT)
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
	Jumping_Time = GetTickCount();
	m_dwTIme = GetTickCount();
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bJump)
		m_fTime = 0;

	Jumping();
	Check_ActiveBuff();
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
}

void CPlayer::Release(void)
{

}
void CPlayer::Render(HDC hDC)
{
	if (m_bCanShoot)
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

void CPlayer::Coin_Pickup()
{
	// Increase Coin by 1
	// Increase Points by 200
}

void CPlayer::Buff_Mushroom()
{
	if (GetTickCount() > m_dwBuffTime + 5000)
	{
		// De-activate Buff
		m_tInfo.fCX -= m_tInfo.fCX * .5f;
		m_tInfo.fCY -= m_tInfo.fCY * .5f;

		m_iActiveBuff = ITEM_END;
		m_bIsBuffActive = false;
	}
	else
	{
		if (!m_bIsBuffActive)
		{
			// Activate Buff
			m_tInfo.fCX += m_tInfo.fCX;
			m_tInfo.fCY += m_tInfo.fCY;

			m_bIsBuffActive = true;
		}
	}
}

void CPlayer::Buff_Star()
{
	// TODO
}

void CPlayer::Buff_Flower()
{
	if (GetTickCount() > m_dwBuffTime + 100000)
	{
		// De-activate Buff
		m_bCanShoot = false;

		m_iActiveBuff = ITEM_END;
		m_bIsBuffActive = false;
	}
	else
	{
		if (!m_bIsBuffActive)
		{
			// Activate Buff
			m_bCanShoot = true;

			m_bIsBuffActive = true;
		}
	}
}

void CPlayer::Shoot()
{
}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_iLastDir = DIR_RIGHT;
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
		
	else if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_iLastDir = DIR_LEFT;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		m_bJump = true;
		
	if (CKeyMgr::Get_Instance()->Key_Down('Z') && m_bCanShoot)
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_iLastDir));
}

void CPlayer::Jumping(void)
{
	
	//���͸� ����� ���� ������ ���, ������ ���� ������ ��� �ٸ��� �����߽��ϴ�.
	
	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);
	
	bool b_BlockCol = CBlockMgr::Get_Instance()->CollisionBlock(m_tRect, m_tInfo.fX, &fY2);


	if (m_bStep_Monster) // ���͸� ����� ��
	{
		m_fJumpPower = 10;
		m_tInfo.fY -= m_fJumpPower*m_fTime - (2.8f*m_fTime*m_fTime*0.5f);
		m_fTime += 0.09f;
		if (m_fTime > 1.2f)
			m_fTime = 1.2f;

		if (b_BlockCol && m_tInfo.fY + m_tInfo.fCY*0.5f >= fY2) 
			//�÷��̾��� Bottom ���� ������ Top�̶� �̼��ϰ� ������ ���� (�� ��� ������ ��)
		{
			m_fTime = 0.0f;
		}
		if (b_LineCol && m_tInfo.fY > fY) //������ �� ������ �� �����ϱ�
		{
			m_fTime = 0.0f;
		}

	}
	else if (m_bJump)  //������ ���� ��
	{
		m_fJumpPower = 15;
		m_tInfo.fY -= m_fJumpPower*m_fTime - (9.8f*m_fTime*m_fTime*0.5f);
		m_fTime += 0.13f;
		if (m_fTime > 3.9f)
			m_fTime = 3.9f;

		if (b_BlockCol && m_tInfo.fY+m_tInfo.fCY*0.5f >= fY2) //플레이어의 Bottom 값이 블록의 Top이랑 미세하게 겹쳤을 때만 (즉 상단 접촉할 때)
		{
			m_fTime = 0.0f;
			m_bJump = false;
		}
		if (b_LineCol && m_tInfo.fY > fY) //땅보다 더 내려갈 수 있으니까
		{
			m_bJump = false;
			m_fTime = 0.0f;

			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
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

