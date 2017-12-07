#pragma once
#include "header.h"
/*!
\brief Байт

Реализация машинного байта
*/
class byte
{
private:
	unsigned char array_of_bytes; ///< Интерпритация машинного байта
public:
	/*!
		\brief Пользовательский конструктор

	*/
	byte(int);
	/*!
		\brief Базовый конструктор

	*/
	byte();
	/*!
		\brief Оператор присваивания

		Присваивает значение другого байта
	*/
	byte &operator =(const byte&);
	/*!
		\brief Оператор присваивания

		Присваивает значение переменной байту
	*/
	byte &operator =(int);
	/*!
		\brief Инверсия

		Инвертирует байт
	*/
	void flip();
	/*!
		\brief Инверсия

		Инвертирует выбранный бит
	*/
	void flip(size_t);
	/*!
	\brief Сброс

	Обнуляет байт
	*/
	void reset();
	/*!
	\brief Оператор сравнения

	Возвращает 1, если объекты равны и 0, если нет
	*/
	bool operator== (const byte&) const;
	/*!
	\brief Оператор сравнения

	Возвращает 0, если объекты равны и 1, если нет
	*/
	bool operator!= (const byte&) const;
	/*!
	\brief Оператор сложения и равенства

	Складывает со значением принимаемого байта и присваивает текущему
	*/
	byte &operator += (const byte&);
	/*!
	\brief Оператор присваивания

	Складывает со значением переменной и присваивает текущему байту
	*/
	byte &operator += (int);
	/*!
	\brief Оператор вычитания и равенства

	Вычитает значение принимаемого байта и присваивает текущему
	*/
	byte &operator -= (const byte&);
	/*!
	\brief Оператор вычитания и равенства

	Вычитает значение принимаемой переменной и присваивает текущему байту
	*/
	byte &operator -= (int);
	/*!
	\brief Приведение

	Приведение к int
	*/
	int to_int() const;
	~byte();
	/*!
	\brief Получение бита

	Возвращает выбранный бит
	*/
	bool getbit(int) const;
	/*!
	\brief Установка бита

	Устанавливает выбранный бит в 0 или 1
	*/
	void setbit(int, bool);
	/*!
	\brief Возврат значения
	
	*/
	unsigned char return_array() const;
	/*!
	\brief Возврат значения

	Возврат для изменения по ссылке
	*/
	unsigned char &return_array();
	byte& operator &=(const byte&);
};

std::ostream & operator<<(std::ostream &out, byte &rhs);