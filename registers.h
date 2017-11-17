#pragma once
#include "header.h"
#include "byte.h"
class registers {
protected:
	byte upper_first;
	byte upper_second;
	byte lower_first;
	byte lower_second;
public:
	byte &return_byte(size_t option);
};

