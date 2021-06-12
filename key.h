#pragma once
#include "common.h"

struct Key {
	uint32_t C : 28;
	uint32_t D : 28;
};

/*
class DES_Key_Scheduler {
private:
	Key key;
	int round;

	const unsigned int arrayPC1[56] = {
		57, 49, 41, 33, 25, 17,  9,  1,
		58, 50, 42, 34, 26, 18, 10,  2,
		59, 51, 43, 35, 27, 19, 11,  3,
		60, 52, 44, 36, 63, 55, 47, 39,
		31, 23, 15,  7, 62, 54, 46, 38,
		30, 22, 14,  6, 61, 53, 45, 37,
		29, 21, 13,  5, 28, 20, 12,  4
	};

	const unsigned int arrayPC2[48] = {
		14, 17, 11, 24,  1,  5,  3, 28,
		15,  6, 21, 10, 23, 19, 12,  4,
		26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32
	};
protected:

public:
	DES_Key_Scheduler() { DES_Key_Scheduler(0x0); }
	DES_Key_Scheduler(uint64_t newKey) {
		uint64_t shortedKey = PC1(newKey);
		uint64_t mask = 0x000000000FFFFFFF;
		uint32_t d = (shortedKey & mask);
		shortedKey >>= 28;
		uint32_t c = (shortedKey & mask);
		key = { c, d };
	}

	~DES_Key_Scheduler() { }

	uint64_t PC1(uint64_t key) {
		std::bitset<64> input{ key };
		std::bitset<56> result{ 0x0 };
		for (int i = 0; i < result.size(); i++) {
			result[i] = input[arrayPC1[i]];
		}
		return result.to_ullong();
	}

	uint64_t PC2() {
		uint64_t temp = getKey();
		std::bitset<64> input{ temp };
		std::bitset<48> result{ 0x000000000000 };
		for (int i = 0; i < result.size(); i++) {
			std::cout << i << std::endl;
			result[i] = input[arrayPC2[i]];
		}
		return (uint64_t)result.to_ullong();
	}

	void Transform(int round) {
		int shift = 2;
		if (round == 1 || round == 2 || round == 9 || round == 16) shift = 1;

		key.C = std::rotl(key.C, shift);
		key.D = std::rotl(key.D, shift);
	}

	uint64_t GetKey(int round) {
		Transform(round);
		return PC2();
	}

	void Reset() {
		round = 0;
		key = { 0x0, 0x0 };
	}

	void Set(uint64_t newKey) {
		Reset();
		uint64_t shortedKey = PC1(newKey);
		uint64_t mask = 0x000000000FFFFFFF;
		uint32_t d = (shortedKey & mask);
		shortedKey >>= 28;
		uint32_t c = (shortedKey & mask);
		key = { c, d };
	}

	uint64_t getKey(){
		uint64_t temp = key.C;
		temp <<= 28;
		temp |= key.D;
		return temp;
	}

};
*/