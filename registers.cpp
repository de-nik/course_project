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

