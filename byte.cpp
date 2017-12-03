#include "byte.h"

std::ostream & operator<<(std::ostream &out, byte &rhs)
{
	for (int i = 7; i >= 0; --i)
		out << rhs.getbit(i);
	return out;
}

byte::byte() {
	for (int i = 0; i < 8; ++i) {
		setbit(i, 0);
	}
}

int byte::to_int() const {
	int res = 0;

	if (getbit(0)) {
		++res;
		for (int i = 0; i < 8; ++i) {
			if (!getbit(i))
				res += (int)pow(2, 7 - i);
		}
		return -res;
	}

	else {
		for (int i = 8 - 1; i > 0; --i) {
			if (getbit(i))
				res += (int)pow(2, 7 - i);
		}
	}
	return res;

}

byte::byte(int val)
{
	int tmp = val;

	for (int i = 0; i < 8; ++i)
	{
		if (val % 2)
			setbit(i, 1);
		else
			setbit(i, 0);
		val = val / 2;
	}

	if (tmp < 0) {
		flip();
		flip(0);
		if (!getbit(0))
			for (int i = 7; !getbit(7 - i); --i)
			{
					flip(8 - i);
			}
	}
}

void byte::reset()
{
	for (size_t i = 0; i < 8; ++i)
	{
		setbit(i, 0);
	}
}

void byte::flip()
{
	for (size_t i = 0; i < 8; i++)
	{
		setbit(i, !getbit(i));
	}
}

bool byte::operator== (const byte& rhs) const
{
	for (int i = 0; i < 8; ++i)
	{
		if (getbit(i) != rhs.getbit(i))
			return false;
	}
	return true;
}

bool byte::operator!= (const byte& rhs) const
{
	for (int i = 0; i < 8; ++i)
	{
		if (getbit(i) != rhs.getbit(i))
			return true;
	}
	return false;
}

byte& byte::operator += (int rhs) {
	int val = to_int() + rhs;
	int tmp = val;
	for (int i = 0; i < 8; ++i)
	{
		if (val % 2)
			setbit(i, 1);
		else
			setbit(i, 0);
		val = val / 2;
	}

	if (tmp < 0) {
		flip();
		flip(0);
		if (!getbit(0))
			for (int i = 7; !getbit(7 - i); --i)
			{
				flip(8 - i);
			}
	}
	return *this;
}

byte& byte::operator -= (const byte& rhs) {
	for (int i = 7; i >= 0; --i)
		setbit(i, (rhs.getbit(i) != getbit(i)));
	return *this;
}

byte& byte::operator -= (int rhs) {
	int val = to_int() - rhs;
	int tmp = val;
	for (int i = 0; i < 8; ++i)
	{
		if (val % 2)
			setbit(i, 1);
		else
			setbit(i, 0);
		val = val / 2;
	}

	if (tmp < 0) {
		flip();
		flip(0);
		if (!getbit(0))
			for (int i = 7; !getbit(7 - i); --i)
			{
				flip(8 - i);
			}
	}
	return *this;
}

byte& byte::operator =(int val) {
	reset();
	int tmp = val;
	for (int i = 0; i < 8; ++i)
	{
		if (val % 2)
			setbit(i, 1);
		else
			setbit(i, 0);
		val = val / 2;
	}

	if (tmp < 0) {
		flip();
		flip(0);
		if (!getbit(0))
			for (int i = 7; !getbit(7 - i); --i)
			{
				flip(8 - i);
			}
	}
	return *this;
}

byte& byte::operator += (const byte& rhs) {
	for (int i = 7; i >= 0; --i)
		setbit(i, (rhs.getbit(i) != getbit(i)));
	return *this;
}

byte& byte::operator =(const byte& rhs) {
	for (size_t i = 0; i <= 7; ++i)
		setbit(i, rhs.getbit(i));
	return *this;
}

byte::~byte() {

}

void byte::flip(size_t index)
{
	setbit(index, !getbit(index));
}


bool byte::getbit(int index) const
{
	return array_of_bytes >> index & 1;
}

void byte::setbit(int index, bool newval)
{
	if (newval)
		array_of_bytes |= 1 << index;
	else
		array_of_bytes &= ~(1 << index);
}

unsigned char byte::return_array() const{
	return array_of_bytes;
}

unsigned char & byte::return_array() {
	return array_of_bytes;
}