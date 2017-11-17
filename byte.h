#pragma once
#include "header.h"
class byte
{
private:
	unsigned char array_of_bytes;
public:
	void setbit(int, bool);
	byte(int);
	byte();
	byte &operator =(const byte&);
	byte &operator =(int);
	bool getbit(int) const;
	void reset();
	void flip();
	void flip(size_t);
	bool operator== (const byte&) const;
	bool operator!= (const byte&) const;
	byte &operator += (const byte&);
	byte &operator += (int);
	byte &operator -= (const byte&);
	byte &operator -= (int);
	int to_int() const;
	~byte();
};

