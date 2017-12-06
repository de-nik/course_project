#include "RAM.h"

RAM::RAM() : size(0), size_elector(0) { }

void RAM::inc_electors() {
	byte *temp_elector = new byte[size_elector];
	for (int i = 0; i <= size_elector - 1; ++i)
		temp_elector[i] = elector[i];
	delete[]elector;
	elector = new byte[++size_elector];
	for (int i = 0; i <= size_elector - 1; ++i)
		elector[i] = temp_elector[i];
	delete[]temp_elector;
}

void RAM::inc_data(int count) {
	byte *temp_data = new byte[size];
	for (int i = 0; i <= size - 1; ++i)
		temp_data[i] = data[i];
	delete[]data;
	size += count;
	data = new byte[size];
	for (int i = 0; i <= size - 1; ++i)
		data[i] = temp_data[i];
	delete[]temp_data;
}

void RAM::push(const byte &value)
{
	if (data == nullptr) {
		data = new byte[++size];
		elector = new byte[++size_elector];
		data[0] = value;
		elector[0].setbit(0, 1);
	}
	else {
		inc_data(1);
		data[size - 1] = value;
		if (elector[size_elector - 1].getbit(6) || elector[size_elector - 1].getbit(7)) {
			inc_electors();
			elector[size_elector - 1].setbit(0, 1);
		}
		else if (elector[size_elector - 1].getbit(4) || elector[size_elector - 1].getbit(5)) {
			elector[size_elector - 1].setbit(6, 1);
		}
		else if (elector[size_elector - 1].getbit(2) || elector[size_elector - 1].getbit(3)) {
			elector[size_elector - 1].setbit(4, 1);
		}
		else {
			elector[size_elector - 1].setbit(2, 1);
		}
	}
}

void RAM::push(const word &value)
{
	if (data == nullptr) {
		size += 4;
		data = new byte[4];
		elector = new byte[++size_elector];
		for (int i = 3; i >= 0; --i)
			data[i] = value.return_byte(i);
		elector[0].setbit(1, 1);
	}
	else {
		inc_data(2);
		for (int i = 1, j = 1; i >= 0; --i, ++j)
			data[size - j] = value.return_byte(i);

		if (elector[size_elector - 1].getbit(6) || elector[size_elector - 1].getbit(7)) {
			inc_electors();
			elector[size_elector - 1].setbit(1, 1);
		}
		else if (elector[size_elector - 1].getbit(4) || elector[size_elector - 1].getbit(5)) {
			elector[size_elector - 1].setbit(7, 1);
		}
		else if (elector[size_elector - 1].getbit(2) || elector[size_elector - 1].getbit(3)) {
			elector[size_elector - 1].setbit(5, 1);
		}
		else {
			elector[size_elector - 1].setbit(3, 1);
		}
	}
}

void RAM::push(const dword &value)
{
	if (data == nullptr) {
		size += 4;
		data = new byte[4];
		elector = new byte[++size_elector];
		for(int i = 3; i >= 0; --i)
			data[i] = value.return_byte(i);
		elector[0].setbit(0, 1);
		elector[0].setbit(1, 1);
	}
	else {
		inc_data(4);
		for (int i = 3, j = 1; i >= 0; --i, ++j)
			data[size - j] = value.return_byte(i);

		if (elector[size_elector - 1].getbit(6) || elector[size_elector - 1].getbit(7)) {
			inc_electors();
			elector[size_elector - 1].setbit(0, 1);
			elector[size_elector - 1].setbit(1, 1);
		}
		else if (elector[size_elector   - 1].getbit(4) || elector[size_elector - 1].getbit(5)) {
			elector[size_elector - 1].setbit(6, 1);
			elector[size_elector - 1].setbit(7, 1);
		}
		else if (elector[size_elector   - 1].getbit(2) || elector[size_elector - 1].getbit(3)) {
			elector[size_elector - 1].setbit(5, 1);
			elector[size_elector - 1].setbit(4, 1);
		}
		else {
			elector[size_elector - 1].setbit(3, 1);
			elector[size_elector - 1].setbit(2, 1);
		}
	}
}

void RAM::kill_electors() {
		byte *temp_elector = new byte[size_elector];
		for (int i = 0; i <= size_elector - 2; ++i)
			temp_elector[i] = elector[i];
		delete[]elector;
		elector = new byte[--size_elector];
		for (int i = 0; i <= size_elector - 1; ++i)
			elector[i] = temp_elector[i];
		delete[]temp_elector;
}

void RAM::dec_data(int count){
	byte *temp_data = new byte[size];
	for (int i = 0; i <= size - 1 - count; ++i)
		temp_data[i] = data[i];
	delete[]data;
	size -= count;
	data = new byte[size];
	for (int i = 0; i <= size - 1; ++i)
		data[i] = temp_data[i];
	delete[]temp_data;
}

void RAM::kill_elector(int number) {
	if (number == 28 || number == 15 || number == 13) {
		elector[size_elector - 1].setbit(7, 0);
		elector[size_elector - 1].setbit(6, 0);
	}
	if (number == 20 || number == 11 || number == 9) {
		elector[size_elector - 1].setbit(5, 0);
		elector[size_elector - 1].setbit(4, 0);
	}
	if (number == 12 || number == 7 || number == 5) {
		elector[size_elector - 1].setbit(3, 0);
		elector[size_elector - 1].setbit(2, 0);
	}
	if (number == 4 || number == 3 || number == 1) {
		elector[size_elector - 1].setbit(1, 0);
		elector[size_elector - 1].setbit(0, 0);
	}
}

int RAM::make_dword() {
	dword dw(data[size - 4], data[size - 3], data[size - 2], data[size - 1]);
	int temp = dw.to_int();
	return temp;
}

int RAM::make_word() {
	word dw(data[size - 2], data[size - 1]);
	int temp = dw.to_int();
	return temp;
}

int RAM::make_byte() {
	byte dw;
	dw = data[size - 1];
	int temp = dw.to_int();
	return temp;
}

int RAM::elections(int electors_choise) {
	int temp(0);
	switch (electors_choise) {
	case 28:
		temp = make_dword();
		dec_data(4);
		kill_elector(electors_choise);
		return temp;
	case 15:
		temp = make_word();
		dec_data(2);
		kill_elector(electors_choise);
		return temp;
	case 13:
		temp = make_byte();
		dec_data(1);
		kill_elector(electors_choise);
		return temp;
	case 20:
		temp = make_dword();
		dec_data(4);
		kill_elector(electors_choise);
		return temp;
	case 11:
		temp = make_word();
		dec_data(2);
		kill_elector(electors_choise);
		return temp;
	case 9:
		temp = make_byte();
		dec_data(1);
		kill_elector(electors_choise);
		return temp;
	case 12:
		temp = make_dword();
		dec_data(4);
		kill_elector(electors_choise);
		return temp;
	case 7:
		temp = make_word();
		dec_data(2);
		kill_elector(electors_choise);
		return temp;
	case 5:
		temp = make_byte();
		dec_data(1);
		kill_elector(electors_choise);
		return temp;
	case 4:
		temp = make_dword();
		dec_data(4);
		kill_electors();
		return temp;
	case 3:
		temp = make_word();
		dec_data(2);
		kill_electors();
		return temp;
	case 1:
		temp = make_byte();
		dec_data(1);
		kill_electors();
		return temp;
	}
}

int RAM::pop()
{
	int flag(0), w(0);
	for (int i = 7; i >= 0; --i) {
		++w;
		if (elector[size_elector - 1].getbit(i)) {
			flag += (2*i + 1);
		}
		if (w == 2 && flag != 0) {
			return elections(flag);
		}
		else if (w == 2 && flag == 0) {
			w = 0;
		}
	}
}

void RAM::print_stack()
{
	for (int i = size - 1; i >= 0; i--)
		std::cout << "data[" << i << "] : " << data[i] << std::endl;
}

void RAM::print_electors()
{
	for (int i = size_elector - 1; i >= 0; i--)
		std::cout  << elector[i] << std::endl;
}
