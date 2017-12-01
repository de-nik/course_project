#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"


class stack {
	byte *data;
	size_t size;
	size_t top;
	size_t *pushed; // 1 - byte
					// 2 - word
	size_t pushed_top;

public:
	stack(int = 10);
	void push(const byte &); 
	void push(word &);
	byte pop(const byte&);
	word pop(const word&);
	void print_stack();
	void pop();
};
