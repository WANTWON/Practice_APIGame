#pragma once

#include "Item.h"

class CFlower : public CItem
{
public:
	CFlower();
	virtual ~CFlower();

	void Initialize() override;
	void Release() override;

	// 프레임마다 실행되는 함수 
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;

private:
	void Animate() override;
};

