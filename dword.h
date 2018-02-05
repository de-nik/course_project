#pragma once
#include "header.h"
#include "byte.h"

class dword {
	byte array_of_bytes[4];
public:
	dword(int);
	dword();
	dword &operator =(const dword&);
	dword &operator =(int);
	void flip(size_t);
	void reset();
	bool operator== (const dword&) const;
	dword &operator += (const dword&);
	dword &operator += (int);
	dword &operator -= (const dword&);
	dword &operator -= (int);
	int to_int() const;
	~dword();
	void flip();
	bool getbit(int) const;
	void setbit(int, bool);
	byte return_byte(size_t) const;
	byte & return_byte(size_t);
	dword(const byte&, const byte&, const byte&, const byte&);
	dword& operator ^=(const dword&);
	dword& operator &=(const dword&);
	bool parity();
};

std::ostream & operator<<(std::ostream &out, dword &rhs);