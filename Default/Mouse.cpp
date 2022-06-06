#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}


void CMouse::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
}
int CMouse::Update(void)
{
	POINT pt = {}; //마우스 커서의 위치를 받아올 x좌표, y좌표

	GetCursorPos(&pt); //마우스 커서의 위치를 알아오는 함수
					   //현재 이 상태는 Window 모니터 창을 기준으로 좌표를 반환하기 때문에 생성한 창을 기준으로 좌표를 반환하게 해야함

	ScreenToClient(g_hWnd, &pt); //생성한 스크린 창을 기준으로 좌표를 반환함.

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	Update_Rect();

	ShowCursor(FALSE); //마우스 커서 보이게 하기 말기
	return OBJ_NOEVENT;
}
void CMouse::Late_Update(void)
{

}
void CMouse::Release(void)
{

}
void CMouse::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

}