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

byte stack::pop(const byte& ptr)
{
	--pushed_top;
	return data[--top]; 
}

word stack::pop(const word& ptr)
{
	word temp(data[top], data[top-1]);
	top -= 2;
	--pushed_top;
	return temp;
}

void stack::print_stack()
{
	for (int i = top - 1; i >= 0; i--)
		std::cout << "|" << std::setw(4) << data[i] << std::endl;
}

void stack::pop() {
	pop(data[top]);
}
