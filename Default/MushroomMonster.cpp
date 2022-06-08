#include "stdafx.h"
#include "LineMgr.h"
#include "MushroomMonster.h"
#include "BlockMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mushroom.bmp", L"Mushroom_Front");

}
int  CMushroomMonster::Update(void)
{

	if (false == m_bEditMode)
	{
		if (m_bDead)
			return OBJ_DEAD;

		if (m_bGet_Attacked)
		{
			m_iMonsterNumber = 1;
			Set_Dead(true);

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

	if (m_dwDrawTime + 200 < GetTickCount())
	{
		++DrawID;
		if (DrawID == 2)
			DrawID = 0;
		m_dwDrawTime = GetTickCount();
	}

	CBlockMgr::Get_Instance()->Collision_with_Direction(this);
	CCollisionMgr::Collision_Bullet(this, CObjMgr::Get_Instance()->Get_Bullets());

}

void CMushroomMonster::Release(void)
{

}

void CMushroomMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Mushroom_Front");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		16 * DrawID,								// 비트맵 출력 시작 좌표, X,Y
		0,
		16,				// 복사할 비트맵의 가로, 세로 길이
		16,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
}


void CMushroomMonster::Move(void)
{
	float fY = 0.f;
	float fY2 = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, m_tInfo.fY, &fY);
	bool b_BlockCol = CBlockMgr::Get_Instance()->CollisionBlock(m_tRect, m_tInfo.fX, &fY2);


	if (b_LineCol)
	{

		if (m_bFalling)
		{
			m_tInfo.fY += m_fSpeed;
			if (m_tInfo.fY >= fY - m_tInfo.fCY*0.5f)
				m_bFalling = false;
		}
		else
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;

		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY = fY - m_tInfo.fCY*0.5f;

	}
	else
	{
		m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}



}
