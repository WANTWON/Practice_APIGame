#pragma once

#include "Include.h"

class CLine
{
public:
	CLine();
	~CLine();
	CLine(LINEPOINT& RightPoint, LINEPOINT& LeftPoint);

public:
	const LINE& Get_Line(void) { return m_tInfo; }
	void Render(HDC hDC);
	void Release(void);

private:
	LINE m_tInfo;
};

