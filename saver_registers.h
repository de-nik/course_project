#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"
#include "dword.h"
#include "stack.h"
/*!
	\brief Класс симуляции

	Реализация работы с регистрами и обратока входящих данных
	*/
class saver_registers
{
	dword EAX;
	dword EBX;
	stack Stack;
public:
	/*!
	\brief Возврат значения

	Возвращает байт по строке
	*/
	byte &return_by_string(const std::string &title);/*!
	\brief Возврат значения

	Возвращает регистр по строке
	*/
	dword &return_reg_by_string(const std::string &title);
	/*!
	\brief Пересылка данных
		MOV приемник, источник 
			Базовая команда пересылки данных. Копирует содержимое источника в приемник, источник не изменяется. 
	\param регистр
	*/
	dword mov_reg(const std::string &in, const std::string &out);
	/*!
	\brief Пересылка данных
		MOV приемник, источник
			Базовая команда пересылки данных. Копирует содержимое источника в приемник, источник не изменяется.
	\param регистр
	*/
	dword mov_reg(const std::string &in, int out);

	byte mov(const std::string &in, const std::string &out);
	byte mov(const std::string &in, int out);
	byte add(const std::string &in, const std::string &out);
	byte add(const std::string &in, int out);
	byte sub(const std::string &in, const std::string &out);
	byte sub(const std::string &in, int out);
	bool cmp(const std::string &in, const std::string &out); 
	void input_mov();
	void input_add();
	void input_sub();
	void input_cmp();
	bool parser(const std::string &);
	void push(const std::string &); 
	void pop();

};

std::ostream & operator<<(std::ostream &out, dword &rhs);


