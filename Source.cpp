#include "header.h"
#include "saver_registers.h"
#include "word.h"
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

	
	//	word a(60000);
	//	a.setbit(15, 1);
	////	byte b(5);
	//	//a += b;
	//	std::cout << a << std::endl;
	
	
	stack a;
	byte b(5);
	byte c(7);

	a.push(b);
	a.push(c);

	a.print_stack();

	a.pop();
	a.print_stack();

}