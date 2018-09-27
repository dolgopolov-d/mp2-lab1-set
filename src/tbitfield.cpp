// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include <string>
#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = len / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
		for (int i = 0; i <= MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw "Error";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0)
	{
		int tmp = n / (sizeof(TELEM) * 8);
		return tmp;
	}
	else
		throw "Error";
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	int pos = n % (sizeof(TELEM) * 8);
	TELEM tmp = mask << pos;
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	}
	else
		throw "Error";
}
void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		int pos = n % (sizeof(TELEM) * 8);
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] << pos;
		pMem[GetMemIndex(n)] = 0;
	}
	else
		throw "Error";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
	{
		int tmp;
		tmp = pMem[GetMemIndex(n)] >> (GetMemIndex(n) & 1);
		return tmp;
	}
	else 
		throw "Error";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete[] this->pMem;
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[bf.MemLen];
	for (int i = 0; i <= bf.MemLen; i++)
		this->pMem[i] = bf.pMem[i]; 
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (this->BitLen != bf.BitLen)
		return 0;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
			if (this->pMem[i] != bf.pMem[i])
				return 0;
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (this->BitLen != bf.MemLen)
		return 1;
	else
		for (int i = 0; i < bf.MemLen; i++)
			if (this->pMem[i] != bf.pMem[i])
				return 1;
			else
				return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (this->BitLen == bf.BitLen)
	{
		for (int i = 0; i < this->MemLen; i++)
			this->pMem[i] = this->pMem[i] | bf.pMem[i];
		return *this;
	}
	if (this->BitLen != bf.BitLen)
	{
		if (this->BitLen > bf.BitLen)
		{
			TBitField tmp(this->BitLen);
			if (this->MemLen < bf.MemLen)
			{
				for (int i = 0; i < this->MemLen; i++)
					tmp.pMem[i] = (this->pMem[i] | bf.pMem[i]);
				return tmp;
			}
			else
			{
				for (int i = 0; i < bf.MemLen; i++)
					tmp.pMem[i] = (this->pMem[i] | bf.pMem[i]);
				return tmp;
			}
				
		}
		if (this->BitLen < bf.BitLen)
		{
			TBitField tmp(bf.BitLen);
			if (this->MemLen < bf.MemLen)
			{
				for (int i = 0; i < this->MemLen; i++)
					tmp.pMem[i] = (this->pMem[i] | bf.pMem[i]);
				return tmp;
			}
			else
			{
				for (int i = 0; i < bf.MemLen; i++)
					tmp.pMem[i] = (this->pMem[i] | bf.pMem[i]);
				return tmp;
			}
				
		}
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (this->BitLen == bf.BitLen)
	{
		for (int i = 0; i < this->MemLen; i++)
			this->pMem[i] = this->pMem[i] & bf.pMem[i];
		return *this;
	}
	if (this->BitLen != bf.BitLen)
	{
		if (this->BitLen > bf.BitLen)
		{
			TBitField tmp(this->BitLen);
			if (this->MemLen < bf.MemLen)
			{
				for (int i = 0; i < this->MemLen; i++)
					tmp.pMem[i] = (this->pMem[i] & bf.pMem[i]);
				return tmp;
			}
			else
			{
				for (int i = 0; i < bf.MemLen; i++)
					tmp.pMem[i] = (this->pMem[i] & bf.pMem[i]);
				return tmp;
			}

		}
		if (this->BitLen < bf.BitLen)
		{
			TBitField tmp(bf.BitLen);
			if (this->MemLen < bf.MemLen)
			{
				for (int i = 0; i < this->MemLen; i++)
					tmp.pMem[i] = (this->pMem[i] & bf.pMem[i]);
				return tmp;
			}
			else
			{
				for (int i = 0; i < bf.MemLen; i++)
					tmp.pMem[i] = (this->pMem[i] & bf.pMem[i]);
				return tmp;
			}

		}
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(this->BitLen);
	for (int i = 0; i < this->BitLen; i++)
		if (this->GetBit(i) == 0)
			tmp.SetBit(i);
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{	
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}