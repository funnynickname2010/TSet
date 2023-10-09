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

void if_field_isnt_initialized(bool* set_created_array, int index, TSet& set_op)
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
	TSet TSetArray[2];
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

			if_field_isnt_initialized(set_initialized, which_set, TSetArray[which_set]);

			std::cout << "\nPlease input the bitfield: ";

			InputRow(TSetArray[which_set]);

			break;

		case 2:
		{
			int which_bitfield;

			std::cout << "\nDo you want to input bitfield A or bitfield B?\nA - 0\nB - 1\n";
			std::cin >> which_bitfield;

			if_field_isnt_initialized(set_initialized, which_bitfield, TSetArray[which_bitfield]);
			std::cin.clear();

			unsigned int index = 0;
			unsigned int value = 0;

			unsigned int zero_temp = 0;
			unsigned int two_temp = 0;
			UnsignedIntCorrectInput(index, "\nInput index: ", 0, (TSetArray[which_bitfield].reserved_ints * 32));

			value = !TSetArray[which_bitfield].CheckState(index);

			unsigned int temp_upper_bound_value = 2;
			UnsignedIntCorrectInput(value, "\nInput value: ", -1, temp_upper_bound_value, 0);

			if (value == 0)
			{
				TSetArray[which_bitfield].TurnOff(index);
			}
			else if (value == 1)
			{
				TSetArray[which_bitfield].TurnOn(index);
			}

			if (TSetArray[which_bitfield].used_bits <= index)
			{
				TSetArray[which_bitfield].used_bits = index + 1;
			}

			OutputRow(TSetArray[which_bitfield]);

			break;
		}
		case 3:
		{
			int which_bitfield;

			std::cout << "\nDo you want to check a bit in bitfield A or bitfield B?\nA - 0\nB - 1\n\n";
			std::cin >> which_bitfield;

			if_field_isnt_initialized(set_initialized, which_bitfield, TSetArray[which_bitfield]);

			unsigned int index = 0;

			UnsignedIntCorrectInput(index, "\nInput index: ", 0, TSetArray[which_bitfield].reserved_ints * 32);

			std::cout << "Bit with an index " << index << " equals to " << TSetArray[which_bitfield].CheckState(index) << std::endl;

			OutputRow(TSetArray[which_bitfield]);

			break;
		}
		case 4:

			unsigned int inpt;

			if_field_isnt_initialized(set_initialized, 0, TSetArray[0]);
			if_field_isnt_initialized(set_initialized, 1, TSetArray[1]);

			if (TSetArray[0].reserved_ints > TSetArray[1].reserved_ints)
			{
				TSetArray[2].ChangeSize(TSetArray[0].reserved_ints);
			}
			else
			{
				TSetArray[2].ChangeSize(TSetArray[1].reserved_ints);
			}

			TSetArray[2] = (TSetArray[0] | TSetArray[1]);

			OutputRow(TSetArray[2]);
			break;

		case 5:

			if_field_isnt_initialized(set_initialized, 0, TSetArray[0]);
			if_field_isnt_initialized(set_initialized, 1, TSetArray[1]);

			if (TSetArray[0].reserved_ints > TSetArray[1].reserved_ints)
			{
				TSetArray[2].ChangeSize(TSetArray[0].reserved_ints);
			}
			else
			{
				TSetArray[2].ChangeSize(TSetArray[1].reserved_ints);
			}

			TSetArray[2] = (TSetArray[0] & TSetArray[1]);

			OutputRow(TSetArray[2]);
			break;

		case 6:
		{

			int which_bitfield = 0;

			std::cout << "\nWhich bitfield do you want printed?\nA - 0\nB - 1\n";
			std::cin.ignore();
			std::cin >> which_bitfield;

			if (set_initialized[which_bitfield])
			{
				OutputRow(TSetArray[which_bitfield]);
			}
			else
			{
				std::cout << "Please input the bitfield first\n";
			}

			break;
		}
		case 7:

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