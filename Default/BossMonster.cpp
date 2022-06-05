#include "stdafx.h"
#include "BossMonster.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "Monster_Bullet.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "CollisionMgr.h"


CBossMonster::CBossMonster() : fY(0), m_bMove(true), m_dwMoveTime(GetTickCount()), m_dwCreateBulletTime(GetTickCount())
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 100.f, 100.f };
	m_fSpeed = 5.f;
	m_iHp = 30;
	m_fDistance = m_tInfo.fCX;
}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	

	Move();
	Set_TargetAngle();
	Make_Bullet();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update(void)
{
	if (m_bGet_Attacked)
	{
			m_bDead = true;
	}

	if (m_dwMoveTime + 4000 < GetTickCount())
	{
		Set_bMove();
		m_dwMoveTime = GetTickCount();
	}

	CCollisionMgr::Collision_Bullet(this, CObjMgr::Get_Instance()->Get_Bullets());
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
		m_tInfo.fY = fY - m_tInfo.fCY*0.5f;

		if(m_bMove)
			m_tInfo.fX += m_fSpeed;

	}
	else
	{
		if (m_bMove)
		{
			m_fSpeed *= -1;
			m_tInfo.fX += m_fSpeed;
		}
			
	}
}

void CBossMonster::Make_Bullet(void)
{
	if (m_bMove)
		return;

	if (m_dwCreateBulletTime + 700 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CMonsterBullet>::
			Create_with_Target(m_tInfo.fX + m_fTargetPosX, m_tInfo.fY - m_fTargetPosY, CObjMgr::Get_Instance()->Get_Player(), OBJ_MONSTER));

		dynamic_cast<CMonsterBullet*>(CObjMgr::Get_Instance()->Get_Bullets().back())->Set_MovePos(m_fTargetPosX, m_fTargetPosY);

		m_dwCreateBulletTime = GetTickCount();
	}

	

}

void CBossMonster::Set_TargetAngle(void)
{
	float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

	float fRadian = acosf(fWidth / fDiagonal);
	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		fRadian *= -1;

	m_fTargetPosX = cos(fRadian)*m_fDistance;
	m_fTargetPosY = sin(fRadian)*m_fDistance;

}

