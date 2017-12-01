#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"

/*!
\brief Стек
\warning Временная версия для тестирования некоторых функций

Реализация стека
*/

class stack {
	byte *data;
	size_t size;
	size_t top;
	size_t *pushed; ///< 1 - byte
					///< 2 - word
	size_t pushed_top;

public:
	stack(int = 1024);
	void push(const byte &); 
	void push(word &);
	byte pop();
	void print_stack();
	size_t return_pushed_top();
};
