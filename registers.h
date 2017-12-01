#pragma once
#include "header.h"
#include "byte.h"
/*!
\brief Реализация регистра

32-битный регистр общего назначения
*/
class registers {
protected:
	byte upper_first;
	byte upper_second;
	byte lower_first;
	byte lower_second;
public:
	/*!
	\brief Возврат значения

	Возврат байта по значению
	*/
	byte &return_byte(size_t option);
};

