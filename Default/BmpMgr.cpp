#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr*	CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
}

void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImageKey)
{
//	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImageKey))


}

HDC CBmpMgr::Find_Image(const TCHAR * pImageKey)
{
	return HDC();
}

void CBmpMgr::Release(void)
{
}
