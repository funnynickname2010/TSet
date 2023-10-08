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

void if_field_isnt_initialized(bool* field_created_array, int index, BitField& bitfield_op)
{
	if (field_created_array[index] != 1)
	{
		unsigned int temp_size = 1;

		std::wcout << "Input size of the bitfield in bits: ";
		std::wcin >> temp_size;

		bitfield_op.ChangeSize(temp_size);
		field_created_array[index] = 1;
	}
}

void Interface()
{
	std::cout << "1. Input a bitfitfield as a row\n";
	std::cout << "2. Change a single bit of a bitfield\n";
	std::cout << "3. Check state of a bit\n";
	std::cout << "4. Test | operator\n";
	std::cout << "5. Test & operator\n";
	std::cout << "6. Print the bitfield\n";
	std::cout << "7. Print menu\n";
	std::cout << "8. Exit\n";
}

int main()
{
	int option;
	int exit_option = 8;

	BitField BitFieldArray[3];

	bool field_initialized[2];

	for (int i = 0; i < 2; i++)
	{
		field_initialized[i] = 0;
	}

	Interface();

	do
	{
		std::cout << "\n////////////////////////////CHOOSE AN OPTION: ";
		std::cin >> option;

		switch (option)
		{
		case 1:

			int which_bitfield;

			std::cout << "\nDo you want to input bitfield A or bitfield B?\nA - 0\nB - 1\n";
			std::cin >> which_bitfield;

			if_field_isnt_initialized(field_initialized, which_bitfield, BitFieldArray[which_bitfield]);

			std::cout << "\nPlease input the bitfield: ";

			InputRow(BitFieldArray[which_bitfield]);

			break;

		case 2:
		{
			int which_bitfield;

			std::cout << "\nDo you want to input bitfield A or bitfield B?\nA - 0\nB - 1\n";
			std::cin >> which_bitfield;

			if_field_isnt_initialized(field_initialized, which_bitfield, BitFieldArray[which_bitfield]);
			std::cin.clear();

			unsigned int index = 0;
			unsigned int value = 0;

			unsigned int zero_temp = 0;
			unsigned int two_temp = 0;
			UnsignedIntCorrectInput(index, "\nInput index: ", 0, (BitFieldArray[which_bitfield].reserved_ints * 32));

			value = !BitFieldArray[which_bitfield].CheckState(index);

			unsigned int temp_upper_bound_value = 2;
			UnsignedIntCorrectInput(value, "\nInput value: ", -1, temp_upper_bound_value, 0);

			if (value == 0)
			{
				BitFieldArray[which_bitfield].TurnOff(index);
			}
			else if (value == 1)
			{
				BitFieldArray[which_bitfield].TurnOn(index);
			}

			if (BitFieldArray[which_bitfield].used_bits <= index)
			{
				BitFieldArray[which_bitfield].used_bits = index + 1;
			}

			OutputRow(BitFieldArray[which_bitfield]);

			break;
		}
		case 3:
		{
			int which_bitfield;

			std::cout << "\nDo you want to check a bit in bitfield A or bitfield B?\nA - 0\nB - 1\n\n";
			std::cin >> which_bitfield;

			if_field_isnt_initialized(field_initialized, which_bitfield, BitFieldArray[which_bitfield]);

			unsigned int index = 0;

			UnsignedIntCorrectInput(index, "\nInput index: ", 0, BitFieldArray[which_bitfield].reserved_ints * 32);

			std::cout << "Bit with an index " << index << " equals to " << BitFieldArray[which_bitfield].CheckState(index) << std::endl;

			OutputRow(BitFieldArray[which_bitfield]);

			break;
		}
		case 4:

			unsigned int inpt;

			if_field_isnt_initialized(field_initialized, 0, BitFieldArray[0]);
			if_field_isnt_initialized(field_initialized, 1, BitFieldArray[1]);

			if (BitFieldArray[0].reserved_ints > BitFieldArray[1].reserved_ints)
			{
				BitFieldArray[2].ChangeSize(BitFieldArray[0].reserved_ints);
			}
			else
			{
				BitFieldArray[2].ChangeSize(BitFieldArray[1].reserved_ints);
			}

			BitFieldArray[2] = (BitFieldArray[0] | BitFieldArray[1]);

			OutputRow(BitFieldArray[2]);
			break;

		case 5:

			if_field_isnt_initialized(field_initialized, 0, BitFieldArray[0]);
			if_field_isnt_initialized(field_initialized, 1, BitFieldArray[1]);

			if (BitFieldArray[0].reserved_ints > BitFieldArray[1].reserved_ints)
			{
				BitFieldArray[2].ChangeSize(BitFieldArray[0].reserved_ints);
			}
			else
			{
				BitFieldArray[2].ChangeSize(BitFieldArray[1].reserved_ints);
			}

			BitFieldArray[2] = (BitFieldArray[0] & BitFieldArray[1]);

			OutputRow(BitFieldArray[2]);
			break;

		case 6:
		{

			int which_bitfield = 0;

			std::cout << "\nWhich bitfield do you want printed?\nA - 0\nB - 1\n";
			std::cin.ignore();
			std::cin >> which_bitfield;

			if (field_initialized[which_bitfield])
			{
				OutputRow(BitFieldArray[which_bitfield]);
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
}