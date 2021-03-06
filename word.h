#pragma once
#include "header.h"
#include "byte.h"

class word {
	byte array_of_bytes[2];
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
	byte return_byte(size_t) const;
	byte & return_byte(size_t);
	word(const byte&, const byte&);
	word& operator ^=(const word&);
	word& operator &=(const word&);
	bool parity();
};

std::ostream & operator<<(std::ostream &out, word &rhs);