#include "stack.h"

stack::stack(int maxSize) 
{
	size = maxSize;
	top = 0;
	data = new byte[size]; 
	pushed = new size_t[size];
}

void stack::push(const byte &value)
{
	data[top++] = value;
	pushed[pushed_top++] = 1;
}

void stack::push(word &value)
{
	data[top++] = value.return_byte(0);
	pushed[pushed_top++] = 2;
}

byte stack::pop()
{
		--pushed_top;
		return data[--top];
}


void stack::print_stack()
{
	for (int i = top - 1; i >= 0; i--)
		std::cout << "|" << std::setw(4) << data[i] << std::endl;
}

size_t stack::return_pushed_top() {
	return pushed_top;
}
