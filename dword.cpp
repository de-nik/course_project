#include "dword.h"
dword::dword() {
	array_of_bytes[0] = 0;
	array_of_bytes[1] = 0;
}
int dword::to_int() const {
	int res = 0;
	dword temp = *this;
	if (getbit(31)) {
		if (getbit(0))
			for (int i = 31; !getbit(31 - i); --i)
			{
				temp.flip(32 - i);
			}
		temp.flip(0);
		temp.flip();
		for (int i = 0; i <= 31; ++i) {
			if (temp.getbit(i))
				res += (int)pow(2, i);
		}
		return -res;
	}

	else {
		for (int i = 0; i <= 31; ++i) {
			if (getbit(i))
				res += (int)pow(2, i);
		}
	}
	return res;
}
dword::dword(int val){
	int tmp = val;

	for (int i = 0; i < 32; ++i)
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
			for (int i = 31; !getbit(31 - i); --i)
			{
				flip(32 - i);
			}
	}
}
void dword::reset(){
	for (size_t i = 0; i < 32; ++i)
	{
		setbit(i, 0);
	}
}
void dword::flip(){
	for (size_t i = 0; i < 32; i++)
	{
		setbit(i, !getbit(i));
	}
}
bool dword::operator== (const dword& rhs) const {
	for (int i = 0; i < 32; ++i){
		if (getbit(i) != rhs.getbit(i))
			return false;
	}
	return true;
}
dword& dword::operator += (int rhs) {
	int val = to_int() + rhs;
	int tmp = val;
	for (int i = 0; i < 32; ++i){
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
			for (int i = 31; !getbit(31 - i); --i) {
				flip(32 - i);
			}
	}
	return *this;
}
dword& dword::operator -= (const dword& rhs) {
	for (int i = 31; i >= 0; --i)
		setbit(i, (rhs.getbit(i) != getbit(i)));
	return *this;
}
dword& dword::operator -= (int rhs) {
	int val = to_int() - rhs;
	int tmp = val;
	for (int i = 0; i < 32; ++i){
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
			for (int i = 31; !getbit(31 - i); --i) {
				flip(32 - i);
			}
	}
	return *this;
}
dword& dword::operator =(int val) {
	reset();
	int tmp = val;
	for (int i = 0; i < 32; ++i)
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
			for (int i = 31; !getbit(31 - i); --i)
			{
				flip(32 - i);
			}
	}
	return *this;
}
dword& dword::operator += (const dword& rhs) {
	for (int i = 31; i >= 0; --i)
		setbit(i, (rhs.getbit(i) != getbit(i)));
	return *this;
}
dword& dword::operator =(const dword& rhs) {
	for (size_t i = 0; i <= 31; ++i)
		setbit(i, rhs.getbit(i));
	return *this;
}
dword::~dword() {

}
void dword::flip(size_t index){
	setbit(index, !getbit(index));
}
bool dword::getbit(int index) const{
	if (index < 8)
		return array_of_bytes[0].return_array() >> index & 1;
	else if (index > 7 && index < 16)
		return array_of_bytes[1].return_array() >> (index - 8) & 1;
	else if (index > 15 && index < 24)
		return array_of_bytes[2].return_array() >> (index - 16) & 1;
	else
		return array_of_bytes[3].return_array() >> (index - 24) & 1;
}
void dword::setbit(int index, bool newval){
	if (newval) {
		if (index < 8)
			array_of_bytes[0].return_array() |= 1 << index;
		else if (index > 7 && index < 16)
			array_of_bytes[1].return_array() |= 1 << (index - 8);
		else if (index > 15 && index < 24)
			array_of_bytes[2].return_array() |= 1 << (index - 16);
		else
			array_of_bytes[3].return_array() |= 1 << (index - 24);
	}
	else {
		if (index < 8)
			array_of_bytes[0].return_array() &= ~(1 << index);
		else if (index > 7 && index < 16)
			array_of_bytes[1].return_array() &= ~(1 << (index - 8));
		else if (index > 15 && index < 24)
			array_of_bytes[2].return_array() &= ~(1 << (index - 16));
		else
			array_of_bytes[3].return_array() &= ~(1 << (index - 24));
	}
}
byte dword::return_byte(size_t number) const{
	return array_of_bytes[number];
}
byte & dword::return_byte(size_t number) {
	return array_of_bytes[number];
}
dword::dword(const byte& first, const byte& second, const byte& third, const byte& fourth) {
	array_of_bytes[0] = first;
	array_of_bytes[1] = second;
	array_of_bytes[2] = third;
	array_of_bytes[3] = fourth;
}
dword& dword::operator^=(const dword& in) {
	for (int i = 31; i >= 0; --i) {
		if (in.getbit(i) == getbit(i)) {
			setbit(i, 0);
		}
		else
			setbit(i, 1);
	}
	return *this;
}
dword& dword::operator&=(const dword& in) {
	for (int i = 31; i >= 0; --i) {
		if (in.getbit(i) == 1 && getbit(i) == 1) {
			setbit(i, 1);
		}
		else
			setbit(i, 0);
	}
	return *this;
}
bool dword::parity() {
	int temp = 0;
	for (int i = 0; i < 32; ++i)
		if (getbit(i)) ++temp;

	if (temp % 2)
		return false;
	else
		return true;
}
std::ostream & operator<<(std::ostream &out, dword &rhs){
	for (int i = 3; i >= 0; --i)
		out << rhs.return_byte(i) << " : ";
	return out;
}