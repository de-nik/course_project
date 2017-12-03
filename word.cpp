#include "word.h"
word::word() {
	array_of_bytes[0] = 0;
	array_of_bytes[1] = 0;
}

int word::to_int() const {
	int res = 0;

	if (getbit(0)) {
		++res;
		for (int i = 0; i < 16; ++i) {
			if (!getbit(i))
				res += (int)pow(2, 15 - i);
		}
		return -res;
	}

	else {
		for (int i = 16 - 1; i > 0; --i) {
			if (getbit(i))
				res += (int)pow(2, 15 - i);
		}
	}
	return res;

}

word::word(int val)
{
	int tmp = val;

	for (int i = 0; i < 16; ++i)
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
			for (int i = 15; !getbit(15 - i); --i)
			{
				flip(16 - i);
			}
	}
}

void word::reset()
{
	for (size_t i = 0; i < 16; ++i)
	{
		setbit(i, 0);
	}
}

void word::flip()
{
	for (size_t i = 0; i < 16; i++)
	{
		setbit(i, !getbit(i));
	}
}

bool word::operator== (const word& rhs) const
{
	for (int i = 0; i < 16; ++i)
	{
		if (getbit(i) != rhs.getbit(i))
			return false;
	}
	return true;
}

bool word::operator!= (const word& rhs) const
{
	for (int i = 0; i < 16; ++i)
	{
		if (getbit(i) != rhs.getbit(i))
			return true;
	}
	return false;
}

word& word::operator += (int rhs) {
	int val = to_int() + rhs;
	int tmp = val;
	for (int i = 0; i < 16; ++i)
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
			for (int i = 15; !getbit(15 - i); --i)
			{
				flip(16 - i);
			}
	}
	return *this;
}

word& word::operator -= (const word& rhs) {
	for (int i = 15; i >= 0; --i)
		setbit(i, (rhs.getbit(i) != getbit(i)));
	return *this;
}

word& word::operator -= (int rhs) {
	int val = to_int() - rhs;
	int tmp = val;
	for (int i = 0; i < 16; ++i)
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
			for (int i = 15; !getbit(15 - i); --i)
			{
				flip(16 - i);
			}
	}
	return *this;
}

word& word::operator =(int val) {
	reset();
	int tmp = val;
	for (int i = 0; i < 16; ++i)
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
			for (int i = 15; !getbit(15 - i); --i)
			{
				flip(16 - i);
			}
	}
	return *this;
}

word& word::operator += (const word& rhs) {
	for (int i = 15; i >= 0; --i)
		setbit(i, (rhs.getbit(i) != getbit(i)));
	return *this;
}

word& word::operator =(const word& rhs) {
	for (size_t i = 0; i <= 15; ++i)
		setbit(i, rhs.getbit(i));
	return *this;
}

word::~word() {

}

void word::flip(size_t index)
{
	setbit(index, !getbit(index));
}


bool word::getbit(int index) const
{
	if(index < 8)
		return array_of_bytes[0].return_array() >> index & 1;
	else 
		return array_of_bytes[1].return_array() >> index - 8 & 1;
}

void word::setbit(int index, bool newval)
{
	if (newval && index < 8) {
		array_of_bytes[0].return_array() |= 1 << index;
	}
	else if (newval && index > 7) {
		array_of_bytes[1].return_array() |= 1 << index - 8;
	}
	else if (!newval && index < 8) {
		array_of_bytes[0].return_array() &= ~(1 << index);
	}
	else {
		array_of_bytes[1].return_array() &= ~(1 << index - 8);
	}
}

byte word::return_byte(size_t number) {
	return array_of_bytes[number];
}

word::word(const byte& first, const byte& second) {
	array_of_bytes[0] = first;
	array_of_bytes[1] = second;
}