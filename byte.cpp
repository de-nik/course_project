#include "byte.h"
byte::byte() {
	for (int i = 0; i < 8; ++i) {
		setbit(i, 0);
	}
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
byte::~byte() {

}
byte& byte::operator += (const byte& in) {
	for (int i = 7; i >= 0; --i)
		setbit(i, (in.getbit(i) != getbit(i)));
	return *this;
}
byte& byte::operator += (int in) {
	int val = to_int() + in;
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
byte& byte::operator -= (const byte& in) {
	for (int i = 7; i >= 0; --i)
		setbit(i, (in.getbit(i) != getbit(i)));
	return *this;
}
byte& byte::operator -= (int in) {
	int val = to_int() - in;
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
byte& byte::operator =(const byte& in) {
	for (size_t i = 0; i <= 7; ++i)
		setbit(i, in.getbit(i));
	return *this;
}
byte& byte::operator =(int in) {
	reset();
	int tmp =in;
	for (int i = 0; i < 8; ++i)
	{
		if (in % 2)
			setbit(i, 1);
		else
			setbit(i, 0);
		in = in / 2;
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
byte& byte::operator^=(const byte& in) {
	for (int i = 7; i >= 0; --i) {
		if (in.getbit(i) == getbit(i)) {
			setbit(i, 0);
		}
		else
			setbit(i, 1);
	}
	return *this;
}
byte& byte::operator&=(const byte& in) {
	for (int i = 7; i >= 0; --i) {
		if (in.getbit(i) == 1 && getbit(i) == 1) {
			setbit(i, 1);
		}
		else
			setbit(i, 0);
	}
	return *this;
}
int byte::to_int() const {
	int res = 0;
	byte temp = *this;
	if (getbit(7)) {
		if (getbit(0))
			for (int i = 7; !getbit(7 - i); --i)
			{
				temp.flip(8 - i);
			}
		temp.flip(0);
		temp.flip();
		for (int i = 0; i <= 7; ++i) {
			if (temp.getbit(i))
				res += (int)pow(2, i);
		}
		return -res;
	}

	else {
		for (int i = 0; i <= 7 ; ++i) {
			if (getbit(i))
				res += (int)pow(2, i);
		}
	}
	return res;

}
void byte::reset()
{
	for (size_t i = 0; i < 8; ++i)
	{
		setbit(i, 0);
	}
}
void byte::flip(size_t index)
{
	setbit(index, !getbit(index));
}
void byte::flip()
{
	for (size_t i = 0; i < 8; i++)
	{
		setbit(i, !getbit(i));
	}
}
void byte::setbit(int index, bool newval)
{
	if (newval)
		array_of_bytes |= 1 << index;
	else
		array_of_bytes &= ~(1 << index);
}
bool byte::getbit(int index) const
{
	return array_of_bytes >> index & 1;
}
bool byte::operator== (const byte& in) const
{
	for (int i = 0; i < 8; ++i)
	{
		if (getbit(i) != in.getbit(i))
			return false;
	}
	return true;
}
unsigned char byte::return_array() const{
	return array_of_bytes;
}
unsigned char & byte::return_array() {
	return array_of_bytes;
}
std::ostream & operator<<(std::ostream &out, byte &in)
{
	for (int i = 7; i >= 0; --i)
		out << in.getbit(i);
	return out;
}