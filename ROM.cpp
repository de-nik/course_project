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
void ROM::mov(const std::string &in, const std::string &out, int type) {
	if (type) 
		return_by_string(in) = return_by_string(out);
	else 
		return_reg_by_string(in) = return_reg_by_string(out);
}
void ROM::mov(const std::string &in, int out, int type) {
	if (type) 
		return_by_string(in) = out;
	else 
		return_reg_by_string(in) = out;
}
void ROM::add(const std::string &in, const std::string &out, int type) {
	if (type)
		return_by_string(in) += return_by_string(out);
	else
		return_reg_by_string(in) += return_reg_by_string(out);
}
void ROM::add(const std::string &in, int out, int type) {
	if (type)
		return_by_string(in) += out;
	else
		return_reg_by_string(in) += out;
}
void ROM::sub(const std::string &in, const std::string &out, int type) {
	if (type)
		return_by_string(in) -= return_by_string(out);
	else
		return_reg_by_string(in) -= return_reg_by_string(out);
}
void ROM::sub(const std::string &in, int out, int type) {
	if (type)
		return_by_string(in) -= out;
	else
		return_reg_by_string(in) -= out;
}
void ROM::xor(const std::string &in, const std::string &out, int type) {
	if (type) 
		return_by_string(in) ^= return_by_string(out);
	else 
		return_reg_by_string(in) ^= return_reg_by_string(out);
}
void ROM::xor(const std::string &in, int out, int type) {
	if (type) {
		byte temp(out);
		return_by_string(in) ^= temp;
	}
	else {
		dword temp(out);
		return_reg_by_string(in) ^= temp;
	}
}
bool ROM::cmp(const std::string &in, const std::string &out) {
	if (return_by_string(in) == return_by_string(out)) {
		std::cout << "eq" << std::endl;
		return true;
	}
	else  {
		std::cout << "not eq" << std::endl;
		return false;
	}
}
void ROM::and (const std::string &in, const std::string &out, int type) {
	if (type)
		return_by_string(in) &= return_by_string(out);
	else
		return_reg_by_string(in) &= return_reg_by_string(out);
}
void ROM::and (const std::string &in, int out, int type) {
	if (type) {
		byte temp(out);
		return_by_string(in) &= temp;
	}
	else {
		dword temp(out);
		return_reg_by_string(in) &= temp;
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
		mov(in, out, 1);
	else if (validator_reg(out))
		mov(in, out, 0);
	else {
		int i = std::atoi(out.c_str());
		if (validator_reg(in)) {
			mov(in, i, 0);
		}
		else if (validator_parts(in))
			mov(in, i, 1);
	}
}
void ROM::input_xor(const std::string &in, const std::string &out) {
	if (validator_parts(out))
		xor(in, out, 1);
	else if (validator_reg(out))
		xor(in, out, 0);
	else {
		int i = std::atoi(out.c_str());
		if (validator_reg(in)) {
			xor(in, i, 0);
		}
		else if (validator_parts(in))
			xor(in, i, 1);
	}
}
void ROM::input_and(const std::string &in, const std::string &out) {
	if (validator_parts(out))
		and(in, out, 1);
	else if (validator_reg(out))
		and(in, out, 0);
	else {
		int i = std::atoi(out.c_str());
		if (validator_reg(in)) {
			and(in, i, 0);
		}
		else if (validator_parts(in))
			and(in, i, 1);
	}
}
void ROM::input_add(const std::string &in, const std::string &out) {
	if (validator_parts(out))
		add(in, out, 1);
	else if (validator_reg(out))
		add(in, out, 0);
	else {
		int i = std::atoi(out.c_str());
		if (validator_reg(in)) {
			add(in, i, 0);
		}
		else if (validator_parts(in))
			add(in, i, 1);
	}
}
void ROM::input_sub(const std::string &in, const std::string &out) {
	if (validator_parts(out))
		sub(in, out, 1);
	else if (validator_reg(out))
		sub(in, out, 0);
	else {
		int i = std::atoi(out.c_str());
		if (validator_reg(in)) {
			sub(in, i, 0);
		}
		else if (validator_parts(in))
			sub(in, i, 1);
	}
}
bool ROM::input_cmp(const std::string &in, const std::string &out) {
	return cmp(in, out);
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
	else if (input == "xor") {
		std::string in, out;
		std::cin >> in >> out;
		input_xor(in, out);
		return true;
	}
	else if (input == "and") {
		std::string in, out;
		std::cin >> in >> out;
		input_and(in, out);
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

int ROM::comp(const std::string &input) {
	std::ifstream file(input);
	int count = 0;
	std::string in, out;
	for (file >> in; !file.eof(); file >> in) {
		++count;
		if (in == "mov" || in == "add" || in == "sub" || in == "cmp" || in == "xor" || in == "and") {
			file >> in;
			file >> out;
		}
		else if (in == "push" || in == "pop" || in == "open") {
			file >> in;
		}
		else if (in == "out" || in == "jmp" || in == "jne" || in == "label") {}
		else {
			std::cout << "Unknown command: <" << in << "> in string " << count << std::endl;
			return false;
		}
	}
	std::cout << "comp. completed. Strings in file: " << count << std::endl;
	return count;
}
bool ROM::file_parser() {
	std::string in, out, label;
	int lbl = 0;
	std::cin >> in;
	std::ifstream file(in);
	if (!file.is_open()) {
		std::cout << "CAN'T OPEN\n";
		return false;
	}
	file.seekg(0, std::ios_base::end);
	std::cout << "Opened file. File size: " << file.tellg() << std::endl;
	file.seekg(0, std::ios_base::beg);
	if (comp(in)) {
		std::cout << "\nRunning...\n";
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
				file >> label;
				int temp = file.tellg();
				if (label == "jne") {
					if (input_cmp(in, out)) {
						file.seekg(-((int)file.tellg() - lbl), std::ios_base::cur);
					}
				}
				else {
					file.seekg(-((int)file.tellg() - temp), std::ios_base::cur);
				}
			}
			else if (in == "xor") {
				file >> in;
				file >> out;
				input_xor(in, out);
			}
			else if (in == "and") {
				file >> in;
				file >> out;
				input_and(in, out);
			}
			else if (in == "push") {
				file >> in;
				push(in);
			}
			else if (in == "pop") {
				file >> in;
				pop(in);
			}
			else if (in == "label") {
				lbl = file.tellg();
			}
			else if (in == "jmp") {
				file.seekg(-((int)file.tellg() - lbl), std::ios_base::cur);
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
		std::cout << "Finished.\n";
		return true;
	}
	return false;
}