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
	\brief Расширение массива.
	Увеличивает массив electors
	*/
	void inc_electors();
	/*!
	\brief Расширение массива.
	Увеличивает массив data
	*/
	void inc_data(int);
	/*!
	\brief Запись данных
	Записывает принимаемые данные и информацию о типе
	*/
	void push(const byte &);
	void push(const dword &);
	void push(const word &);
	//void push(word &);
	/*!
	\brief Возврат данных
	Возвращает объект в конце массива
	*/
	int pop();
	void print_stack();
	/*!
	\brief Обработка
	Возвращает объект по информации о его типе
	*/
	int elections(int);
	void kill_electors();
	/*!
	\brief Обнуляет
	Обнуляет информацию о типе данных
	*/
	void kill_elector(int);
	void dec_data(int);
	void print_electors();
	/*!
	\brief Формировка
	Формирует объект типа dword
	*/
	int make_dword();
	/*!
	\brief Формировка
	Формирует объект типа word
	*/
	int make_word();
	/*!
	\brief Формировка
	Формирует объект типа byte
	*/
	int make_byte();

};
