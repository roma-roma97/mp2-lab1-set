// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

//// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.GetMaxPower()) 
{
	MaxPower=s.MaxPower;
	BitField = s.BitField;
}
//
//// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}
//
TSet::operator TBitField()
{
	return BitField;
}
//
int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}
//
int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem) == 1)
		return 1;
	else
		return 0;
}
//
void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower)
		throw(Elem);
	BitField.SetBit(Elem);
}
//
void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem<0 || Elem>MaxPower)
		throw(Elem);
	BitField.ClrBit(Elem);
}
//
//// теоретико-множественные операции
//
TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (&s == this)
		return *this;
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	int flag = 1;
	if (MaxPower != s.GetMaxPower())
		flag = 0;
	else
		if (BitField != s.BitField)
			flag = 0;
	return flag;
}
//
int TSet::operator!=(const TSet &s) const // сравнение
{
	int flag = 0;
	if (MaxPower != s.GetMaxPower())
		flag = 1;
	else
		if (BitField == s.BitField)
			flag = 0;
		else
			flag = 1;
	return flag;
}
//
TSet TSet::operator+(const TSet &s) // объединение
{
	int size = MaxPower;
	if (MaxPower < s.MaxPower)
		size = s.MaxPower;
	TSet Union(size);
	Union.BitField=BitField|s.BitField;
	return Union;
}
//
TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem >= MaxPower)
		throw(Elem);
	TSet Union(*this);
	//BitField.SetBit(Elem);
	//Union.BitField=BitField;
	Union.BitField.SetBit(Elem);
	return Union;
}
//
TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 || Elem >= MaxPower)
		throw(Elem);
	TSet Difference(MaxPower);
	Difference.BitField = BitField;
	Difference.BitField.ClrBit(Elem);
	return Difference;
}
//
TSet TSet::operator*(const TSet &s) // пересечение
{
	int size = MaxPower;
	if (MaxPower < s.MaxPower)
		size = s.MaxPower;
	TSet TMP(size);
	TMP.BitField = BitField & s.BitField;
	return TMP;
}
//
TSet TSet::operator~(void) // дополнение
{
	TSet TMP(MaxPower);
	TMP.BitField = ~BitField;
	return TMP;
}
//
//// перегрузка ввода/вывода
//
istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
