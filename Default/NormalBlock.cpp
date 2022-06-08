#include "stdafx.h"
#include "NormalBlock.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CNormalBlock::CNormalBlock()
{
}


CNormalBlock::~CNormalBlock()
{
	Release();
}

void CNormalBlock::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_BlockType = BLOCK_NORMAL;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NormalBlock.bmp", L"Block_Normal");
}

int CNormalBlock::Update(void)
{
	if (OBJ_DEAD == m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CNormalBlock::Late_Update(void)
{
	CCollisionMgr::Collision_Bullet(this, CObjMgr::Get_Instance()->Get_Bullets());
}

void CNormalBlock::Release(void)
{
}

void CNormalBlock::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Block_Normal");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		16,				// 복사할 비트맵의 가로, 세로 길이
		16,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
}
