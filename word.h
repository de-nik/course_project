#pragma once
#include "header.h"
#include "byte.h"

class word {
	unsigned char array_of_bytes[2];
public:
	word(int);
	word();
	word &operator =(const word&);
	word &operator =(int);
	void flip(size_t);
	void reset();
	bool operator== (const word&) const;
	bool operator!= (const word&) const;
	word &operator += (const word&);
	word &operator += (int);
	word &operator -= (const word&);
	word &operator -= (int);
	int to_int() const;
	~word();
	void flip();
	bool getbit(int) const;
	void setbit(int, bool);

};