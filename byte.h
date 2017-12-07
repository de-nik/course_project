#pragma once
#include "header.h"
/*!
\brief ����

���������� ��������� �����
*/
class byte
{
private:
	unsigned char array_of_bytes; ///< ������������� ��������� �����
public:
	/*!
		\brief ���������������� �����������

	*/
	byte(int);
	/*!
		\brief ������� �����������

	*/
	byte();
	/*!
		\brief �������� ������������

		����������� �������� ������� �����
	*/
	byte &operator =(const byte&);
	/*!
		\brief �������� ������������

		����������� �������� ���������� �����
	*/
	byte &operator =(int);
	/*!
		\brief ��������

		����������� ����
	*/
	void flip();
	/*!
		\brief ��������

		����������� ��������� ���
	*/
	void flip(size_t);
	/*!
	\brief �����

	�������� ����
	*/
	void reset();
	/*!
	\brief �������� ���������

	���������� 1, ���� ������� ����� � 0, ���� ���
	*/
	bool operator== (const byte&) const;
	/*!
	\brief �������� ���������

	���������� 0, ���� ������� ����� � 1, ���� ���
	*/
	bool operator!= (const byte&) const;
	/*!
	\brief �������� �������� � ���������

	���������� �� ��������� ������������ ����� � ����������� ��������
	*/
	byte &operator += (const byte&);
	/*!
	\brief �������� ������������

	���������� �� ��������� ���������� � ����������� �������� �����
	*/
	byte &operator += (int);
	/*!
	\brief �������� ��������� � ���������

	�������� �������� ������������ ����� � ����������� ��������
	*/
	byte &operator -= (const byte&);
	/*!
	\brief �������� ��������� � ���������

	�������� �������� ����������� ���������� � ����������� �������� �����
	*/
	byte &operator -= (int);
	/*!
	\brief ����������

	���������� � int
	*/
	int to_int() const;
	~byte();
	/*!
	\brief ��������� ����

	���������� ��������� ���
	*/
	bool getbit(int) const;
	/*!
	\brief ��������� ����

	������������� ��������� ��� � 0 ��� 1
	*/
	void setbit(int, bool);
	/*!
	\brief ������� ��������
	
	*/
	unsigned char return_array() const;
	/*!
	\brief ������� ��������

	������� ��� ��������� �� ������
	*/
	unsigned char &return_array();
	byte& operator &=(const byte&);
};

std::ostream & operator<<(std::ostream &out, byte &rhs);