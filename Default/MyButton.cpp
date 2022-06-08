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
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

}

int CMyButton::Update(void)
{

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);
			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);
			return;
		}
		m_iDrawID = 1;
	}
	else
	{
		m_iDrawID = 0;
	}
	
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


}





void CMyButton::Release(void)
{

}
