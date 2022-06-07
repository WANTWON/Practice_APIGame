#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}



void CLineMgr::Add_Line(float _fX, float _fY)
{


	// 처음 마우스 피킹을 한 경우
	if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
	{
		m_tLinePoint[LEFT].fX = _fX;
		m_tLinePoint[LEFT].fY = _fY;
	}
	// 처음 피킹한 경우가 아닐 때
	else
	{
		m_tLinePoint[RIGHT].fX = _fX;
		m_tLinePoint[RIGHT].fY = _fY;

		m_Linelist.push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));
		m_Linelist.back()->Set_typeID(NORMAL_LINE);

		m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
		m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
	}

}	
void CLineMgr::Edit_NULL(float _fX, float _fY)
{
	if (0 == _fX && 0 == _fY)
	{
		m_tLinePoint[LEFT].fX = 0;
		m_tLinePoint[LEFT].fY = 0;
	}
}

void CLineMgr::Initialize(int _Number)
{
	/*if (1 == _Number)
	{
		
	}
	else if (2 == _Number)
	{
		LINEPOINT tPoint[4] =
		{
			{ 10.f, 400.f },
			{ 200.f, 500.f },
			{ 700.f, 500.f },
			{ 700.f, 100.f }
		};
  }*/
	if (3 == _Number)
	{

		LINEPOINT tPoint[8] =
		{
			{ 0, 450.f },
			{ 200.f, 450.f },
			{250.f, 200.f},
			{450.f, 200.f},
			{450.f, 450.f},
			{WINCX, 450.f},
			{ 550.f, 440.f },
			{ 550.f, 100.f}
		};
		m_Linelist.push_back(new CLine(tPoint[0], tPoint[1]));
		m_Linelist.push_back(new CLine(tPoint[1], tPoint[2]));
		m_Linelist.push_back(new CLine(tPoint[2], tPoint[3]));
		m_Linelist.push_back(new CLine(tPoint[3], tPoint[4]));
		m_Linelist.push_back(new CLine(tPoint[4], tPoint[5]));
		m_Flaglist.push_back(new CLine(tPoint[6], tPoint[7]));
	}

}

void CLineMgr::Render(HDC hDC)
{

	for (auto& iter : m_Linelist)
		iter->Render(hDC);

	for (auto& iter : m_Flaglist)
		iter->Render(hDC);

}

void CLineMgr::Release(void)
{
	for_each(m_Linelist.begin(), m_Linelist.end(), CDeleteObj());
	m_Linelist.clear();

	for_each(m_Flaglist.begin(), m_Flaglist.end(), CDeleteObj());
	m_Flaglist.clear();

}

//bool CLineMgr::CollisionLine(CObj*	_pObj, float* _fY)		//+
//{
//	if (m_Linelist.empty())
//		return false;
//
//	CLine* pTarget = nullptr;
//
//	for (auto& iter : m_Linelist)
//	{
//		if (_pObj->Get_Info().fX >= iter->Get_Line().fLPoint.fX  
//			&& _pObj->Get_Info().fX < iter->Get_Line().fRPoint.fX
//			&& _pObj->Get_Info().fY + (_pObj->Get_Info().fCY * 0.5f) >= iter->Get_Y(_pObj->Get_Info().fX)
//			&& _pObj->Get_Info().fY - (_pObj->Get_Info().fCY * 0.5f) < iter->Get_Y(_pObj->Get_Info().fX))
//			pTarget = iter;
//	}
//
//
//
//
//	if (!pTarget)
//		return false;
//
//	// Á÷¼±ÀÇ ¹æÁ¤½Ä 
//	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
//	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1
//
//	float x1 = pTarget->Get_Line().fLPoint.fX;
//	float y1 = pTarget->Get_Line().fLPoint.fY;
//
//	float x2 = pTarget->Get_Line().fRPoint.fX;
//	float y2 = pTarget->Get_Line().fRPoint.fY;
//
//	//-	*_fY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;
//	*_fY = ((y2 - y1) / (x2 - x1))*(_pObj->Get_Info().fX - x1) + y1;
//
//	return true;
//}

bool CLineMgr::CollisionLinePlayer(float _fX, float _fY, float * _fXOut, float * _fYOut)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		// Obj is in the middle of a Line (X Axis)
		if (_fX >= iter->Get_Line().fLPoint.fX
			&& _fX < iter->Get_Line().fRPoint.fX)

			// Line has way bigger Y compared to Obj
			if (_fY > iter->Get_Line().fLPoint.fY + 20)
			{
				float fDistanceL = abs(_fX - iter->Get_Line().fLPoint.fX);
				float fDistanceR = abs(_fX - iter->Get_Line().fRPoint.fX);
				
				if (fDistanceL > fDistanceR)
					*_fXOut = iter->Get_Line().fRPoint.fX + 25;
				
				else
					*_fXOut = iter->Get_Line().fLPoint.fX - 25;
			}
			else
				pTarget = iter;
	}

	if (!pTarget)
		return false;

	float x1 = pTarget->Get_Line().fLPoint.fX;
	float y1 = pTarget->Get_Line().fLPoint.fY;

	float x2 = pTarget->Get_Line().fRPoint.fX;
	float y2 = pTarget->Get_Line().fRPoint.fY;

	*_fYOut = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;

	return true;
}

bool CLineMgr::CollisionLine(float	_fX, float _fY, float* _fYOut)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		// Obj is in the middle of a Line (X Axis)
		if (_fX >= iter->Get_Line().fLPoint.fX
			&& _fX < iter->Get_Line().fRPoint.fX)

			// Line has way bigger Y compared to Obj
			if (_fY > iter->Get_Line().fLPoint.fY + 20 )
				return false;
			else
				pTarget = iter;	
	}

	if (!pTarget)
		return false;

	float x1 = pTarget->Get_Line().fLPoint.fX;
	float y1 = pTarget->Get_Line().fLPoint.fY;

	float x2 = pTarget->Get_Line().fRPoint.fX;
	float y2 = pTarget->Get_Line().fRPoint.fY;

	*_fYOut = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;

	return true;
}


CLine* CLineMgr::CollisionLine_Bullet(float _fX, float * _OutY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		// Bullet is in the middle of a line
		// (X Axis) 
		if (_fX >= iter->Get_Line().fLPoint.fX && _fX < iter->Get_Line().fRPoint.fX)
			pTarget = iter;
	}

	if (!pTarget)
		return nullptr;

	float x1 = pTarget->Get_Line().fLPoint.fX;
	float y1 = pTarget->Get_Line().fLPoint.fY;

	float x2 = pTarget->Get_Line().fRPoint.fX;
	float y2 = pTarget->Get_Line().fRPoint.fY;

	*_OutY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;

	return pTarget;
}



bool CLineMgr::CollisionFlag(RECT rc)
{
	if (m_Flaglist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Flaglist)
	{
		/*if (iter->Get_typeID() == FLAG_LINE)
			return true;*/

		if (rc.right >= iter->Get_Line().fLPoint.fX
			&& rc.left < iter->Get_Line().fRPoint.fX)
		{

			pTarget = iter;
			return true;
		}
	}

	if (!pTarget)
		return false;

	// Á÷¼±ÀÇ ¹æÁ¤½Ä 
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	//float x1 = pTarget->Get_Line().fLPoint.fX;
	//float y1 = pTarget->Get_Line().fLPoint.fY;

	//float x2 = pTarget->Get_Line().fRPoint.fX;
	//float y2 = pTarget->Get_Line().fRPoint.fY;

	//*_fY = ((y2 - y1) / (x2 - x1))*(rc.right - x1) + y1;

	return true;
}

void CLineMgr::Save_File(void)
{
	HANDLE hFile = CreateFile(L"../Data/SaveTemp/Line.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save Player", L"Error", MB_OK);
		return;
	}

	DWORD	dwByte = 0;
	DWORD dwTypeByte = 0;

	/*for (size_t i = 0; i < LINE_END ; ++i)
	{*/
		for (auto& iter : m_Linelist)
		{
			WriteFile(hFile, &(iter->Get_Line()), sizeof(LINE), &dwByte, nullptr);
			WriteFile(hFile, &(static_cast<CLine*>(iter)->Get_typeID()), sizeof(int), &dwTypeByte, nullptr);
		}

		for (auto& iter : m_Flaglist)
		{
			WriteFile(hFile, &(iter->Get_Line()), sizeof(LINE), &dwByte, nullptr);
			WriteFile(hFile, &(static_cast<CLine*>(iter)->Get_typeID()), sizeof(int), &dwTypeByte, nullptr);
		}
	//}

	CloseHandle(hFile);
}

void CLineMgr::Load_File(int _iStage)
{
	HANDLE	hFile = nullptr;
	DWORD	dwByte = 0;
	LINE	tInfo{};
	DWORD	dwTypeByte = 0;
	int		iDest = 0;
	LINE_TYPE typeTemp = LINE_END;

	switch (_iStage)
	{
	case 1:
		hFile = CreateFile(L"../Data/Save1/Line.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Line", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		tInfo = {};
		dwByte = 0;
		iDest = 0;
		dwTypeByte = 0;
		typeTemp = LINE_END;

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
			ReadFile(hFile, &iDest, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iDest)
			{
			case NORMAL_LINE:
				m_Linelist.push_back(new CLine(tInfo));
				m_Linelist.back()->Set_typeID(NORMAL_LINE);
				break;
			case FLAG_LINE:
				m_Flaglist.push_back(new CLine(tInfo));
				m_Flaglist.back()->Set_typeID(FLAG_LINE);
				break;
			}

		}

		CloseHandle(hFile);
		return;
	case 2:
		hFile = CreateFile(L"../Data/Save2/Line.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Line", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		tInfo = {};
		dwByte = 0;
		iDest = 0;
		dwTypeByte = 0;
		typeTemp = LINE_END;

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
			ReadFile(hFile, &iDest, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iDest)
			{
			case NORMAL_LINE:
				m_Linelist.push_back(new CLine(tInfo));
				m_Linelist.back()->Set_typeID(NORMAL_LINE);
				break;
			case FLAG_LINE:
				m_Flaglist.push_back(new CLine(tInfo));
				m_Flaglist.back()->Set_typeID(FLAG_LINE);
				break;
			}

		}

		CloseHandle(hFile);
		return;
	case 3:
		hFile = CreateFile(L"../Data/Save3/Line.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Line", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		tInfo = {};
		dwByte = 0;
		iDest = 0;
		dwTypeByte = 0;
		typeTemp = LINE_END;

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
			ReadFile(hFile, &iDest, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iDest)
			{
			case NORMAL_LINE:
				m_Linelist.push_back(new CLine(tInfo));
				m_Linelist.back()->Set_typeID(NORMAL_LINE);
				break;
			case FLAG_LINE:
				m_Flaglist.push_back(new CLine(tInfo));
				m_Flaglist.back()->Set_typeID(FLAG_LINE);
				break;
			}

		}

		CloseHandle(hFile);
		return;
	case 4:
		hFile = CreateFile(L"../Data/Save4/Line.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Line", L"Error", MB_OK);
			return;
		}

		dwByte = 0;
		tInfo = {};
		dwByte = 0;
		iDest = 0;
		dwTypeByte = 0;
		typeTemp = LINE_END;

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
			ReadFile(hFile, &iDest, sizeof(int), &dwTypeByte, nullptr);

			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iDest)
			{
			case NORMAL_LINE:
				m_Linelist.push_back(new CLine(tInfo));
				m_Linelist.back()->Set_typeID(NORMAL_LINE);
				break;
			case FLAG_LINE:
				m_Flaglist.push_back(new CLine(tInfo));
				m_Flaglist.back()->Set_typeID(FLAG_LINE);
				break;
			}
		}

		CloseHandle(hFile);
		return;
	}
}

void CLineMgr::Add_FlagLine(float _fX, float _fY, float flagBoxX, float flagBoxY)
{
		m_tLinePoint[LEFT].fX = _fX;
		m_tLinePoint[LEFT].fY = _fY;
	
		m_tLinePoint[RIGHT].fX = flagBoxX;
		m_tLinePoint[RIGHT].fY = flagBoxY;

		m_Linelist.push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));
		m_Linelist.back()->Set_typeID(FLAG_LINE);
}

