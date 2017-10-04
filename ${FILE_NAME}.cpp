#include<iostream>
#include<string>

template < size_t N >
class sup_byte {
	unsigned char *array_of_bytes;
	int count_of_bit_in_register;
public:
	sup_byte()
	{
		array_of_bytes = new unsigned char[N];
		for (int i = 0; i < N; ++i)
			array_of_bytes[i] = 0;
		count_of_bit_in_register = 8 * N;
	}

	class changereg : public sup_byte
	{
	public:
		int index;
		sup_byte point;

		changereg(int ind, sup_byte&  p)
		{
			index = ind;
			point = p;
		}

		changereg operator=(bool val)
		{
			point.setbit(index, val);
			return *this;
		}

		operator bool()
		{
			return point.getbit(index);
		}

	};

	changereg operator[](int index)
	{
		changereg ret(index, *this);
		return ret;
	}

	changereg change(int index)
	{
		changereg ret(index, *this);
		return ret;
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
			b = current % 2;
			current /= 2;
		}
		return ret;

	}

	bool getbit(int index) const
	{
		int cur = count_of_bit_in_register - 1 - index;
		size_t ret;
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
			array_of_bytes[num] += pow(2, num_in);
		else if (curr_bit == 1 && newval == 0)
			array_of_bytes[num] -= pow(2, num_in);

	}
};

template < size_t N >
class byte
{
private:
	sup_byte<N> sup;
public:

	byte() = default;

	byte(unsigned long val)
	{
		for (int i = 8 * N - 1; i >= 0; --i)
		{
			sup.setbit(i, val % 2);
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
				sup.setbit(j, 0);
			else if (str[i] == '1')
				sup.setbit(j, 1);
			else
			{
				~byte();
				throw std::exception();
			}
			j++;
		}
	}

	~byte() = default;

	byte& set()
	{
		for (size_t i = 0; i < 8 * N; ++i)
			sup.setbit(i, 1);
		return *this;
	};

	byte& set(size_t index, bool value = true)
	{
		if (index >= 8 * N || index < 0)
			throw std::exception();
		sup.setbit(8 * N - index - 1, value);
		return *this;
	}

	byte& reset()
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			sup.setbit(i, 0);
		}
		return *this;
	}

	byte& reset(size_t index)
	{
		sup.setbit(index, 0);
		return *this;
	}

	byte& flip()
	{
		for (size_t i = 0; i < 8 * N; i++)
		{
			sup.setbit(i, sup.getbit(i) ^ 1);
		}
		return *this;
	}

	byte& flip(size_t index)
	{
		if (index >= 8 * N || index < 0)
			throw std::exception();
		sup.setbit(8 * N - index - 1, sup.getbit(8 * N - index - 1) ^ 1);
		return *this;
	}

	typename sup_byte<N>::changereg operator[](size_t index)
	{

		typename sup_byte<N>::changereg tmp = sup.change(index);
		return tmp;
	}

	size_t count() const
	{
		size_t count = 0;
		for (size_t i = 0; i < 8 * N; ++i)
		{
			count += sup.getbit(i);
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
		return sup.getbit(index);
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
			if (sup.getbit(i) == 0)
				return false;
		}
		return true;
	}

	byte& operator&= (const byte& rhs)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (sup.getbit(i) == 0 || rhs.sup.getbit(i) == 0)
			{
				sup.setbit(i, 0);
			}
			else
				sup.setbit(i, 1);
		}
		return *this;
	}

	byte& operator|= (const byte& rhs)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (sup.getbit(i) == 1 || rhs.sup.getbit(i) == 1)
			{
				sup.setbit(i, 1);
			}
			else
				sup.setbit(i, 0);
		}
		return *this;
	}

	byte& operator^= (const byte& rhs)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			sup.setbit(i, !(sup.getbit(i) == rhs.sup.getbit(i)));
		}
		return *this;
	}

	byte& operator<<= (size_t pos)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (i + pos < N)
				sup.setbit(i, sup.getbit(i + pos));
			else
				sup.setbit(i, 0);
		}
		return *this;
	}

	byte& operator>>= (size_t pos)
	{
		for (size_t i = 8 * N - 1; i > 0; --i)
		{
			if (i - pos >= 0)
				sup.setbit(i, sup.getbit(i - pos));
			else
				sup.setbit(i, 0);
		}
		return *this;
	}

	byte operator~()
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (sup.getbit(i) == 0)
				sup.setbit(i, 1);
			else
				sup.setbit(i, 0);
		}
		return *this;
	}

	byte operator<<(size_t pos)
	{
		for (size_t i = 0; i < 8 * N; ++i)
		{
			if (i + pos < N)
				sup.setbit(i, sup.getbit(i + pos));
			else
				sup.setbit(i, 0);
		}
		return *this;
	}

	byte operator >> (size_t pos)
	{
		for (int i = 8 * N - 1; i >= 0; --i)
		{
			if (i - pos >= 0) {
				int a = sup.getbit(i - pos);
				sup.setbit(i, sup.getbit(i - pos));
			}
			else
				sup.setbit(i, 0);
		}
		return *this;
	}

	bool operator== (const byte& rhs)
	{
		if (N != rhs.size())
			return false;
		for (int i = 0; i < 8 * N; ++i)
		{
			if (sup.getbit(i) != rhs.sup.getbit(i))
				return false;
		}
		return true;
	}

	std::string to_string()
	{
		char* str = new char[N + 1];
		for (size_t i = 0; i < 8 * N; ++i)
		{
			str[i] = 48 + sup.getbit(i);
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
			if (tolong + sup.getbit(i) * two > 4294967295)
				throw std::overflow_error("Overflow");
			tolong += sup.getbit(i) * two;
			two *= 2;
		}
		return tolong;
	}
};

template<size_t N>
std::ostream & operator<<(std::ostream &out, byte<N> &rhs)
{
	for (int i = 0; i < 8 * N; ++i)
		out << rhs[i];
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


struct registers {
	byte <1> AX;
	byte <1> BX;
	byte <1> CX;
	byte <1> DX;

	friend std::ostream  & operator<<(std::ostream &out, registers &rhs) {
		out << rhs.AX;
		out << rhs.BX;
		out << rhs.CX;
		out << rhs.DX;
		return out;
	}
};

int main()
{
	registers EAX;

	EAX.CX.set();
	std::cout << EAX << std::endl;

}
