#pragma once
#include "Obj.h"
class CBlockNull :
	public CObj
{
public:
	CBlockNull();
	~CBlockNull();

public:
	void	Initialize(void)  override;
	int		Update(void) override;
	void	Late_Update(void) override;
	void	Release(void) override;
	void	Render(HDC hDC) override;



};

