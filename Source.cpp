#include "header.h"
#include "saver_registers.h"
int main()
{
	saver_registers one;
	std::string input;
	while (input != "exit") {
		system("cls");
		std::cin >> input;
		one.parser(input);
		system("pause");
	}

	
		/*byte a(2);
		byte b(5);
		a += b;
		std::cout << a << std::endl;*/
	
	

	


}