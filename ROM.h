#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"
#include "dword.h"
#include "data_block.h"
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
	data_block data;
public:
	/*!
	\brief ������� ��������

	���������� ���� �� ������
	*/
	byte &return_by_string(const std::string &);
	/*!
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
	void mov(const std::string &, const std::string &);
	void add(const std::string &, const std::string &);
	void xor(const std::string &, const std::string &);
	void and(const std::string &, const std::string &);
	void sub(const std::string &, const std::string &);
	bool cmp(const std::string &, const std::string &);
	bool parser(const std::string &);
	void push(const std::string &);
	void pop(const std::string &);
	bool validator_parts(const std::string &);
	bool validator_reg(const std::string &);
	bool validator_command_double(const std::string &);
	bool validator_command(const std::string &);
	bool ROM::validator_title(const std::string &);
	bool file_parser();
	int comp(const std::string &);
	void add_integer(int, const std::string &);
};

std::ostream & operator<<(std::ostream &out, dword &rhs);


