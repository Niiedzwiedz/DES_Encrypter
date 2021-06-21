#pragma once
#include "common.h"

struct Key {
	uint32_t C : 28;
	uint32_t D : 28;
};

class KeyScheduler {
private:
	Key		 key			= { 0x0, 0x0 };
	uint64_t roundKeys[16]	= { 0x0 };
protected:
public:
	KeyScheduler() { }

	void	 SetNewKey(uint64_t);
	void	 Rotate(int);
	uint64_t PC1(uint64_t);
	uint64_t PC2();
	uint64_t GetRoundKey(int i) { return roundKeys[i - 1]; }
};