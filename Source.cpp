#include <iostream>
#include <string>
#include <vector>
#include <map>



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
		for (int i = 0; i < N; ++i)
			array_of_bytes[i] = 0;
		count_of_bit_in_register = 8 * N;
	}

	class changereg : public byte
	{
	public:
		int index;
		byte point;

		changereg(int ind, byte&  p)
		{
			index = ind;
			point = p;
		}

		changereg operator=(changereg &rhs)
		{
			point.setbit(index, rhs.return_point().getbit(index));
			return *this;
		}

		byte& return_point() {
			return point;
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

	byte(unsigned long val)
	{
		for (int i = 8 * N - 1; i >= 0; --i)
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

	typename changereg operator[](size_t index)
	{

		typename changereg tmp = change(index);
		return tmp;
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

	bool operator== (const byte& rhs)
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
	for (int i = 7; i >= 0 ; --i)
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

class registers {
	std::map<const std::string, byte<1>> cont;
public:
	registers(const std::string &title_upper_first, const std::string &title_upper_second, 
		      const std::string &title_lower_first, const std::string &title_lower_second)
	{

		byte<1> upper_first;
		byte<1> upper_second;
		byte<1> lower_first;;
		byte<1> lower_second;

		cont.emplace(title_upper_first, upper_first);
		cont.emplace(title_upper_second, upper_second);
		cont.emplace(title_lower_first, lower_first);
		cont.emplace(title_lower_second, lower_second);

	}
	
	std::map<const std::string, byte<1>>& out() {
		return cont;
	}
};

std::ostream & operator<<(std::ostream &out, registers &rhs)
{

	for (auto it = rhs.out().begin(); it != rhs.out().end(); ++it)
	{
		out /*<< (*it).first << " : "*/ << (*it).second/* << std::endl*/;
	}

	return out;
}

int main()
{
	byte<1> r;
	registers EAX("UF", "US", "AH", "AL");
	EAX.out()["AL"].set(1);
	std::cout << EAX << std::endl;
	
	std::pair <const std::string, byte<1>> a = { "as", r };
}