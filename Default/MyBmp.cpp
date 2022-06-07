#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스 핸들, 이미지는 프로그램에서 얻어오는 것이 아니라 파일로부터 읽어 들이기 때문에 NULL값
		pFilePath,  // 파일 경로
		IMAGE_BITMAP, // 어떤 타입을 읽을 것인가
		0,			// 가로, 세로 사이즈
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldMap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
