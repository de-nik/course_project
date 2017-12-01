#pragma once
#include "header.h"
class byte
{
private:
	unsigned char array_of_bytes;
public:
	byte(int);
	byte();
	byte &operator =(const byte&);
	byte &operator =(int);
	void flip(size_t);
	void reset();
	bool operator== (const byte&) const;
	bool operator!= (const byte&) const;
	byte &operator += (const byte&);
	byte &operator += (int);
	byte &operator -= (const byte&);
	byte &operator -= (int);
	int to_int() const;
	~byte();
	void flip();
	bool getbit(int) const;
	void setbit(int, bool);
	unsigned char return_array() const; 
	unsigned char &return_array();
};

std::ostream & operator<<(std::ostream &out, byte &rhs);