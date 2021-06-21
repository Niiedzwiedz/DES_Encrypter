#include "Key_scheduler.h"

void KeyScheduler::SetNewKey(uint64_t newKey) {
	uint64_t pc1 = PC1(newKey);

	//Save pc1 result
	uint32_t d = pc1 & 0x000000000FFFFFFF;
	pc1 >>= 28;
	uint32_t c = pc1 & 0x000000000FFFFFFF;
	key = { c, d };

	//Generate round keys
	for (int i = 1; i <= 16; i++) {
		Rotate(i);
		roundKeys[i - 1] = PC2();
	}
}

uint64_t KeyScheduler::PC1(uint64_t newKey) {
	std::bitset<64> key = { Mirror(newKey, 64) };
	std::bitset<56> result = { 0x0 };
	//Translation
	for (int i = 0; i < result.size(); i++) {
		result[i] = key[TranslationTables::PC1[i] - 1];
	}
	return Mirror(result.to_ullong(), 56);
}

void KeyScheduler::Rotate(int round) {
	int shift = 2;
	if (round == 1 || round == 2 || round == 9 || round == 16) shift = 1;
	key.C = rotateLeft(key.C, shift);
	key.D = rotateLeft(key.D, shift);
}

uint64_t KeyScheduler::PC2() {
	uint64_t toPC2 = ((uint64_t)key.C << 28) | key.D;
	std::bitset<56> key = { Mirror(toPC2, 56) };
	std::bitset<48> result{ 0x0 };
	//Translation
	for (int i = 0; i < result.size(); i++) {
		result[i] = key[TranslationTables::PC2[47 - i] - 1];
	}
	return result.to_ullong();
}