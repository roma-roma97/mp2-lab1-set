// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
		throw(len);
	BitLen = len;
	MemLen = (BitLen / 32) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < bf.MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / 32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
		throw(n);
	TELEM Mask = 1;
	TELEM position = n % 32;
	Mask = Mask << position;
	return Mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	TELEM tmp = 1;
	if ((n < 0) || (n >= BitLen))
		throw(n);
	pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
	TELEM tmp = 1;
	if ((n < 0) || (n >= BitLen))
		throw(n);
	pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw(n);
	if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == GetMemMask(n))
		return 1;
	else
		return 0;
}

// битовые операции
//
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf == this)
		return *this;
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		delete[]pMem;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < bf.MemLen; i++)
		if (pMem[i] != bf.pMem[i])
		{
			return 0;
		}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	for (int i = 0; i < bf.MemLen; i++)
		if (pMem[i] != bf.pMem[i])
		{
			return 1;
		}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField Temp(len);
	for (int i = 0; i < MemLen; i++)
		Temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Temp.pMem[i] |= bf.pMem[i];
	return Temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField Temp(len);
	for (int i = 0; i < MemLen; i++)
		Temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Temp.pMem[i] &= bf.pMem[i];
	return Temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField TMP(BitLen);
	TMP = *this;
	for (int i = 0; i < BitLen; i++)
		TMP.pMem[GetMemIndex(i)] ^= GetMemMask(i);
	return TMP;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int count = 0;
	string str;
	str = getchar();
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
			count++;
		if (str[i] == '1')
		{

			bf.SetBit(i - count);
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}
