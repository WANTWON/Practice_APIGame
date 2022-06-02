#pragma once


template<typename T>
void Safe_Delete(T& temp)
{
	if (temp)
	{
		delete temp;
		temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}