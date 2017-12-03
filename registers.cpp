#include "registers.h"
byte& registers::return_byte(size_t option) {
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

std::ostream & operator<<(std::ostream &out, registers &rhs)
{
	for (size_t i = 0; i < 4; ++i) {
		out << rhs.return_byte(i) << " : ";
	}
	return out;
}