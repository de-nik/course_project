#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"
#include "dword.h"

class RAM {
	byte *data;
	int size;
	byte *elector;
	int size_elector;
public:
	RAM();
	void inc_electors();
	void inc_data(int);
	void push(const byte &);
	void push(const dword &);
	void push(const word &);
	//void push(word &);
	int pop();
	void print_stack();
	int elections(int);
	void kill_electors();
	void kill_elector(int);
	void dec_data(int);
	void print_electors();
	int make_dword();
	int make_word();
	int make_byte();

};
