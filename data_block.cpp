#include "data_block.h"
#include "cstring"
data_block::data_block() : size(0), count(0) { }
void data_block::inc_data() {
		dword *temp_data = new dword[size];
		for (int i = 0; i <= size - 1; ++i)
			temp_data[i] = data[i];
		delete[]data;
		count *= 2;
		data = new dword[count];
		for (int i = 0; i <= size - 1; ++i)
			data[i] = temp_data[i];
		delete[]temp_data;

		char **temp_title = new char*[size];
		for (int i = 0; i <= size - 1; ++i) {
			temp_title[i] = new char[size_char(title[i])];
			temp_title[i] = title[i];
		}
		delete[]title;
		title = new char*[count];
		for (int i = 0; i <= size - 1; ++i) {
			title[i] = new char[size_char(temp_title[i])];
			title[i] = temp_title[i];
		}
		delete[]temp_title;
}
void data_block::dec_data() {
	dword *temp_data = new dword[size];
	for (int i = 0; i <= size - 1; ++i)
		temp_data[i] = data[i];
	delete[]data;
	count /= 2;
	data = new dword[count];
	for (int i = 0; i <= size - 1; ++i)
		data[i] = temp_data[i];
	delete[]temp_data;

	char **temp_title = new char*[size];
	for (int i = 0; i <= size - 1; ++i) {
		temp_title[i] = new char[size_char(title[i])];
		temp_title[i] = title[i];
	}
	delete[]title;
	title = new char*[count];
	for (int i = 0; i <= size - 1; ++i) {
		title[i] = new char[size_char(temp_title[i])];
		title[i] = temp_title[i];
	}
	delete[]temp_title;
}
int data_block::size_char(char* text) {
	int i = 0;
	while (*text++) ++i;
	return i;
}
void data_block::push(const dword &value, const std::string& in) {
	if (data == nullptr) {
		++size;
		++count;
		data = new dword[1];
		data[0] = value;
		title = new char*[1];
		title[0] = new char[in.size() + 2];
		strcpy_s(title[0], in.size() + 1, in.c_str());
	}
	else {
		++size;
		if (count == size) {
			inc_data();
		}
		title[size - 1] = new char[in.size() + 2];
		strcpy_s(title[size - 1], in.size() + 1, in.c_str());
		data[size - 1] = value;
	}
}
void data_block::print_stack() {
	for (int i = size - 1; i >= 0; i--)
		std::cout << "title[" << i << "] : " << title[i] << data[i] << std::endl;
}
bool data_block::validator(const std::string &in) {
	for (int i = 0; i < size; ++i) {
		if (in == title[i]) {
			return true;
		}
	}
	return false;
}
dword& data_block::return_by_string(const std::string &in) {
	for (int i = 0; i < size; ++i) {
		if (in == title[i]) {
			return data[i];
		}
	}
}
int data_block::return_size() {
	return size;
}
dword data_block::pop() {
	--size;
	if (count - size == size)
		dec_data();
	return data[size];
}