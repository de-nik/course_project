#include "header.h"
#include "ROM.h"
#include "word.h"
#include "dword.h"
#include "data_block.h"
std::ostream & operator<<(std::ostream &out, word &rhs)
{
	for (int i = 15; i >= 0; --i)
		out << rhs.getbit(i);
	return out;
}

int main()
{
	ROM one;
	std::string input;
	while (input != "exit") {
		std::cout << "List of avaible command: " << std::endl 
				  << "mov, add, sub, cmp, push, pop, out, xor, and, dec, inc, open (+ jmp, jne)" << std::endl;
		std::cin >> input;
		one.parser(input);
		system("pause");
		system("cls");
	}

	/*data_block a;
	dword b(7);
	a.push(b, "first");
	a.push(b, "second");
	a.push(b, "3");
	a.push(b, "4");
	a.print_stack();*/
	
	
	
}