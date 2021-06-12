#pragma once
#include "common.h"

class SBox
{
private:
	uint8_t subTable[4][16];
protected:

public:
	SBox(uint8_t newTable[4][16]) {
		for (int i = 0; i < 16 * 4; i++) subTable[i / 16][i % 16] = newTable[i / 16][i % 16];
	}

	uint8_t Substitute(uint8_t code) {
		unsigned int row = ((code & 0b00100000) >> 4 ) | (code & 0b00000001);
		unsigned int column = (code & 0b00011110) >> 1;
		return subTable[row][column];
	}
};

