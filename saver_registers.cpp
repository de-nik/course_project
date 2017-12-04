#include "saver_registers.h"

byte& saver_registers::return_by_string(const std::string &title) {
	if (title == "AH") return EAX.return_byte(0);
	else if (title == "AL") return EAX.return_byte(1);
	else if (title == "BH") return EBX.return_byte(0);
	else if (title == "BL") return EBX.return_byte(1);
}

dword& saver_registers::return_reg_by_string(const std::string &title) {
	if (title == "EAX") return EAX;
	else if (title == "EBX") return EBX;
}

dword saver_registers::mov_reg(const std::string &in, const std::string &out) {
	return_reg_by_string(in) = return_reg_by_string(out);
	return return_reg_by_string(in);
}

dword saver_registers::mov_reg(const std::string &in, int out) {
	return_reg_by_string(in) = out;
	return return_reg_by_string(in);
}

byte saver_registers::mov(const std::string &in, const std::string &out) {
	return_by_string(in) = return_by_string(out);
	return return_by_string(in);
}

byte saver_registers::mov(const std::string &in, int out) {
	return_by_string(in) = out;
	return return_by_string(in);
}

byte saver_registers::add(const std::string &in, const std::string &out) {
	return_by_string(in) += return_by_string(out);
	return return_by_string(in);
}

byte saver_registers::add(const std::string &in, int out) {
	return_by_string(in) += out;
	return return_by_string(in);
}

byte saver_registers::sub(const std::string &in, const std::string &out) {
	return_by_string(in) -= return_by_string(out);
	return return_by_string(in);
}

byte saver_registers::sub(const std::string &in, int out) {
	return_by_string(in) -= out;
	return return_by_string(in);
}

bool saver_registers::cmp(const std::string &in, const std::string &out) {
	if (return_by_string(in) == return_by_string(out)) {
		std::cout << "eq" << std::endl;
		return true;
	}
	if (return_by_string(in) != return_by_string(out)) {
		std::cout << "not eq" << std::endl;
		return false;
	}
}
void saver_registers::push(const std::string &in) {
	if (in == "AH" || in == "BH" || in == "AL" || in == "BL")
		Stack.push(return_by_string(in));
	if (in == "EAX" || in == "EBX") {
		Stack.push(return_reg_by_string(in));
	}
	else {
		dword temp = std::stoi(in);
		Stack.push(temp);
	}
}
void saver_registers::pop() {	
	std::string in;
	std::cin >> in;
	if (in == "AH" || in == "BH" || in == "AL" || in == "BL")
		return_by_string(in) = Stack.pop();
	if (in == "EAX" || in == "EBX") {
		return_reg_by_string(in) = Stack.pop();
	}
}

void saver_registers::input_mov() {
	std::string in, out;
	std::cin >> in >> out;
	if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
		mov(in, out);
	else if (out == "EAX" || out == "EBX")
		mov_reg(in, out);
	else {
		int i = std::atoi(out.c_str());
		if (in == "EAX" || in == "EBX") {
			mov_reg(in, i);
		}
		if (in == "AH" || in == "BH" || in == "AL" || in == "BL")
			mov(in, i);
	}
}
void saver_registers::input_add() {
	std::string in, out;
	std::cin >> in >> out;
	if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
		add(in, out);
	else {
		int i = std::atoi(out.c_str());
		add(in, i);
	}
}
void saver_registers::input_sub() {
	std::string in, out;
	std::cin >> in >> out;
	if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
		sub(in, out);
	else {
		int i = std::atoi(out.c_str());
		sub(in, i);
	}
}
void saver_registers::input_cmp() {
	std::string in, out;
	std::cin >> in >> out;
	cmp(in, out);
}
bool saver_registers::parser(const std::string &input) {
	if (input == "mov") {
		input_mov();
		return true;
	}
	if (input == "add") {
		input_add();
		return true;
	}
	if (input == "sub") {
		input_sub();
		return true;
	}
	if (input == "cmp") {
		input_cmp();
		return true;
	}
	if (input == "push") {
		std::string in;
		std::cin >> in;
		push(in);
		return true;
	}
	if (input == "pop") {
		pop();
		return true;
	}
	if (input == "out") {
		std::cout <<
			"EAX: " << EAX << std::endl <<
			"EBX: " << EBX << std::endl << std::endl;
		return true;
	}
	else if (input == "exit") throw false;
}

