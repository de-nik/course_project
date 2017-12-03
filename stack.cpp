#include "stack.h"

stack::stack() : size(0) { }

void stack::push(const byte &value)
{
	if (data == nullptr) {
		data = new byte[++size];
		elector = new byte[1];
		data[0] = value;
		elector[0].setbit(0, 1);
	}
	else {
		byte *temp_data = new byte[size];
		for (int i = 0; i <= size - 1; ++i)
			temp_data[i] = data[i];
		delete[]data;
		data = new byte[++size];
		for (int i = 0; i <= size - 1; ++i)
			data[i] = temp_data[i];
		delete[]temp_data;
		data[size - 1] = value;

		if (elector[(size + 3) / 4   - 1].getbit(6) || elector[(size + 3) / 4 - 1].getbit(7)) {
			byte *temp_elector = new byte[(size + 3) / 4];
			for (int i = 0; i <= (size + 3) / 4 - 1; ++i)
				temp_elector[i] = elector[i];
			delete[]elector;
			elector = new byte[(size + 3) / 4 + 1];
			for (int i = 0; i <= (size + 3) / 4 - 1; ++i)
				elector[i] = temp_elector[i];
			delete[]temp_elector;
			elector[(size + 3) / 4   - 1].setbit(0, 1);
		}
		else if (elector[(size + 3) / 4 - 1].getbit(4) || elector[(size + 3) / 4 - 1].getbit(5)) {
			elector[(size + 3) / 4   - 1].setbit(6, 1);
		}
		else if (elector[(size + 3) / 4 - 1].getbit(2) || elector[(size + 3) / 4 - 1].getbit(3)) {
			elector[(size + 3) / 4 - 1].setbit(4, 1);
		}
		else {
			elector[(size + 3) / 4 - 1].setbit(2, 1);
		}
	}
}

void stack::push(const dword &value)
{
	if (data == nullptr) {
		size += 4;
		data = new byte[4];
		elector = new byte[1];
		for(int i = 3; i >= 0; --i)
			data[i] = value.return_byte(i);
		elector[0].setbit(0, 1);
		elector[0].setbit(1, 1);
	}
	else {
		byte *temp_data = new byte[size];
		for (int i = 0; i <= size - 1; ++i)
			temp_data[i] = data[i];
		delete[]data;
		size += 4;
		data = new byte[size];
		for (int i = 0; i <= size - 1; ++i)
			data[i] = temp_data[i];
		delete[]temp_data;
		for (int i = 3, j = 1; i >= 0; --i, ++j)
			data[size - j] = value.return_byte(i);

		if (elector[(size + 3) / 4 - 1].getbit(6) || elector[(size + 3) / 4 - 1].getbit(7)) {
			byte *temp_elector = new byte[(size + 3) / 4];
			for (int i = 0; i <= (size + 3) / 4 - 1; ++i)
				temp_elector[i] = elector[i];
			delete[]elector;
			elector = new byte[(size + 3) / 4 + 1];
			for (int i = 0; i <= (size + 3) / 4 - 1; ++i)
				elector[i] = temp_elector[i];
			delete[]temp_elector;
			elector[(size + 3) / 4 - 1].setbit(0, 1);
			elector[(size + 3) / 4 - 1].setbit(1, 1);
		}
		else if (elector[(size + 3) / 4   - 1].getbit(4) || elector[(size + 3) / 4 - 1].getbit(5)) {
			elector[(size + 3) / 4 - 1].setbit(6, 1);
			elector[(size + 3) / 4 - 1].setbit(7, 1);
		}
		else if (elector[(size + 3) / 4   - 1].getbit(2) || elector[(size + 3) / 4 - 1].getbit(3)) {
			elector[(size + 3) / 4 - 1].setbit(5, 1);
			elector[(size + 3) / 4 - 1].setbit(4, 1);
		}
		else {
			elector[(size + 3) / 4 - 1].setbit(3, 1);
			elector[(size + 3) / 4 - 1].setbit(2, 1);
		}
	}
}

void stack::kill_electors(int target) {
	if (target == 4) {
		byte *temp_elector = new byte[size/4];
		for (int i = 0; i <= size/4 - 1; ++i)
			temp_elector[i] = elector[i];
		delete[]elector;
		elector = new byte[size/4 - 1];
		for (int i = 0; i <= size/4 - 2; ++i)
			elector[i] = temp_elector[i];
		delete[]temp_elector;
	}
}

void stack::elections(int electors_choise) {
	switch (electors_choise) {
	case 28:
		size -= 4;
		kill_electors(4);
		break;
	case 15:
		size -= 2;
		kill_electors(2);
		break;
	case 13:
		size -= 1;
		kill_electors(1);
		break;
	case 20:
		size -= 4;
		kill_electors(4);
		break;
	case 11:
		size -= 2;
		kill_electors(2);
		break;
	case 9:
		size -= 1;
		kill_electors(1);
		break;
	case 12:
		size -= 4;
		kill_electors(4);
		break;
	case 7:
		size -= 2;
		kill_electors(2);
		break;
	case 5:
		size -= 1;
		kill_electors(1);
		break;
	case 4:
		size -= 4;
		kill_electors(4);
		break;
	case 3:
		size -= 2;
		kill_electors(2);
		break;
	case 1:
		size -= 1;
		kill_electors(1);
		break;
	}
}
void stack::pop()
{
	int flag(0), w(0);
	for (int i = 7; i >= 0; --i) {
		++w;
		if (elector[(size + 3) / 4 - 1].getbit(i)) {
			flag += (2*i + 1);
		}
		if (w == 2 && flag != 0) {
			elections(flag);
			break;
		}
		else if (w == 2 && flag == 0) {
			w = 0;
		}
	}
	byte *temp_data = new byte[size];
	for (int i = 0; i <= size - 1; ++i)
		temp_data[i] = data[i];
	delete[]data;
	data = new byte[size];
	for (int i = 0; i <= size - 1; ++i)
		data[i] = temp_data[i];
	delete[]temp_data;
}

void stack::print_stack()
{
	for (int i = size - 1; i >= 0; i--)
		std::cout << "data[" << i << "] : " << data[i] << std::endl;
}

void stack::print_electors()
{
	for (int i = (size + 3) / 4 - 1; i >= 0; i--)
		std::cout  << elector[i] << std::endl;
}