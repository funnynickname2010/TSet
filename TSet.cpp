#include "TSet.h"

TSet::TSet(unsigned int n)
{
	indicator_vector.ChangeSize(n);
	size = n;
}

TSet::TSet(TSet& obj2)
{
	indicator_vector = obj2.indicator_vector;
	size = obj2.size;
}

TSet::TSet(BitField& obj2)
{
	indicator_vector = obj2;
	size = obj2.used_bits;
}

TSet::operator BitField()
{
	BitField result(indicator_vector);
	return result;
}

void TSet::Include(unsigned int index)
{
	indicator_vector.TurnOn(index);
}

void TSet::Exclude(unsigned int index)
{
	indicator_vector.TurnOff(index);
}

bool TSet::CheckIfBelongs(unsigned int index)
{
	return indicator_vector.CheckState(index);
}

TSet TSet::operator+(TSet& obj2)
{
	unsigned int result_size;

	if (size > obj2.size)
	{
		result_size = size;
	}
	else
	{
		result_size = obj2.size;
	}

	TSet result(result_size);

	for (int i = 0; i < result_size; i++)
	{
		if (this->CheckIfBelongs(i) || obj2.CheckIfBelongs(i))
		{
			result.Include(i);
		}
	}

	return result;
}

TSet TSet::operator~()
{
	TSet result(size);

	for (int i = 0; i < result.size; i++)
	{
		if (indicator_vector.CheckState(i))
		{
			result.Exclude(i);
		}
		else
		{
			result.Include(i);
		}
	}

	return result;
}

TSet TSet::operator*(TSet& obj2)
{
	unsigned int result_size;

	if (size < obj2.size)
	{
		result_size = size;
	}
	else
	{
		result_size = obj2.size;
	}

	TSet result(result_size);

	for (int i = 0; i < result_size; i++)
	{
		if (this->CheckIfBelongs(i) && obj2.CheckIfBelongs(i))
		{
			result.Include(i);
		}
	}
	
	return result;
}

std::istream& operator>>(std::istream& is, TSet& st)
{
	if (is.peek() == '\n')
	{
		is.ignore();
	}

	std::string input;
	std::getline(is, input);
	std::istringstream inps(input);

	if (inps.peek() == '{')
	{
		inps.ignore();
	}

	for (int i = 0; i < st.size; i++)
	{
		if (i != 0)
		{
			if (!(inps.get() == ','))
			{
				// Error handling: Failed to extract comma
				is.setstate(std::ios::failbit);
				break;
			}
		}

		unsigned int temp;

		if (!(inps >> temp))
		{
			// Error handling: Failed to extract vector element
			is.setstate(std::ios::failbit);
			break;
		}
		else
		{
			st.Include(temp);
		}
	}

	if (inps.peek() == ' ')
	{
		inps.ignore(); // Skipping the space before ')' if there's one
	}

	if (inps.peek() == '}')
	{
		inps.ignore();
	}

	if (is.rdstate() == std::ios::failbit)
	{
		std::cout << "//////INPUT ERROR\n";

		for (int i = 0; i < st.size; i++)
		{
			st.Exclude(i);
		}
	}

	// Clear any error flags that may have been set on the stream
	is.clear();

	return is;
}

std::ostream& operator <<(std::ostream& os, const TSet& vec)
{
	os << "{" << vec.val[0];

	for (int i = 1; i < vec.size; i++)
	{
		os << ", " << vec.val[i];
	}

	os << ")";
	return os;
}