#include "stdafx.h"
#include "MyButton.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	// 사진의 가로 세로 사이즈 설정
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

}

int CMyButton::Update(void)
{

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{

}


void CMyButton::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		m_iDrawID * (int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
	//여기서 부터 하면 됨


}





void CMyButton::Release(void)
{

}
