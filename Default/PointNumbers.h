#pragma once
class CPointNumbers
{
public:
	CPointNumbers();
	CPointNumbers(int iPoints, float fX, float fY);
	~CPointNumbers();

	void Release();

	// 프레임마다 실행되는 함수 
	int Update();
	void Late_Update();
	void Render(HDC hDC);

private:
	int m_iNumber;
	float m_fX;
	float m_fY;
	float m_fSpeed;
	float m_dwTime;
	bool m_bDead;
};

