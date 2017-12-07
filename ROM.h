#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"
#include "dword.h"
#include "RAM.h"
/*!
	\brief ����� ���������

	���������� ������ � ���������� � �������� �������� ������
	*/
class ROM
{
	dword EAX;
	dword EBX;
	dword ECX;
	dword EDX;
	RAM Stack;
public:
	/*!
	\brief ������� ��������

	���������� ���� �� ������
	*/
	byte &return_by_string(const std::string &);/*!
	\brief ������� ��������

	���������� ������� �� ������
	*/
	dword &return_reg_by_string(const std::string &);
	/*!
	\brief ��������� ������
		MOV ��������, �������� 
			������� ������� ��������� ������. �������� ���������� ��������� � ��������, �������� �� ����������. 
	\param �������
	*/
	void mov(const std::string &, const std::string &, int);
	void mov(const std::string &, int, int);
	void add(const std::string &, const std::string &, int);
	void add(const std::string &, int, int);
	void xor(const std::string &, const std::string &, int);
	void xor(const std::string &, int, int); 
	void and(const std::string &, const std::string &, int);
	void and(const std::string &, int, int);
	void input_xor(const std::string &in, const std::string &out);
	void input_and(const std::string &in, const std::string &out);
	void sub(const std::string &, const std::string &, int);
	void sub(const std::string &, int, int);
	bool cmp(const std::string &, const std::string &); 
	void input_mov(const std::string &, const std::string &);
	void input_add(const std::string &, const std::string &);
	void input_sub(const std::string &, const std::string &);
	bool input_cmp(const std::string &, const std::string &);
	bool parser(const std::string &);
	void push(const std::string &); 
	void pop(const std::string &);
	bool validator_parts(const std::string &);
	bool validator_reg(const std::string &);
	bool validator_command(const std::string &);
	bool file_parser();
	int comp(const std::string &);
};

std::ostream & operator<<(std::ostream &out, dword &rhs);


