#pragma once
#include "Block.h"
class CCoinBlock :
	public CBlock
{
public:
	CCoinBlock();
	~CCoinBlock();

public:
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Release(void)		override;
	virtual void Render(HDC hDC)	override;

private:




};

