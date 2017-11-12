#include <iostream>
#include <string>
#include <vector>

template < size_t N >
class byte
{
private:
	unsigned char *array_of_bytes;
	size_t count_of_bit_in_register;

public:
	byte()
	{
		array_of_bytes = new unsigned char[N];
		for (int i = 0; i < 8 * N; ++i)
			array_of_bytes[i] = 0;
		count_of_bit_in_register = 8 * N;
	}

	int to_int() const {
		int res = 0;
		for (size_t i = 0; i < 8 * N - 1; ++i) {
			if (getbit(i))
				res += (int)pow(2, i);
		}
		return res;
	}

	const bool operator[](int index) const
	{
		int cur = count_of_bit_in_register - 1 - index;
		bool ret;
		int num = (cur / 8);
		int num_in = cur % 8;
		unsigned char current = array_of_bytes[num];
		for (int i = 0; i <= num_in; ++i)
		{
			ret = current % 2;
			current /= 2;
		}
		return ret;

	}

	bool getbit(int index) const
	{
		int cur = count_of_bit_in_register - 1 - index;
		bool ret;
		int num = (cur / 8);
		int num_in = cur % 8;
		unsigned char current = array_of_bytes[num];
		for (int i = 0; i <= num_in; ++i)
		{
			ret = current % 2;
			current /= 2;
		}
		return ret;
	}

	void setbit(int index, size_t newval)
	{
		int cur = count_of_bit_in_register - 1 - index;
		int num = (cur / 8);
		int num_in = cur % 8;
		size_t curr_bit;
		unsigned char current = array_of_bytes[num];
		for (int i = 0; i <= num_in; ++i)
		{
			curr_bit = current % 2;
			current /= 2;
		}
		if (curr_bit == 0 && newval == 1)
			array_of_bytes[num] += (unsigned char)pow(2, num_in);
		else if (curr_bit == 1 && newval == 0)
			array_of_bytes[num] -= (unsigned char)pow(2, num_in);

	}

	byte(unsigned long val)
	{
		array_of_bytes = new unsigned char[N];
		for (int i = 0; i < 8 * N; ++i)
			array_of_bytes[i] = 0;
		count_of_bit_in_register = 8 * N;
		for (int i = 0; i < 8 * N; ++i)
		{
			setbit(i, val % 2);
			val = val / 2;
		}
	}

	byte(const std::string& str, size_t pos, size_t n)
	{
		size_t j = 0;
		if (pos >= str.size())
			throw std::out_of_range("Error!");
		for (size_t i = pos; i < n; ++i)
		{
			if (j >= N)
				return;
			if (str[i] == '0')
				setbit(j, 0);
			else if (str[i] == '1')
				setbit(j, 1);
			else
			{
				~byte();
				throw std::exception();
			}
			j++;
		}
	}

	byte& set()
	{
		for (size_t i = 0; i < 8 * N; ++i)
			setbit(i, 1);
		return *this;
	};

	byte& set(size_t index, bool value = true)
	{
		if (index >= 8 * N || index < 0)
			throw std::exception();
		setbit(index, value);
		return *this;
	}

	byte& reset()
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			setbit(i, 0);
		}
		return *this;
	}

	byte& reset(size_t index)
	{
		setbit(index, 0);
		return *this;
	}

	byte& flip()
	{
		for (size_t i = 0; i < 8 * N; i++)
		{
			setbit(i, getbit(i) ^ 1);
		}
		return *this;
	}

	byte& flip(size_t index)
	{
		if (index >= 8 * N || index < 0)
			throw std::exception();
		setbit(index, getbit(index) ^ 1);
		return *this;
	}

	size_t count() const
	{
		size_t count = 0;
		for (size_t i = 0; i < 8 * N; ++i)
		{
			count += getbit(i);
		}
		return count;
	}

	size_t size() const
	{
		return N;
	}

	bool test(size_t index) const
	{
		if (index >= N || index < 0)
			throw std::out_of_range("Error");
		return getbit(index);
	}

	bool any()
	{
		for (size_t i = 0; i < N; ++i)
		{
			if ((*this).operator[](i) == 1)
				return true;
		}
		return false;
	}

	bool none()
	{
		return !(any());
	}

	bool all() const
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (getbit(i) == 0)
				return false;
		}
		return true;
	}

	byte& operator&= (const byte& rhs)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (getbit(i) == 0 || rhs.getbit(i) == 0)
			{
				setbit(i, 0);
			}
			else
				setbit(i, 1);
		}
		return *this;
	}

	byte& operator|= (const byte& rhs)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (getbit(i) == 1 || rhs.getbit(i) == 1)
			{
				setbit(i, 1);
			}
			else
				setbit(i, 0);
		}
		return *this;
	}

	byte& operator^= (const byte& rhs)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			setbit(i, !(getbit(i) == rhs.getbit(i)));
		}
		return *this;
	}

	byte& operator<<= (size_t pos)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (i + pos < N)
				setbit(i, getbit(i + pos));
			else
				setbit(i, 0);
		}
		return *this;
	}

	byte& operator>>= (size_t pos)
	{
		for (size_t i = 8 * N - 1; i > 0; --i)
		{
			if (i - pos >= 0)
				setbit(i, getbit(i - pos));
			else
				setbit(i, 0);
		}
		return *this;
	}

	byte operator~()
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (getbit(i) == 0)
				setbit(i, 1);
			else
				setbit(i, 0);
		}
		return *this;
	}

	byte operator<<(size_t pos)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (i + pos < N)
				setbit(i, getbit(i + pos));
			else
				setbit(i, 0);
		}
		return *this;
	}

	byte operator >> (size_t pos)
	{
		for (int i = 8 * N - 1; i >= 0; --i)
		{
			if (i - pos >= 0) {
				int a = getbit(i - pos);
				setbit(i, getbit(i - pos));
			}
			else
				setbit(i, 0);
		}
		return *this;
	}

	bool operator== (const byte& rhs) const
	{
		if (N != rhs.size())
			return false;
		for (int i = 0; i < 8 * N; ++i)
		{
			if (getbit(i) != rhs.getbit(i))
				return false;
		}
		return true;
	}

	bool operator!= (const byte& rhs) const
	{
		if (N != rhs.size())
			return false;
		for (int i = 0; i < 8 * N; ++i)
		{
			if (getbit(i) != rhs.getbit(i))
				return true;
		}
		return false;
	}

	byte operator += (const byte& rhs) {
		if (N != rhs.size())
			return false;
		for (int i = 8 * N - 1; i >= 0; --i)
			//setbit(i, (rhs.getbit(i) != getbit(i)));
			return *this;
	}

	byte operator += (const int& rhs) {
		int temp_bit = to_int() + rhs;
		for (size_t i = 0; i <= 8 * N - 1; ++i) {
			setbit(i, temp_bit % 2);
			temp_bit /= 2;
		}
		return *this;
	}

	byte operator= (const byte& rhs) {
		for (size_t i = 0; i <= 8 * N - 1; ++i)
			setbit(i, rhs.getbit(i));
		return *this;
	}

	byte operator =(int val) {
		reset();
		for (int i = 0; i < 8 * N; ++i)
		{
			setbit(i, val % 2);
			val = val / 2;
		}
		return *this;
	}

	std::string to_string()
	{
		char* str = new char[N + 1];
		for (size_t i = 0; i < 8 * N; ++i)
		{
			str[i] = 48 + getbit(i);
		}
		str[N] = '\0';
		std::string stri;
		stri.reserve(N);
		stri = str;
		delete[] str;
		return stri;
	}

	unsigned long to_ulong()
	{
		double tolong = 0;
		int two = 1;
		for (int i = 8 * N - 1; i >= 0; --i)
		{
			if (tolong + getbit(i) * two > 4294967295)
				throw std::overflow_error("Overflow");
			tolong += getbit(i) * two;
			two *= 2;
		}
		return tolong;
	}

};

template<size_t N>
std::ostream & operator<<(std::ostream &out, byte<N> &rhs)
{
	for (int i = 8 * N - 1; i >= 0; --i)
		out << rhs.getbit(i);
	return out;
}

template<size_t N>
byte<N> operator& (const byte<N>& lhs, const byte<N>& rhs)
{
	byte<N> tmp = lhs;
	tmp &= rhs;
	return tmp;
}

template<size_t N>
byte<N> operator| (const byte<N>& lhs, const byte<N>& rhs)
{

	byte<N> tmp = lhs;
	tmp |= rhs;
	return tmp;
}

template<size_t N>
byte<N> operator^ (const byte<N>& lhs, const byte<N>& rhs)
{
	byte<N> tmp = lhs;
	tmp ^= rhs;
	return tmp;
}

template<size_t N>
byte<N> operator+(const byte<N>& lhs, const byte<N> &rhs)
{
	byte<N> tmp = lhs;
	tmp += rhs;
	return tmp;
}

template<size_t N>
byte<N> operator+(const byte<N>& lhs, const int& rhs)
{
	byte<N> tmp = lhs;
	tmp += rhs;
	return tmp;
}

class registers {
protected:
	byte<1> upper_first;
	byte<1> upper_second;
	byte<1> lower_first;
	byte<1> lower_second;
public:
	byte<1> &return_byte(size_t option) {
		switch (option) {
		case 0:
			return upper_first;
		case 1:
			return upper_second;
		case 2:
			return lower_first;
		case 3:
			return lower_second;
		default:
			break;
		}
	}
};

std::ostream & operator<<(std::ostream &out, registers &rhs)
{
	for (size_t i = 0; i < 4; ++i) {
		out << rhs.return_byte(i) << " : ";
	}
	return out;
}

class saver_registers
{
	registers EAX;
	registers EBX;
public:
	byte<1> &return_by_string(const std::string &title) {
		if (title == "AH") return EAX.return_byte(3);
		else if (title == "AL") return EAX.return_byte(2);
		else if (title == "BH") return EBX.return_byte(3);
		else if (title == "BL") return EBX.return_byte(2);
	}

	registers &return_reg_by_string(const std::string &title) {
		if (title == "EAX") return EAX;
		else if (title == "EBX") return EBX;
	}

	registers mov_reg(const std::string &in, const std::string &out) {
		return_reg_by_string(in) = return_reg_by_string(out);
		return return_reg_by_string(in);
	}

	registers mov_reg(const std::string &in, const unsigned long &out) {
		if (out <= 255)
			return_reg_by_string(in).return_byte(3) = out;
		else if (out <= 65535) {
			return_reg_by_string(in).return_byte(3) = 255;
			return_reg_by_string(in).return_byte(2) = out - 256;
		}
		else if (out <= 16777215) {
			return_reg_by_string(in).return_byte(3) = 255;
			return_reg_by_string(in).return_byte(2) = 65535;
			return_reg_by_string(in).return_byte(1) = out - 65536;
		}
		else if (out <= 4294967295) {
			return_reg_by_string(in).return_byte(3) = 255;
			return_reg_by_string(in).return_byte(2) = 65535;
			return_reg_by_string(in).return_byte(1) = 16777215;
			return_reg_by_string(in).return_byte(1) = out - 4294967296;
		}
		return return_reg_by_string(in);
	}

	byte<1> mov(const std::string &in, const std::string &out) {
		return_by_string(in) = return_by_string(out);
		return return_by_string(in);
	}

	byte<1> mov(const std::string &in, const unsigned long& out) {
		return_by_string(in) = out;
		return return_by_string(in);
	}

	byte<1> add(const std::string &in, const std::string &out) {
		return_by_string(in) += return_by_string(out);
		return return_by_string(in);
	}

	byte<1> add(const std::string &in, const unsigned long& out) {
		return_by_string(in) += out;
		return return_by_string(in);
	}

	bool cmp(const std::string &in, const std::string &out) {
		if (return_by_string(in) == return_by_string(out)) {
			std::cout << "eq" << std::endl;
			return true;
		}
		if (return_by_string(in) != return_by_string(out)) {
			std::cout << "not eq" << std::endl;
			return false;
		}
	}

	bool parser(const std::string &input) {
		if (input == "mov") {
			std::string in, out;
			std::cin >> in >> out;
			if (out == "AH" || out == "BH" || out == "CH" || out == "DH")
				mov(in, out);
			else if (out == "EAX" || out == "EBX")
				mov_reg(in, out);
			else {
				unsigned long i = std::atoi(out.c_str());
				if (in == "EAX" || in == "EBX")
					mov_reg(in, i);
				if (in == "AH" || in == "BH" || in == "CH" || in == "DH")
					mov(in, i);
			}

			return true;
		}
		if (input == "add") {
			std::string in, out;
			std::cin >> in >> out;
			if (out == "AH" || out == "BH" || out == "CH" || out == "DH")
				add(in, out);
			else {
				unsigned long i = std::atoi(out.c_str());
				add(in, i);
			}
			return true;
		}
		if (input == "set") {
			std::string in;
			std::cin >> in;
			return_by_string(in).set();
			return true;
		}
		if (input == "cmp") {
			std::string in, out;
			std::cin >> in >> out;
			cmp(in, out);
			return true;
		}
		if (input == "out") {
			std::cout <<
				"EAX: " << EAX << std::endl <<
				"EBX: " << EBX << std::endl << std::endl;
			return true;
		}
		else if (input == "exit") throw false;
		else {
			std::cout << "unavailable command" << std::endl;
			return true;
		}
	}
};

int main()
{
	saver_registers one;
	try {
		std::string input;
		while (input != "exit") {
			system("cls");
			std::cin >> input;
			one.parser(input);
			system("pause");
		}
	}
	catch (size_t number) {
		std::cout << number << std::endl;
	}
	/*byte<1> a(5);
	byte<1> b(7);
	byte<1> r;
	r = (a + b);
	std::cout  << a;*/
}
