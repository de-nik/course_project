#pragma once
#include "header.h"
#include "byte.h"
/*!
\brief ���������� ��������

32-������ ������� ������ ����������
*/
class registers {
protected:
	byte upper_first;
	byte upper_second;
	byte lower_first;
	byte lower_second;
public:
	/*!
	\brief ������� ��������

	������� ����� �� ��������
	*/
	byte &return_byte(size_t option);
};

