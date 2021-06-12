#pragma once
#include "common.h"

struct Key {
	uint32_t C : 28;
	uint32_t D : 28;
};

class KeyScheduler {
private:
	Key key = {0x0, 0x0};
	uint64_t roundKeys[16] = {0x0};
protected:
public:
	KeyScheduler() { }

	void SetNewKey(uint64_t);
	uint64_t getSheduledKey(int);
	uint64_t Transform(int);
	uint64_t PrepareKey();
	void Rotate(int round);
};