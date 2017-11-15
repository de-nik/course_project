#include <iostream>
#include <string>

template < size_t N >
class byte
{
private:
	unsigned char *array_of_bytes;
public:
	byte()
	{
		array_of_bytes = new unsigned char[N];
		for (int i = 0; i < 8 * N; ++i)
			array_of_bytes[i] = 0;
	}

	int to_int() const {
		int res = 0;

		if (getbit(0)) {
				++res;
			for (int i = 0; i < 8 * N; ++i) {
				if (!getbit(i))
					res += (int)pow(2, 8 * N - 1 - i);
			}
			return -res;
		}

		else {
			for (int i = 8 * N - 1; i > 0; --i) {
				if (getbit(i))
					res += (int)pow(2, 8 * N - 1 - i);
			}
		}
		return res;

	}

	bool getbit(int index) const
	{
		int cur = 8 * N - 1 - index;
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
		int cur = 8 * N - 1 - index;
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

	byte(int val)
	{
		int tmp = val;
		array_of_bytes = new unsigned char[N];
		for (int i = 8 * N - 1; i >= 0; --i)
			array_of_bytes[i] = 0;

		for (int i = 8 * N - 1; i >= 0; --i) {
			setbit(i, abs((val % 2)));
			val = val / 2;
		}
		if (tmp < 0) {
			flip();
			flip(8 * N - 1);
			for (int i = 2; !getbit(8 * N - i + 1); ++i) {
				flip(8 * N - i);
			}
		}
	}

	byte& set()
	{
		for (size_t i = 0; i < 8 * N; ++i)
			setbit(i, 1);
		return *this;
	};

	byte& reset()
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			setbit(i, 0);
		}
		return *this;
	}

	byte& flip()
	{
		for (size_t i = 0; i < 8 * N; i++)
		{
			setbit(i, !getbit(i));
		}
		return *this;
	}

	byte& flip(size_t index)
	{
		setbit(index, !getbit(index));
		return *this;
	}

	bool operator== (const byte& rhs) const
	{
		for (int i = 0; i < 8 * N; ++i)
		{
			if (getbit(i) != rhs.getbit(i))
				return false;
		}
		return true;
	}

	bool operator!= (const byte& rhs) const
	{
		for (int i = 0; i < 8 * N; ++i)
		{
			if (getbit(i) != rhs.getbit(i))
				return true;
		}
		return false;
	}

	byte &operator += (const byte& rhs) {
		for (int i = 8 * N - 1; i >= 0; --i)
			setbit(i, (rhs.getbit(i) != getbit(i)));
		return *this;
	}

	byte &operator += (int rhs) {
		int val = to_int() + rhs;
		int tmp = val;
		for (int i = 8 * N - 1; i >= 0; --i) {
			setbit(i, abs((val % 2)));

			val = val / 2;
		}
		if (tmp < 0) {
			flip();
			flip(8 * N - 1);
			for (int i = 2; !getbit(8 * N - i + 1); ++i) {
				flip(8 * N - i);
			}
		}
		return *this;
	}

	byte &operator -= (const byte& rhs) {
		for (int i = 8 * N - 1; i >= 0; --i)
			setbit(i, (rhs.getbit(i) != getbit(i)));
		return *this;
	}

	byte &operator -= (int rhs) {
		int val = to_int() - rhs;
		int tmp = val;
		for (int i = 8 * N - 1; i >= 0; --i) {
			setbit(i, abs((val % 2)));

			val = val / 2;
		}
		if (tmp < 0) {
			flip();
			flip(8 * N - 1);
			for (int i = 2; !getbit(8 * N - i + 1); ++i) {
				flip(8 * N - i);
			}
		}
		return *this;
	}

	byte &operator =(const byte& rhs) {
		for (size_t i = 0; i <= 8 * N - 1; ++i)
			setbit(i, rhs.getbit(i));
		return *this;
	}

	byte &operator =(int val) {
		reset();
		int tmp = val;
		for (int i = 8 * N - 1; i >= 0; --i) {
			setbit(i, abs((val % 2)));

			val = val / 2;
		}
		if (tmp < 0) {
			flip();
			flip(8 * N - 1);
			for (int i = 2; !getbit(8 * N - i + 1); ++i) {
				flip(8 * N - i);
			}
		}
		return *this;
	}

	byte<1> conc(size_t k) {
		byte<1> tmp;
		for (int i = 8*(N - k) - 1, k = 7; i >= 8*(N - k + 1); --i, --k) {
			tmp.setbit(k, getbit(i));
			std::cout << " get: " << getbit(i) << std::endl;
		}
		return tmp;
	}

	~byte() {
		for (int i = 8 * N - 1; i >= 0; --i)
			array_of_bytes[i] = 0;
		delete [] array_of_bytes;
	}
	/*std::string to_string()
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
	}*/

};

template<size_t N>
std::ostream & operator<<(std::ostream &out, byte<N> &rhs)
{
	for (int i = 0; i < 8 * N; ++i)
		out << rhs.getbit(i);
	return out;
}

//template<size_t N>
//byte<N> operator+(const byte<N>& lhs, const byte<N> &rhs)
//{
//	byte<N> tmp = lhs;
//	tmp += rhs;
//	return tmp;
//}
//
//template<size_t N>
//byte<N> operator+(const byte<N>& lhs, const int& rhs)
//{
//	byte<N> tmp = lhs;
//	tmp += rhs;
//	return tmp;
//}

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

	/*registers mov_reg(const std::string &in, int out) {
		if (out >= -128 && out <= 127) {
			return_reg_by_string(in).return_byte(3) = out;
		}
		else if (out >= -32768 && out <= 32767) {
			byte<2> tmp = out;
			return_reg_by_string(in).return_byte(3) = 256;
			return_reg_by_string(in).return_byte(2) = out - 256;
		}
		else if (out >= -8388608 && out <= 8388607) {

		}
		else if (out >= -214748368 && out <= 2147483647) {
			
		}
		return return_reg_by_string(in);
	}*/

	byte<1> mov(const std::string &in, const std::string &out) {
		return_by_string(in) = return_by_string(out);
		return return_by_string(in);
	}

	byte<1> mov(const std::string &in, int out) {
		return_by_string(in) = out;
		return return_by_string(in);
	}

	byte<1> add(const std::string &in, const std::string &out) {
		return_by_string(in) += return_by_string(out);
		return return_by_string(in);
	}

	byte<1> add(const std::string &in, int out) {
		return_by_string(in) += out;
		return return_by_string(in);
	}

	byte<1> sub(const std::string &in, const std::string &out) {
		return_by_string(in) -= return_by_string(out);
		return return_by_string(in);
	}

	byte<1> sub(const std::string &in, int out) {
		return_by_string(in) -= out;
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
			if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
				mov(in, out);
			else if (out == "EAX" || out == "EBX")
				mov_reg(in, out);
			else {
				int i = std::atoi(out.c_str());
				if (in == "EAX" || in == "EBX")
					mov_reg(in, i);
				if (in == "AH" || in == "BH" || in == "AL" || in == "BL")
					mov(in, i);
			}

			return true;
		}
		if (input == "add") {
			std::string in, out;
			std::cin >> in >> out;
			if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
				add(in, out);
			else {
				int i = std::atoi(out.c_str());
				add(in, i);
			}
			return true;
		}
		if (input == "sub") {
			std::string in, out;
			std::cin >> in >> out;
			if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
				sub(in, out);
			else {
				int i = std::atoi(out.c_str());
				sub(in, i);
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
	/*saver_registers one;
	std::string input;
	while (input != "exit") {
		system("cls");
		std::cin >> input;
		one.parser(input);
		system("pause");
	}*/
	
	/*	byte<2> a(-15000);
		std::cout << a.conc(0) << " | "<< a << std::endl;*/

}
