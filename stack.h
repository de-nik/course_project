#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"
#include "dword.h"

class stack {
	byte *data;
	int size;
	byte *elector;
public:
	stack();
	void push(const byte &);
	void push(const dword &);
	//void push(word &);
	void pop();
	void print_stack();
	void elections(int);
	void kill_electors(int); 
	void print_electors();
};
