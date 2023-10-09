#include "TSet.h"
#include <string>
#include <sstream>

void InputRow(BitField& obj);
void OutputRow(BitField& obj);

void UnsignedIntCorrectInput(unsigned int& container, std::string str, int lower_bound, int upper_bound)
{
	do {
		std::cout << str;
		std::cin >> container;
	} while ((container > upper_bound) || (container < lower_bound));
}

void UnsignedIntCorrectInput(unsigned int& container, std::string str, int lower_bound, int upper_bound, int kstl)
{
	do {
		std::cout << str;
		std::cin >> container;
	} while ((container > upper_bound) || (container != 0 && container != 1));
}

void if_set_isnt_initialized(bool* set_created_array, int index, TSet& set_op)
{
	if (set_created_array[index] != 1)
	{
		unsigned int temp_size = 1;

		std::wcout << "Input size of the bitfield in bits: ";
		std::wcin >> temp_size;

		TSet temp_set(temp_size);
		set_op = temp_set;
		set_created_array[index] = 1;
	}
}

int Interface()
{
	int i = 0;
	std::cout << (i = (i + 1)) << ". Input set\n";
	std::cout << (i = (i + 1)) << ". Add/Remove an element from a set\n";
	std::cout << (i = (i + 1)) << ". Check if a number is in set\n";
	std::cout << (i = (i + 1)) << ". Test + operator\n";
	std::cout << (i = (i + 1)) << ". Test ~ operator\n";
	std::cout << (i = (i + 1)) << ". Test * operator\n";
	std::cout << (i = (i + 1)) << ". Print a set\n";
	std::cout << (i = (i + 1)) << ". Print menu\n";
	std::cout << (i = (i + 1)) << ". Exit\n";
	return i;
}

int main()
{
	TSet TSetArray[3];
	bool set_initialized[2];

	for (int i = 0; i < 2; i++)
	{
		set_initialized[i] = 0;
	}

	int option;
	int exit_option = Interface();

	do
	{
		std::cout << "\n////////////////////////////CHOOSE AN OPTION: ";
		std::cin >> option;

		switch (option)
		{
		case 1: //Change

			int which_set;

			std::cout << "\nDo you want to input set A or set B?\nA - 0\nB - 1\n";
			std::cin >> which_set;

			if_set_isnt_initialized(set_initialized, which_set, TSetArray[which_set]);

			std::cout << "\nPlease input the bitfield: ";

			std::cin >> TSetArray[which_set];

			break;

		case 2:
		{
			int which_set;
			int remove_or_add_option;

			std::cout << "\nDo you want to input set A or set B?\nA - 0\nB - 1\n";
			std::cin >> which_set;

			std::cout << "\nDo you want add or remove a number?\nRemove - 0\nAdd - 1\n";
			std::cin >> remove_or_add_option;

			if_set_isnt_initialized(set_initialized, which_set, TSetArray[which_set]);
			std::cin.clear();

			unsigned int number_set = 0;
			unsigned int value = 0;

			unsigned int zero_temp = 0;
			unsigned int two_temp = 0;

			if (remove_or_add_option == 1)
			{
				UnsignedIntCorrectInput(number_set, "\nInput a number: ", 0, (TSetArray[which_set].size));

				TSetArray[which_set].Include(number_set);
			}
			else if (remove_or_add_option == 0)
			{
				UnsignedIntCorrectInput(number_set, "\nInput a number: ", 0, (TSetArray[which_set].size));

				TSetArray[which_set].Exclude(number_set);
			}

			std::cout << TSetArray[which_set];

			break;
		}
		case 3:
		{
			int which_set;

			std::cout << "\nDo you want to check a number in set A or set B?\nA - 0\nB - 1\n\n";
			std::cin >> which_set;

			if_set_isnt_initialized(set_initialized, which_set, TSetArray[which_set]);

			unsigned int index = 0;

			UnsignedIntCorrectInput(index, "\nInput index: ", 0, TSetArray[which_set].indicator_vector.reserved_ints * 32);

			if (TSetArray[which_set].CheckIfBelongs(which_set))
			{
				std::cout << "The number belongs to the set\n";
			}
			else
			{
				std::cout << "The number does not belong to the set\n";
			}

			std::cout << TSetArray[which_set];

			break;
		}
		case 4:

			if_set_isnt_initialized(set_initialized, 0, TSetArray[0]);
			if_set_isnt_initialized(set_initialized, 1, TSetArray[1]);

			TSetArray[2] = (TSetArray[0] + TSetArray[1]);

			std::cout << TSetArray[2];
			break;

		case 5:

			std::cout << "\nDo you want to use set A or set B?\nA - 0\nB - 1\n";
			std::cin >> which_set;

			if_set_isnt_initialized(set_initialized, which_set, TSetArray[which_set]);

			TSetArray[2] = ~TSetArray[which_set];

			std::cout << TSetArray[2];
			break;

		case 6:

			if_set_isnt_initialized(set_initialized, 0, TSetArray[0]);
			if_set_isnt_initialized(set_initialized, 1, TSetArray[1]);

			TSetArray[2] = (TSetArray[0] * TSetArray[1]);

			std::cout << TSetArray[2];
			break;

		case 7:
		{

			int which_set = 0;

			std::cout << "\nWhich set do you want printed?\nA - 0\nB - 1\n";
			std::cin.ignore();
			std::cin >> which_set;

			if (set_initialized[which_set])
			{
				std::cout << TSetArray[which_set];
			}
			else
			{
				std::cout << "Please input the set first\n";
			}

			break;
		}
		case 8:

			std::cout << "\n";
			Interface();

			break;
		}

	} while (option != exit_option || option < 1 || option > exit_option);
}


/*
void InputRow(BitField& obj)
{
	char* input;
	input = new char[obj.reserved_ints * 32];
	std::cin.clear();
	std::cin >> input;
	obj.used_bits = 0;

	for (unsigned int i = 0; i < (obj.reserved_ints * 32); i++)
	{
		obj.TurnOff(i);
	}

	for (unsigned int i = 0; i < (obj.reserved_ints * 32); i++)
	{
		if (input[i] == '1')
		{
			obj.TurnOn(i);
			obj.used_bits += 1;
		}
		else if (input[i] == '0')
		{
			obj.TurnOff(i);
			obj.used_bits += 1;
		}
		else
		{
			break;
		}
	}

	delete[] input;
}

void OutputRow(BitField& obj)
{
	int* output = new int[obj.reserved_ints * 32];

	for (unsigned int i = 0; i < obj.used_bits; i++)
	{
		output[i] = (obj.CheckState(i));
	}

	std::cout << "\n";

	for (unsigned int i = 0; i < obj.used_bits; i++)
	{
		std::cout << output[i];
	}

	std::cout << "\n";

	delete[] output;
}*/