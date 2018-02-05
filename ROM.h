#pragma once
#include "header.h"
#include "byte.h"
#include "word.h"
#include "dword.h"
#include "data_block.h"
#include "RAM.h"
/*!
	\brief Класс симуляции

	Реализация работы с регистрами и обработка входящих данных
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
	\brief Возврат значения.
	Возвращает байт по строке
	\param title Возвращает ссылку на байт для пользования
	*/
	byte &return_by_string(const std::string &);
	/*!
	\brief Возврат значения.
	Возвращает регистр по строке
	\param title Возвращает ссылку на dword для пользования
	*/
	dword &return_reg_by_string(const std::string &);
	dword &return_cr_reg_by_string(const std::string &);
	/*!
	\brief Пересылка данных.
	mov приемник, источник. 
	Базовая команда пересылки данных. Копирует содержимое источника в приемник, источник не изменяется.
	\param in приемник
	\param out источник
	*/
	void mov(const std::string &, const std::string &);
	/*!
	\brief Сложение данных.
	add приемник, источник.
	Складывает содержимое источника и приемника, результат записывается в приемник, источник не изменяется.
	\param in приемник
	\param out источник
	*/
	void add(const std::string &, const std::string &);
	/*!
	\brief Вычитание данных.
	sub приемник, источник.
	Вычитает содержимое источника из приемника, результат записывается в приемник, источник не изменяется.
	\param in приемник
	\param out источник
	*/
	void sub(const std::string &, const std::string &);
	/*!
	\brief Операция xor.
	xor приемник, источник.
	Выполняет операцию xor источника и приемника, результат записывается в приемник, источник не изменяется.
	\param in приемник
	\param out источник
	*/
	void xor(const std::string &, const std::string &);
	/*!
	\brief Операция and.
	and приемник, источник.
	Выполняет операцию and источника и приемника, результат записывается в приемник, источник не изменяется.
	\param in приемник
	\param out источник
	*/
	void and(const std::string &, const std::string &);
	/*!
	\brief Пересылка данных.
	cmp приемник, источник.
	Выполняет операцию сравнения источника и приемника, результат не изменяется, источник не изменяется.
	\param in приемник
	\param out источник
	\return 1 - равны, иначе - 0
	*/
	bool cmp(const std::string &, const std::string &);
	void add_integer(int, const std::string &);
	/*!
	\brief Запись в RAM.
	push источник.
	Записывает значение во временную память.
	\param in источник
	*/
	void push(const std::string &);
	/*!
	\brief Возврат из RAM.
	pop приемник.
	Возвращает значение из временной памяти.
	\param in приемник
	\return Байт, слово, или двйоное слово
	*/
	void pop(const std::string &);
	void call(int);
	int comp(const std::string &);
	bool parser(const std::string &);
	bool file_parser();
	/*!
	\brief Проверка названия.
	Проверяет наличие названия части регистра
	*/
	bool validator_parts(const std::string &);
	/*!
	\brief Проверка названия.
	Проверяет наличие названия регистра
	*/
	bool validator_reg(const std::string &);
	/*!
	\brief Проверка названия.
	Проверяет наличие названия регистра
	*/
	bool validator_cr_reg(const std::string &);
	/*!
	\brief Проверка названия.
	Проверяет наличие названия функции с двумя переменными
	*/
	bool validator_command_double(const std::string &);
	/*!
	\brief Проверка названия.
	Проверяет наличие названия функции с одной переменной
	*/
	bool validator_command(const std::string &);
	/*!
	\brief Проверка названия.
	Проверяет наличие названия пользовательской переменной
	*/
	bool validator_title(const std::string &);
	bool validator_callret_title(const std::string &);
	/*!
	\brief Проверка названия.
	Проверяет наличие названия метки
	*/
	bool validator_labels(const std::string &);
	/*!
	\brief Проверка на тип.
	Проверяет является ли объект int
	*/
	bool isint(const std::string &);
	void parity(const std::string &);
	void zero(const std::string &in);
	void flags_check(const std::string &in);
};

std::ostream & operator<<(std::ostream &out, dword &rhs);


