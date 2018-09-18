// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw(len);
	BitLen = abs(len);
	if (BitLen == 0)
		BitLen++;
	MemLen = (BitLen / 32)+1;
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
	if (n == 0)
		return ((BitLen - n) / 32) - 1;
	else
		return (BitLen - n) / 32;

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM a = 1;
	if (n > 31)
		a << (n % 32);
	else
		a << n;
	return a;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	TELEM tmp = 1;
	if ((n < 0)||(n>BitLen))
		throw(n);
	if (n == 0)
		pMem[((BitLen - n) / 32) - 1] |= (tmp << (n % 32));
	if(n>31)
		pMem[(BitLen - n) / 32] |= (tmp << (n % 32));
	else
		pMem[(BitLen - n) / 32] |= (tmp << n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
	TELEM tmp = 1;
	if ((n < 0)||(n>BitLen))
		throw(n);
	if (n == 0)
		pMem[((BitLen - n) / 32) - 1] ^= (tmp << (n % 32));
	else
		pMem[(BitLen - n) / 32] ^= (tmp << (n % 32));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0)||(n>BitLen))
		throw(n);
	TELEM tmp = pMem[(BitLen - n) / 32];
	tmp &= GetMemMask(n);
	/*if (n > 0)*/
	if (tmp != 0)
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
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int flag = 1;
	for (TELEM i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
		{
			flag = 0;
			break;
		}
	return flag;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int flag = 0;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
		{
			flag = 1;
			break;
		}
	return flag;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField Temp(BitLen);
	for (int i = 0; i < MemLen; i++)
		Temp.pMem[i] = (pMem[i] | bf.pMem[i]);
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
	for (int i = 0; i < MemLen; i++)
		~pMem[i];
	return *this;
}

// ввод/вывод

//istream &operator>>(istream &istr, TBitField &bf) // ввод
//{
//}
//
//ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
//{
//}
