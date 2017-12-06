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
	byte &return_by_string(const std::string &title);/*!
	\brief ������� ��������

	���������� ������� �� ������
	*/
	dword &return_reg_by_string(const std::string &title);
	/*!
	\brief ��������� ������
		MOV ��������, �������� 
			������� ������� ��������� ������. �������� ���������� ��������� � ��������, �������� �� ����������. 
	\param �������
	*/
	dword mov_reg(const std::string &in, const std::string &out);
	/*!
	\brief ��������� ������
		MOV ��������, ��������
			������� ������� ��������� ������. �������� ���������� ��������� � ��������, �������� �� ����������.
	\param �������
	*/
	dword mov_reg(const std::string &in, int out);

	byte mov(const std::string &in, const std::string &out);
	byte mov(const std::string &in, int out);
	byte add(const std::string &in, const std::string &out);
	byte add(const std::string &in, int out);
	byte sub(const std::string &in, const std::string &out);
	byte sub(const std::string &in, int out);
	bool cmp(const std::string &in, const std::string &out); 
	void input_mov(const std::string &, const std::string &);
	void input_add(const std::string &, const std::string &);
	void input_sub(const std::string &, const std::string &);
	void input_cmp(const std::string &, const std::string &);
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


