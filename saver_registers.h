#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"
#include "registers.h"
#include "stack.h"
/*!
	\brief ����� ���������

	���������� ������ � ���������� � �������� �������� ������
	*/
class saver_registers
{
	registers EAX;
	registers EBX;
	stack Stack;
public:
	/*!
	\brief ������� ��������

	���������� ���� �� ������
	*/
	byte &return_by_string(const std::string &title);/*!
	\brief ������� ��������

	���������� ������� �� ������
	*/
	registers &return_reg_by_string(const std::string &title);
	/*!
	\brief ��������� ������
		MOV ��������, �������� 
			������� ������� ��������� ������. �������� ���������� ��������� � ��������, �������� �� ����������. 
	\param �������
	*/
	registers mov_reg(const std::string &in, const std::string &out);
	/*!
	\brief ��������� ������
		MOV ��������, ��������
			������� ������� ��������� ������. �������� ���������� ��������� � ��������, �������� �� ����������.
	\param �������
	*/
	registers mov_reg(const std::string &in, int out);

	byte mov(const std::string &in, const std::string &out);
	byte mov(const std::string &in, int out);
	byte add(const std::string &in, const std::string &out);
	byte add(const std::string &in, int out);
	byte sub(const std::string &in, const std::string &out);
	byte sub(const std::string &in, int out);
	bool cmp(const std::string &in, const std::string &out);
	bool parser(const std::string &input);
	void push(const std::string &); 
	void pop(const std::string &);

};



