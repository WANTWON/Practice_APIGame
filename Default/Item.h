#pragma once

#include "Obj.h"

class CItem : public CObj
{
public:
	CItem();
	virtual ~CItem();

	void Initialize() override;
	void Release() override;
	
	// 프레임마다 실행되는 함수 
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;

	// 게터와 세터
	int Get_Type() { return m_Type; }
	void Set_Type(ITEM_TYPE type) { m_Type = type; }

private:
	ITEM_TYPE m_Type;
	
	void Render_Coin(HDC hdc);
	void Render_Mushroom(HDC hdc);
	void Render_Star(HDC hdc);
	void Render_Flower(HDC hdc);
};