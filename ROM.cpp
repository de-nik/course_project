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
/******************************doublecommand*****************************************/
void ROM::mov(const std::string &in, const std::string &out) {
	int temp_out(0);
	if (validator_parts(out))
		temp_out = return_by_string(out).to_int();
	else if (validator_reg(out))
		temp_out = return_reg_by_string(out).to_int();
	else if (validator_title(out))
		temp_out = data.return_by_string(out).to_int();
	else if(isint(out))
		temp_out = std::atoi(out.c_str());

	if (validator_parts(in))
		return_by_string(in) = temp_out;
	else if (validator_reg(in))
		return_reg_by_string(in) = temp_out;
	else if (validator_title(in))
		data.return_by_string(in) = temp_out;
	else {}
}
void ROM::add(const std::string &in, const std::string &out) {
	int temp_out(0);
	if (validator_parts(out))
		temp_out = return_by_string(out).to_int();
	else if (validator_reg(out))
		temp_out = return_reg_by_string(out).to_int();
	else if (validator_title(out))
		temp_out = data.return_by_string(out).to_int();
	else if(isint(out))
		temp_out = std::atoi(out.c_str());

	if (validator_parts(in)) 
		return_by_string(in) += temp_out;
	else if (validator_reg(in))	 
		return_reg_by_string(in) += temp_out;
	else if (validator_title(in))
		data.return_by_string(in) += temp_out;
	else {}
}
void ROM::sub(const std::string &in, const std::string &out) {
	int temp_out(0);
	if (validator_parts(out)) 
		temp_out = return_by_string(out).to_int();
	else if (validator_reg(out))   
		temp_out = return_reg_by_string(out).to_int();
	else if (validator_title(out)) 
		temp_out = data.return_by_string(out).to_int();
	else
		temp_out = std::atoi(out.c_str());

	if (validator_parts(out)) 
		return_by_string(in) -= temp_out;
	else if (validator_reg(in))	
		return_reg_by_string(in) -= temp_out;
	else if (validator_title(in))
		data.return_by_string(in) -= temp_out;
	else {}
}
void ROM:: xor (const std::string &in, const std::string &out) {
	int temp_out;
	if (validator_parts(out))
		temp_out = return_by_string(out).to_int();
	else if (validator_reg(out))
		temp_out = return_reg_by_string(out).to_int();
	else if (validator_title(out))
		temp_out = data.return_by_string(out).to_int();
	else
		temp_out = std::atoi(out.c_str());

	if (validator_parts(in))
		return_by_string(in) ^= temp_out;
	else if (validator_reg(in))
		return_reg_by_string(in) ^= temp_out;
	else if (validator_title(in))
		data.return_by_string(in) ^= temp_out;
	else {}
}
void ROM:: and (const std::string &in, const std::string &out) {
	int temp_out;
	if (validator_parts(out))
		temp_out = return_by_string(out).to_int();
	else if (validator_reg(out))
		temp_out = return_reg_by_string(out).to_int();
	else if (validator_title(out))
		temp_out = data.return_by_string(out).to_int();
	else
		temp_out = std::atoi(out.c_str());

	if
		(validator_parts(in)) return_by_string(in) &= temp_out;
	else if
		(validator_reg(in))	  return_reg_by_string(in) &= temp_out;
	else if
		(validator_title(in)) data.return_by_string(in) &= temp_out;
	else {}
}
bool ROM::cmp(const std::string &in, const std::string &out) {
	int temp_in, temp_out;
	if (validator_parts(in))
		temp_in = return_by_string(in).to_int();
	else if (validator_reg(in))
		temp_in = return_reg_by_string(in).to_int();
	else if (validator_title(in))
		temp_in = data.return_by_string(in).to_int();
	else
		temp_in = std::atoi(out.c_str());

	if (validator_parts(out)) 
		temp_out = return_by_string(out).to_int();
	else if (validator_reg(out))
		temp_out = return_reg_by_string(out).to_int();
	else if (validator_title(out))
		temp_out = data.return_by_string(out).to_int();
	else
		temp_out = std::atoi(out.c_str());

	if (temp_in == temp_out)
		return true;
	else
		return false;
}
void ROM::add_integer(int out, const std::string &in) {
	dword temp(out);
	data.push(temp, in);
}
/**********************************command********************************************/
void ROM::push(const std::string &in) {
	if (validator_title(in))
		Stack.push(data.return_by_string(in));
	else if (validator_parts(in))
		Stack.push(return_by_string(in));
	else if (validator_reg(in))	
		Stack.push(return_reg_by_string(in));
	else
		dword i = std::atoi(in.c_str());
}
void ROM::pop(const std::string &in) {
	if (validator_parts(in)) 
		return_by_string(in) = Stack.pop();
	else if (validator_reg(in))
		return_reg_by_string(in) = Stack.pop();
	else if (validator_title(in))
		data.return_by_string(in) = Stack.pop();
}
/*************************************************************************************/
int ROM::comp(const std::string &input) {
	std::ifstream file(input);
	int count = 0;
	std::string in;
	for (file >> in; !file.eof(); file >> in) {
		++count;
		if (in == "dword") {
			file >> in;
			dword temp(0);
			data.push(temp, in);
		}
		else if (validator_command_double(in)) {
			file >> in;
			if (!validator_title(in) && !validator_parts(in) && !validator_reg(in) && !isint(in)) {
				std::cout << "Unknown in: <" << in << "> in string " << count << std::endl;
				return false;
			}
			file >> in;
			if (!validator_title(in) && !validator_parts(in) && !validator_reg(in) && !isint(in)) {
				std::cout << "Unknown out: <" << in << "> in string " << count << std::endl;
				return false;
			}
		}
		else if (validator_command(in)) {
			file >> in; 
			if (!validator_title(in) && !validator_parts(in) && !validator_reg(in) && !isint(in)) {
				std::cout << "Unknown in: <" << in << "> in string " << count << std::endl;
				return false;
			}
		}
		else if (in == "out" || in == "jmp" || in == "jne" || in == "label") {}
		else {
			std::cout << "Unknown command: <" << in << "> in string " << count << std::endl;
			return false;
		}
	}
	for (; data.return_size() != 0; )
		data.pop();
	std::cout << "comp. completed. Strings in file: " << count << std::endl;
	return count;
}
bool ROM::parser(const std::string &input) {
	std::string in, out;
	if (validator_command_double(input)) {
		std::cin >> in >> out;
		if (input == "mov") mov(in, out);
		else if (input == "add") add(in, out);
		else if (input == "sub") sub(in, out);
		else if (input == "cmp") cmp(in, out);
		else if (input == "xor") xor (in, out);
		else if (input == "dec") add(in, "1");
		else if (input == "inc") sub(in, "1");
		else if (input == "and") and (in, out);
		return true;
	}
	else if (validator_command(input)) {
		std::cin >> in;
		if (input == "push") push(in);
		else if (input == "pop") pop(in);
		else if (input == "dword") add_integer(0, in);
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
	else if (input == "open") file_parser();
	else if (input == "exit") return false;
	else std::cout << "Try again" << std::endl;
}
bool ROM::file_parser() {
	std::string in, out, label, input;
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
		for (file >> input; !file.eof(); file >> input) {
			if (validator_command_double(input)) {
				file >> in >> out;
				if (input == "mov") mov(in, out);
				else if (input == "add")
					add(in, out);
				else if (input == "sub")
					sub(in, out);
				else if (input == "xor") 
					xor (in, out);
				else if (input == "and") 
					and (in, out);
				else if (input == "dec") 
					add(in, "1");
				else if (input == "inc") 
					sub(in, "1");
				else if (input == "cmp") {
					file >> label;
					int temp = file.tellg();
					if (label == "jne") {
						if (cmp(in, out)) {
							file.seekg(-((int)file.tellg() - lbl), std::ios_base::cur);
						}
					}
					else {
						file.seekg(-((int)file.tellg() - temp), std::ios_base::cur);
					}
				}
			}
			else if (validator_command(input)) {
				file >> in;
				if (input == "push") 
					push(in);
				else if (input == "pop") 
					pop(in);
				else if (input == "dword") 
					add_integer(0, in);
			}
			else if (input == "label") 
				lbl = file.tellg();
			else if (input == "jmp") 
				file.seekg(-((int)file.tellg() - lbl), std::ios_base::cur);
			else if (input == "out") {
				std::cout << "EAX: " << EAX << std::endl <<
					"EBX: " << EBX << std::endl <<
					"ECX: " << ECX << std::endl <<
					"EDX: " << EDX << std::endl << std::endl;
			}
			else if (input == "open") {
				file_parser();
			}
		}
		std::cout << "Finished.\n";
		return true;
	}
	return false;
}
/*************************************************************************************/
bool ROM::validator_parts(const std::string &in) {
	if (in == "AH" || in == "BH" || in == "AL" || in == "BL" || in == "CL" || in == "DL" || in == "CH" || in == "DH")
		return true;
	else return false;
}
bool ROM::validator_reg(const std::string &in) {
	if (in == "EAX" || in == "EBX" || in == "ECX" || in == "EDX")
		return true;
	else return false;
}
bool ROM::validator_command_double(const std::string &in) {
	if (in == "mov" || in == "add" || in == "sub" || in == "cmp" || in == "xor" ||
		in == "and")
		return true;
	else return false;
}
bool ROM::validator_command(const std::string &in) {
	if (in == "push" || in == "pop" || in == "dec" || in == "inc" || in == "dword")
		return true;
	else return false;
}
bool ROM::validator_title(const std::string &in) {
	return data.validator(in);
}
bool ROM::isint(const std::string &in) {
	int i= 0;
	if (in[0] == '-') {
		++i;
	}
	for (i; i < in.size(); ++i) {
		if (!isdigit(in[i]))
			return false;
	}
	return true;
}
