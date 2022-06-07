#include "stdafx.h"
#include "CollisionMgr.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"
#include "Define.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

RECT rc = {};

int CCollisionMgr::Collision_Rect(list<CObj*> Sour, list<CObj*> Dest)
{
	int iScore = 0;
	for (auto& iter = Sour.begin(); iter != Sour.end(); )
	{
		int iter_count = 0;
		for (auto& Monster_iter = Dest.begin(); Monster_iter != Dest.end(); )
		{
			if ((Dest.size() != 0) && (IntersectRect(&rc, &((*iter)->Get_Rect()), &((*Monster_iter)->Get_Rect()))))
			{
				(*iter)->Set_Dead(true);
				dynamic_cast<CMonster*>(*Monster_iter)->Be_Attacked();
				iScore += rand() % 10 + 5;
			}
			Monster_iter++;
		}
		iter++;
	}
	return iScore;
}


int CCollisionMgr::Collision_Bullet(CObj* _This, list<CObj*> _Bullet)
{
	RECT rt{};
	int iScore = 0;

	if (OBJ_PLAYER == _This->Get_ID()) //When the player gets hit by a bullet,
	{
		for (auto& iter : _Bullet)
		{
			if (OBJ_MONSTER == iter->Get_ID() && IntersectRect(&rt, &(_This->Get_Rect()), &(iter->Get_Rect())))	//When a bullet is a Monster's bullet,
			{

				(iter)->Set_Dead(true, true);
				if (dynamic_cast<CPlayer*>(_This)->Get_Buff())
				{
					if (dynamic_cast<CPlayer*>(_This)->Get_ActiveBuff() != ITEM_STAR)
						dynamic_cast<CPlayer*>(_This)->Remove_Buff(dynamic_cast<CPlayer*>(_This)->Get_ActiveBuff());
				}
				else
					dynamic_cast<CPlayer*>(_This)->Set_Dead_Count();

			}
		}
		return iScore;
	}
	else if (OBJ_MONSTER == _This->Get_ID()) //When the Monster gets hit by a bullet,
	{
		for (auto& iter : _Bullet)
		{
			if (OBJ_PLAYER == iter->Get_ID() && IntersectRect(&rt, &(_This->Get_Rect()), &(iter->Get_Rect())))	//When a bullet is a Player's bullet,
			{
				(iter)->Set_Dead(true, true);
				dynamic_cast<CMonster*>(_This)->Be_Attacked();
				iScore += rand() % 10 + 5;
			}
		}
		return iScore;
	}
	else if (BLOCK_NORMAL == _This->Get_ID())
	{
		for (auto& iter : _Bullet)
		{
			if (IntersectRect(&rt, &(_This->Get_Rect()), &(iter->Get_Rect())))	//When a bullet is a Player's bullet,
			{
				(iter)->Set_Dead(true, true);
			}

		}

	}


	return iScore;
}

void CCollisionMgr::Collision_Rect_Ex(list<CObj*> _Sour, list<CObj*> _Dest)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float fWidth = 0.f;
			float fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				if (fWidth > fHeight)  //상하 충돌
				{
					if (Dest->Get_Info().fY > Sour->Get_Info().fY)
					{
						Sour->Set_PosY(-fHeight);
					}
					else
					{
						Sour->Set_PosY(fHeight);
					}

				}
				else //좌우 충돌 
				{
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
					{
						Sour->Set_PosX(-fWidth);
					}
					else
					{
						Sour->Set_PosX(fWidth);
					}
				}

			}

		}
	}
}

int CCollisionMgr::Check_Rect(CObj* Sour, CObj* Dest, float* _pX, float* _pY)
{
	float fWidth = abs(Sour->Get_Info().fX - Dest->Get_Info().fX);
	float fHeight = abs(Sour->Get_Info().fY - Dest->Get_Info().fY);

	float fRadiusX = (Sour->Get_Info().fCX + Dest->Get_Info().fCX)*0.5f;
	float fRadiusY = (Sour->Get_Info().fCY + Dest->Get_Info().fCY)*0.5f;

	if ((fWidth <= fRadiusX) && (fHeight <= fRadiusY))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;
		return true;
	}
	else
		return false;
}

int CCollisionMgr::Step_on_Mushroom(list<CObj*> _Sour, list<CObj*> _Dest)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float fWidth = 0.f;
			float fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				if (fWidth > fHeight)  //상하 충돌
				{
					if (true == dynamic_cast<CPlayer*>(Sour)->Get_Count())
						continue;

					// Up
					if (Dest->Get_Info().fY >= Sour->Get_Info().fY)
					{
						Sour->Set_PosY(-fHeight);
						dynamic_cast<CMonster*>(Dest)->Be_Attacked();
						dynamic_cast<CPlayer*>(Sour)->Set_StepMonster(true);
						dynamic_cast<CPlayer*>(Sour)->Set_JumpingTime();
						return rand() & 50 + 10;
					}
					// Down
					else
					{
						CPlayer* pPlayer = dynamic_cast<CPlayer*>(Sour);

						// Has Buff
						if (pPlayer->Get_ActiveBuff() != ITEM_END)
						{
							if(dynamic_cast<CMonster*>(Dest)->Get_Hp() < 3)
								dynamic_cast<CMonster*>(Dest)->Be_Attacked();

							// Remove Buff if not Star
							if (pPlayer->Get_ActiveBuff() != ITEM_STAR)
								pPlayer->Remove_Buff(pPlayer->Get_ActiveBuff());
						}
						// Has no Buff
						else
							pPlayer->Set_Dead_Count();
					}
				}
				else //좌우 충돌 
				{
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(Sour);

					// Has Buff
					if (pPlayer->Get_ActiveBuff() != ITEM_END)
					{
						if (dynamic_cast<CMonster*>(Dest)->Get_Hp() < 3)
							dynamic_cast<CMonster*>(Dest)->Set_Dead(true);

						// Remove Buff if not Star
						if (pPlayer->Get_ActiveBuff() != ITEM_STAR)
							pPlayer->Remove_Buff(pPlayer->Get_ActiveBuff());
					}
					// Has no Buff
					else
						pPlayer->Set_Dead_Count();

					/*if (true == dynamic_cast<CPlayer*>(Sour)->Get_Buff())
					{
						dynamic_cast<CMonster*>(Dest)->Be_Attacked();
						pPlayer->Get_Active(true);
					}
					else
						dynamic_cast<CPlayer*>(Sour)->Set_Dead_Count();*/
				}
			}
		}
	}
	return 0;
}

DIRECTION CCollisionMgr::Col_ReturnDir(list<CObj*> _Sour, list<CObj*> _Dest)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float fWidth = 0.f;
			float fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				float fX = Sour->Get_Info().fX - Dest->Get_Info().fX;
				float fY = Sour->Get_Info().fY - Dest->Get_Info().fY;

				float fR = sqrtf((fX * fX) + (fY * fY));

				float fAngle = (180 / PI) * acos(fX / fR);
				if (Sour->Get_Info().fY <= Dest->Get_Info().fY)
					fAngle = 360 + (-1.f * fAngle);

				if (fAngle > 315.f || fAngle <= 45.f)
				{
					return DIR_RIGHT;
				}
				else if (fAngle > 45.f && fAngle <= 135.f)
				{
					return DIR_DOWN;
				}
				else if (fAngle > 135.f && fAngle <= 225.f)
				{
					return DIR_LEFT;
				}
				else if (fAngle > 225.f && fAngle <= 315.f)
				{
					return DIR_UP;
				}
			}
		}
	}
}


DIRECTION CCollisionMgr::Col_ReturnDir(list<CObj*> _Sour, CObj* _Dest)
{
	for (auto& Sour : _Sour)
	{
		float fWidth = 0.f;
		float fHeight = 0.f;

		if (Check_Rect(_Dest, Sour, &fWidth, &fHeight))
		{
			float fX = Sour->Get_Info().fX - _Dest->Get_Info().fX;
			float fY = Sour->Get_Info().fY - _Dest->Get_Info().fY;

			float fR = sqrtf((fX * fX) + (fY * fY));

			float fAngle = (180 / PI) * acos(fX / fR);
			if (Sour->Get_Info().fY <= _Dest->Get_Info().fY)
				fAngle = 360 + (-1.f * fAngle);

			if (fAngle >= 316.f || fAngle < 44.f)
			{
				return DIR_RIGHT;
			}
			else if (fAngle >= 45.f && fAngle <= 134.f)
			{
				return DIR_DOWN;
			}
			else if (fAngle > 136.f && fAngle <= 224.f)
			{
				return DIR_LEFT;
			}
			else if (fAngle > 224.f && fAngle < 316.f)
			{
				return DIR_UP;
			}
		}
	}


	return DIR_END;
}


void CCollisionMgr::Collision_Item(CObj * Player, list<CObj*> Items)
{
	for (auto& item : Items)
	{
		float fWidth, fHeight = 0.f;

		if (Check_Rect(Player, item, &fWidth, &fHeight))
		{
			CPlayer* pPlayer = static_cast<CPlayer*>(Player);
			CItem* pItem = static_cast<CItem*>(item);

			// If Item is not a Coin
			if (pItem->Get_Type() != ITEM_COIN && pItem->Get_Type() != OBJ_COIN)
			{
				// Player has no Buff
				if (pPlayer->Get_ActiveBuff() == ITEM_END)
				{
					// Set Active Buff and Buff Time
					pPlayer->Set_ActiveBuff(pItem->Get_Type());
					pPlayer->Set_BuffTime(GetTickCount());
				}
				// Player already has Buff
				else
				{
					pPlayer->Remove_Buff(pPlayer->Get_ActiveBuff());

					// Set Active Buff and Buff Time
					pPlayer->Set_ActiveBuff(static_cast<CItem*>(item)->Get_Type());
					pPlayer->Set_BuffTime(GetTickCount());
				}
			}

			// Destroy Item
			item->Set_Dead(true);
		}
	}
}

bool CCollisionMgr::Col_EditorClick(CObj * _Mouse, CObj * _pObj)
{
	float fX = 0.f;
	float fY = 0.f;

	if (Check_Rect(_Mouse, _pObj, &fX, &fY))
	{
		return true;
	}

	return false;
}

int CCollisionMgr::Collision_Sphere(list<CObj*> Sour, list<CObj*> Dest)
{
	int iScore = 0;

	for (auto& Sour_iter = Sour.begin(); Sour_iter != Sour.end(); )
	{
		int iter_count = 0;
		for (auto& Dest_iter = Dest.begin(); Dest_iter != Dest.end(); )
		{
			if ((Dest.size() != 0) && (ChecK_Sphere(*Sour_iter, *Dest_iter)))
			{
				(*Sour_iter)->Set_Dead(true);
				(*Dest_iter)->Set_Dead(true);
				iScore += rand() % 10 + 5;
			}
			Dest_iter++;
		}
		Sour_iter++;
	}
	return iScore;
}

int CCollisionMgr::Collision_Coin(CObj* Player, list<CObj*> Items)
{
	

	for (auto& item : Items)
	{
		if (IntersectRect(&rc, &Player->Get_Rect(), &item->Get_Rect()))
		{
			CItem* _Item = dynamic_cast<CItem*>(item);

			if (_Item->Get_Type() == ITEM_COIN)
			{
				_Item->Set_Dead(true);
			}
		}
	}

	return 0;
}

bool CCollisionMgr::ChecK_Sphere(CObj* Sour, CObj* Dest)
{
	float fRadius = (Sour->Get_Info().fCX + Dest->Get_Info().fCX) * 0.5f; //두 원의 반지름을 더한 값

																		  //절대값을 씌워주는 함수
	float fWidth = fabs(Sour->Get_Info().fX - Dest->Get_Info().fX);
	float fHeight = fabs(Sour->Get_Info().fY - Dest->Get_Info().fY);

	float fDistance = sqrtf((fWidth* fWidth) + (fHeight*fHeight));

	if (fRadius >= fDistance)
		return true;
	else
		return false;
}