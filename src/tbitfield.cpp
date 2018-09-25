// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

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
	if ((n >= 0) && (n <= BitLen))
	{
		int nmbr = n / (sizeof(TELEM) * 8);
		pMem[nmbr] = (pMem[nmbr] | GetMemMask(n));
	}
	else
		throw "Error";
}
void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n <= BitLen))
	{
		int nmbr = n / (sizeof(TELEM) * 8);
		int pos = n % (sizeof(TELEM) * 8);
		pMem[nmbr] = pMem[nmbr] << pos;
		pMem[nmbr] = 0;
	}
	else
		throw "Error";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n <= BitLen))
	{
			int num = (int)(n / (sizeof(TELEM) * 8)); 		
			if ((pMem[num] & GetMemMask(n)) == GetMemMask(n))
				return 1;
			else
				return 0;
	}
	else 
		throw "Error";
}

// битовые операции
/*
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
*/