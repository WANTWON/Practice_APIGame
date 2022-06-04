#pragma once

#include "Item.h"

class CStar : public CItem
{
public:
	CStar();
	virtual ~CStar();

	void Initialize() override;
	void Release() override;

	// 프레임마다 실행되는 함수 
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;

private:
	void Animate() override;
};

