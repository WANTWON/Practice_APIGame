#pragma once
#include "Block.h"

class CFlagBlock :	public CBlock
{
public:
	CFlagBlock();
	~CFlagBlock();
public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Release(void)		override;
	virtual void Render(HDC hDC)	override;
public:
	bool Get_Number(void) { return m_bNumber; }
	void Set_Number(bool _Number) { m_bNumber = _Number; }
	void Set_Down(int Down) { m_iDown = Down; }
private:
	bool m_bNumber;
	int m_iDown;
	float m_fCount;
};

