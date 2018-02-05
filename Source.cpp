#include "header.h"
#include "ROM.h"
#include "word.h"
#include "dword.h"
#include "data_block.h"


int main()
{
	ROM one;
	std::string input;
	while (input != "exit") {
		std::cout << "List of avaible command: " << std::endl 
				  << "mov, add, sub, cmp, push, pop, out, xor, and, dec, inc \nInteger: dword <title> \nRun code from file: open <filename>" << std::endl;
		std::cin >> input;
		one.parser(input);
		system("pause");
		system("cls");
	}
}