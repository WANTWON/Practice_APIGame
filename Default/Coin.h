#pragma once

#include "Item.h"

class CCoin : public CItem
{
public:
	CCoin();
	virtual ~CCoin();
	
	void Initialize() override;
	void Release() override;

	// 프레임마다 실행되는 함수 
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;

private:
	void Animate() override;
};

