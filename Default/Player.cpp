#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 100.f, 575.f, 50.f, 50.f };
	m_fSpeed = 10.f;
}
void CPlayer::Late_Update(void)
{
}
int CPlayer::Update(void)
{
	Key_Down();
	Update_Rect();
	return OBJ_NOEVENT;
}
void CPlayer::Release(void)
{

}
void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}


void CPlayer::Key_Down(void)
{
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
}