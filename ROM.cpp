#include "ROM.h"
#include <cstdlib>
byte& ROM::return_by_string(const std::string &title) {
	if (title == "AH") return EAX.return_byte(0);
	else if (title == "AL") return EAX.return_byte(1);
	else if (title == "BH") return EBX.return_byte(0);
	else if (title == "BL") return EBX.return_byte(1);
	else if (title == "CH") return ECX.return_byte(0);
	else if (title == "CL") return ECX.return_byte(1);
	else if (title == "DH") return EDX.return_byte(0);
	else if (title == "DL") return EDX.return_byte(1);
}

dword& ROM::return_reg_by_string(const std::string &title) {
	if (title == "EAX") return EAX;
	else if (title == "EBX") return EBX;
	else if (title == "ECX") return ECX;
	else if (title == "EDX") return EDX;
}

dword ROM::mov_reg(const std::string &in, const std::string &out) {
	return_reg_by_string(in) = return_reg_by_string(out);
	return return_reg_by_string(in);
}

dword ROM::mov_reg(const std::string &in, int out) {
	return_reg_by_string(in) = out;
	return return_reg_by_string(in);
}

byte ROM::mov(const std::string &in, const std::string &out) {
	return_by_string(in) = return_by_string(out);
	return return_by_string(in);
}

byte ROM::mov(const std::string &in, int out) {
	return_by_string(in) = out;
	return return_by_string(in);
}

byte ROM::add(const std::string &in, const std::string &out) {
	return_by_string(in) += return_by_string(out);
	return return_by_string(in);
}

byte ROM::add(const std::string &in, int out) {
	return_by_string(in) += out;
	return return_by_string(in);
}

byte ROM::sub(const std::string &in, const std::string &out) {
	return_by_string(in) -= return_by_string(out);
	return return_by_string(in);
}

byte ROM::sub(const std::string &in, int out) {
	return_by_string(in) -= out;
	return return_by_string(in);
}

bool ROM::cmp(const std::string &in, const std::string &out) {
	if (return_by_string(in) == return_by_string(out)) {
		std::cout << "eq" << std::endl;
		return true;
	}
	else if (return_by_string(in) != return_by_string(out)) {
		std::cout << "not eq" << std::endl;
		return false;
	}
}
void ROM::push(const std::string &in) {
	if (validator_parts(in))
		Stack.push(return_by_string(in));
	else if (validator_reg(in)) {
		Stack.push(return_reg_by_string(in));
	}
	else {
		dword temp = std::stoi(in);
		Stack.push(temp);
	}
}
void ROM::pop(const std::string &in) {
	if (validator_parts(in))
		return_by_string(in) = Stack.pop();
	else if (validator_reg(in)) {
		return_reg_by_string(in) = Stack.pop();
	}
}

void ROM::input_mov(const std::string &in, const std::string &out) {
	if (validator_parts(out))
		mov(in, out);
	else if (validator_reg(out))
		mov_reg(in, out);
	else {
		int i = std::atoi(out.c_str());
		if (validator_reg(in)) {
			mov_reg(in, i);
		}
		if (validator_parts(in))
			mov(in, i);
	}
}
void ROM::input_add(const std::string &in, const std::string &out) {
	if (validator_parts(out))
		add(in, out);
	else {
		int i = std::atoi(out.c_str());
		add(in, i);
	}
}
void ROM::input_sub(const std::string &in, const std::string &out) {
	if (validator_parts(out))
		sub(in, out);
	else {
		int i = std::atoi(out.c_str());
		sub(in, i);
	}
}
void ROM::input_cmp(const std::string &in, const std::string &out) {
	cmp(in, out);
}
bool ROM::parser(const std::string &input) {
	if (input == "mov") {
		std::string in, out;
		std::cin >> in >> out;
		input_mov(in, out);
		return true;
	}
	else if (input == "add") {
		std::string in, out;
		std::cin >> in >> out;
		input_add(in, out);
		return true;
	}
	else if (input == "sub") {
		std::string in, out;
		std::cin >> in >> out;
		input_sub(in, out);
		return true;
	}
	else if (input == "cmp") {
		std::string in, out;
		std::cin >> in >> out;
		input_cmp(in, out);
		return true;
	}
	else if (input == "push") {
		std::string in;
		std::cin >> in;
		push(in);
		return true;
	}
	else if (input == "pop") {
		std::string in;
		std::cin >> in;
		pop(in);
		return true;
	}
	else if (input == "out") {
		std::cout <<
			"EAX: " << EAX << std::endl <<
			"EBX: " << EBX << std::endl <<
			"ECX: " << ECX << std::endl <<
			"EDX: " << EDX << std::endl << std::endl;
		return true;
	}
	else if (input == "open") {
		file_parser();
	}
	else if (input == "exit") return false;
}

bool ROM::validator_parts(const std::string &in) {
	if (in == "AH" || in == "BH" || in == "AL" || in == "BL" || in == "CL" || in == "DL" || in == "CL" || in == "DL")
		return true;
	else return false;
}

bool ROM::validator_reg(const std::string &in) {
	if (in == "EAX" || in == "EBX" || in == "ECX" || in == "EDX")
		return true;
	else return false;
}

bool ROM::validator_command(const std::string &in) {
	if (in == "mov" || in == "add" || in == "sub" || in == "cmp" ||
		in == "open" || in == "push" || in == "pop" || in == "out")
		return true;
	else return false;
}

int ROM::comp(std::ifstream &file) {
	int count = 0;
	std::string in, out;
	for (file >> in; !file.eof(); file >> in) {
		++count;
		if (in == "mov" || in == "add" || in == "sub" || in == "cmp") {
			file >> in;
			file >> out;
		}
		else if (in == "push" || in == "pop") {
			file >> in;
		}
		else if (in == "out" || in == "open") {}
		else {
			std::cout << "Unknown command: <" << in << "> in string " << count << std::endl;
			return false;
		}
	}
	++count;
	if (in == "mov" || in == "add" || in == "sub" || in == "cmp") {
		file >> in;
		file >> out;
	}
	else if (in == "push" || in == "pop") {
		file >> in;
	}
	else if (in == "out" || in == "open") {}
	else {
		std::cout << "Unknown command: <" << in << "> in string " << count << std::endl;
		return false;
	}
	std::cout << "comp. completed. Strings in file: " << count << std::endl;
	return count;
}

bool ROM::file_parser() {
	std::string in, out;
	std::cin >> in;
	std::ifstream file(in);
	if (!file.is_open()) {
		std::cout << "CAN'T OPEN\n";
		return false;
	}
	file.seekg(0, std::ios_base::end);
	std::cout << "Opened file. File size: " << file.tellg() << std::endl;
	file.seekg(0, std::ios_base::beg);
	if (comp(file)) {
		std::cout << "\nRunning...\n";
		file.seekg(0, std::ios_base::beg);
		for (file >> in; !file.eof(); file >> in) {
			if (in == "mov") {
				file >> in;
				file >> out;
				input_mov(in, out);
			}
			else if (in == "add") {
				file >> in;
				file >> out;
				input_add(in, out);
			}
			else if (in == "sub") {
				file >> in;
				file >> out;
				input_sub(in, out);
			}
			else if (in == "cmp") {
				file >> in;
				file >> out;
				input_cmp(in, out);
			}
			else if (in == "push") {
				file >> in;
				push(in);
			}
			else if (in == "pop") {
				file >> in;
				pop(in);
			}
			else if (in == "out") {
				std::cout << "EAX: " << EAX << std::endl <<
					"EBX: " << EBX << std::endl <<
					"ECX: " << ECX << std::endl <<
					"EDX: " << EDX << std::endl << std::endl;
			}
			else if (in == "open") {
				file_parser();
			}
		}
		if (in == "mov") {
			file >> in;
			file >> out;
			input_mov(in, out);
		}
		else if (in == "add") {
			file >> in;
			file >> out;
			input_add(in, out);
		}
		else if (in == "sub") {
			file >> in;
			file >> out;
			input_sub(in, out);
		}
		else if (in == "cmp") {
			file >> in;
			file >> out;
			input_cmp(in, out);
		}
		else if (in == "push") {
			file >> in;
			push(in);
		}
		else if (in == "pop") {
			file >> in;
			pop(in);
		}
		else if (in == "out") {
			std::cout << "EAX: " << EAX << std::endl <<
				"EBX: " << EBX << std::endl <<
				"ECX: " << ECX << std::endl <<
				"EDX: " << EDX << std::endl << std::endl;
		}
		else if (in == "open") {
			file_parser();
		}
		std::cout << "Finished.\n";
		return true;
	}
	return false;
}