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

public:
	const bool	Get_Check(void) const { return m_bCheck; }


public:
	void		Set_Check(bool _bCheck) { m_bCheck = _bCheck; }

private:
	OBJ_LIST m_ObjID;
	bool	m_bCheck;

};

