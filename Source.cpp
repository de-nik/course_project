#include "header.h"
#include "saver_registers.h"
#include "word.h"
#include "dword.h"
std::ostream & operator<<(std::ostream &out, word &rhs)
{
	for (int i = 15; i >= 0; --i)
		out << rhs.getbit(i);
	return out;
}
int main()
{
	/*saver_registers one;
	std::string input;
	while (input != "exit") {
		system("cls");
		std::cin >> input;
		one.parser(input);
		system("pause");
	}*/

	
		/*dword a(-2147483647);
		std::cout << a << std::endl;
	*/
	
	stack a;
	dword e(1);
	dword b(2);
	dword c(3);
	a.push(e);
	a.push(b);
	a.push(c);
	a.print_electors();
	a.print_stack();
	/*for (size_t i = 0; i < 32; ++i)
	{
		std::cout << (i+3) / 4 << " | " << i << std::endl;
	}*/
}