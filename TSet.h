#pragma once
#include "BitField.h"
#include <iostream>
#include <string>
#include <sstream>

class TSet
{
public:

	BitField indicator_vector;
	unsigned int size = 0;

	explicit TSet(unsigned int n);
	TSet(TSet& obj2);
	TSet(BitField& obj2);
	TSet();

	operator BitField();

	void Include(unsigned int index);
	void Exclude(unsigned int index);
	bool CheckIfBelongs(unsigned int index);

	TSet operator +(TSet& obj2);
	TSet operator ~();
	TSet operator *(TSet& obj2);
	friend std::istream& operator >>(std::istream& is, TSet& st);
	friend std::ostream& operator <<(std::ostream& os, const TSet& st);
};