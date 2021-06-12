#include "Key_scheduler.h"

void KeyScheduler::SetNewKey(uint64_t newKey) {	//PC - 1
	std::bitset<64> packedKey = { newKey };
	std::bitset<56> result = { 0x0 };
	for (int i = 0; i < result.size(); i++) {
		result[i] = packedKey[TranslationTables::PC1[i] - 1];
	}
	uint64_t pc1 = result.to_ullong();
	uint32_t c = pc1 & 0x000000000FFFFFFF;
	pc1 >>= 28;
	uint32_t d = pc1 & 0x000000000FFFFFFF;
	key = { c, d };
	//std::cout << std::bitset<28>{ key.C } << " " << std::bitset<28>{key.D} << std::endl;
}

uint32_t rotateLeft(uint32_t data, int shift) {
	return ((data << shift) | ((data >> 28 - shift)) & 0xfffffff);
}

uint64_t KeyScheduler::getSheduledKey(int round) {
	return Transform(round);
}


uint64_t KeyScheduler::Transform(int round) {
	Rotate(round);
	return PrepareKey();
}

uint64_t KeyScheduler::PrepareKey() {
	uint64_t toPC2 = key.C;
	toPC2 <<= 28;
	toPC2 |= key.D;
	std::bitset<56> preKey{ toPC2 };
	std::bitset<48> resultKey{ 0x0 };
	for (int i = 0; i < resultKey.size(); i++) {
		resultKey[i] = preKey[TranslationTables::PC2[i] - 1];
	}
	return resultKey.to_ullong();
}

void KeyScheduler::Rotate(int round) {
	int shift = 2;
	if (round == 1 || round == 2 || round == 9 || round == 16) shift = 1;
	key.C = rotateLeft(key.C, shift);
	key.D = rotateLeft(key.D, shift);
	//std::cout << std::bitset<28>{ key.C } << " " << std::bitset<28>{key.D} << std::endl;
}