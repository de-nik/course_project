#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"
#include "dword.h"
#include "data_block.h"
#include "RAM.h"
/*!
	\brief ����� ���������

	���������� ������ � ���������� � ��������� �������� ������
	*/
class ROM
{
	dword EAX;
	dword EBX;
	dword ECX;
	dword EDX;

	dword CR0;
	dword CR1;
	dword CR2;
	dword CR3;

	byte f_CR0;
	byte f_CR1;
	byte f_CR2;
	byte f_CR3;

	word flags;

	RAM Stack;
	data_block data;
	data_block callret;
	data_block labels;
public:
	/*!
	\brief ������� ��������.
	���������� ���� �� ������
	\param title ���������� ������ �� ���� ��� �����������
	*/
	byte &return_by_string(const std::string &);
	/*!
	\brief ������� ��������.
	���������� ������� �� ������
	\param title ���������� ������ �� dword ��� �����������
	*/
	dword &return_reg_by_string(const std::string &);
	dword &return_cr_reg_by_string(const std::string &);
	/*!
	\brief ��������� ������.
	mov ��������, ��������. 
	������� ������� ��������� ������. �������� ���������� ��������� � ��������, �������� �� ����������.
	\param in ��������
	\param out ��������
	*/
	void mov(const std::string &, const std::string &);
	/*!
	\brief �������� ������.
	add ��������, ��������.
	���������� ���������� ��������� � ���������, ��������� ������������ � ��������, �������� �� ����������.
	\param in ��������
	\param out ��������
	*/
	void add(const std::string &, const std::string &);
	/*!
	\brief ��������� ������.
	sub ��������, ��������.
	�������� ���������� ��������� �� ���������, ��������� ������������ � ��������, �������� �� ����������.
	\param in ��������
	\param out ��������
	*/
	void sub(const std::string &, const std::string &);
	/*!
	\brief �������� xor.
	xor ��������, ��������.
	��������� �������� xor ��������� � ���������, ��������� ������������ � ��������, �������� �� ����������.
	\param in ��������
	\param out ��������
	*/
	void xor(const std::string &, const std::string &);
	/*!
	\brief �������� and.
	and ��������, ��������.
	��������� �������� and ��������� � ���������, ��������� ������������ � ��������, �������� �� ����������.
	\param in ��������
	\param out ��������
	*/
	void and(const std::string &, const std::string &);
	/*!
	\brief ��������� ������.
	cmp ��������, ��������.
	��������� �������� ��������� ��������� � ���������, ��������� �� ����������, �������� �� ����������.
	\param in ��������
	\param out ��������
	\return 1 - �����, ����� - 0
	*/
	bool cmp(const std::string &, const std::string &);
	void add_integer(int, const std::string &);
	/*!
	\brief ������ � RAM.
	push ��������.
	���������� �������� �� ��������� ������.
	\param in ��������
	*/
	void push(const std::string &);
	/*!
	\brief ������� �� RAM.
	pop ��������.
	���������� �������� �� ��������� ������.
	\param in ��������
	\return ����, �����, ��� ������� �����
	*/
	void pop(const std::string &);
	void call(int);
	int comp(const std::string &);
	bool parser(const std::string &);
	bool file_parser();
	/*!
	\brief �������� ��������.
	��������� ������� �������� ����� ��������
	*/
	bool validator_parts(const std::string &);
	/*!
	\brief �������� ��������.
	��������� ������� �������� ��������
	*/
	bool validator_reg(const std::string &);
	/*!
	\brief �������� ��������.
	��������� ������� �������� ��������
	*/
	bool validator_cr_reg(const std::string &);
	/*!
	\brief �������� ��������.
	��������� ������� �������� ������� � ����� �����������
	*/
	bool validator_command_double(const std::string &);
	/*!
	\brief �������� ��������.
	��������� ������� �������� ������� � ����� ����������
	*/
	bool validator_command(const std::string &);
	/*!
	\brief �������� ��������.
	��������� ������� �������� ���������������� ����������
	*/
	bool validator_title(const std::string &);
	bool validator_callret_title(const std::string &);
	/*!
	\brief �������� ��������.
	��������� ������� �������� �����
	*/
	bool validator_labels(const std::string &);
	/*!
	\brief �������� �� ���.
	��������� �������� �� ������ int
	*/
	bool isint(const std::string &);
	void parity(const std::string &);
	void zero(const std::string &in);
	void flags_check(const std::string &in);
};

std::ostream & operator<<(std::ostream &out, dword &rhs);


