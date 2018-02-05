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
	/*!
	\brief ���������� �������.
	����������� ������ electors
	*/
	void inc_electors();
	/*!
	\brief ���������� �������.
	����������� ������ data
	*/
	void inc_data(int);
	/*!
	\brief ������ ������
	���������� ����������� ������ � ���������� � ����
	*/
	void push(const byte &);
	void push(const dword &);
	void push(const word &);
	//void push(word &);
	/*!
	\brief ������� ������
	���������� ������ � ����� �������
	*/
	int pop();
	void print_stack();
	/*!
	\brief ���������
	���������� ������ �� ���������� � ��� ����
	*/
	int elections(int);
	void kill_electors();
	/*!
	\brief ��������
	�������� ���������� � ���� ������
	*/
	void kill_elector(int);
	void dec_data(int);
	void print_electors();
	/*!
	\brief ����������
	��������� ������ ���� dword
	*/
	int make_dword();
	/*!
	\brief ����������
	��������� ������ ���� word
	*/
	int make_word();
	/*!
	\brief ����������
	��������� ������ ���� byte
	*/
	int make_byte();

};
