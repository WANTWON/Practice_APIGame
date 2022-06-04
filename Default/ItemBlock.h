#pragma once
#include "Block.h"
class CItemBlock :
	public CBlock
{
public:
	CItemBlock();
	~CItemBlock();

public:
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Release(void)		override;
	virtual void Render(HDC hDC)	override;

private:



};

