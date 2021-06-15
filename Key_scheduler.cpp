#include "Key_scheduler.h"

void KeyScheduler::SetNewKey(uint64_t newKey) {
	uint64_t pc1 = PC1(newKey);

	//SAVE PC1 RESULT
	uint32_t d = pc1 & 0x000000000FFFFFFF;
	pc1 >>= 28;
	uint32_t c = pc1 & 0x000000000FFFFFFF;

	//std::cout << "C:\t" << std::bitset<28>{c} << std::endl;
	//std::cout << "D:\t" << std::bitset<28>{d} << std::endl;
	
	key = { c, d };

	//std::cout << "R " << 0 << "\t";
	//std::cout << "C: " << std::hex << key.C << "   ";
	//std::cout << "D: " << std::hex << key.D << std::endl;

	//=====================================
	for (int i = 1; i <= 16; i++) {
		Rotate(i);
		//std::cout << "R " << i << "\t";
		//std::cout << "C: " << std::hex << key.C << "   ";
		//std::cout << "D: " << std::hex << key.D << std::endl;
		//std::cout << "C: " << std::bitset<28>{key.C} << "   ";
		//std::cout << "D: " << std::bitset<28>{key.D} << std::endl;

		roundKeys[i - 1] = PC2();
	}

	/*
	for (int i = 1; i <= 16; i++) {
		std::cout << i << "\t" << std::hex << roundKeys[i - 1] << std::endl;
	}//*/
	//=====================================
}

uint64_t KeyScheduler::PC1(uint64_t newKey) {

	//std::cout << "64b Key:\t" << std::bitset<64>{newKey} << std::endl;

	std::bitset<64> packedKey = { Mirror(newKey, 64) };
	std::bitset<56> result = { 0x0 };

	for (int i = 0; i < result.size(); i++) {
		result[i] = packedKey[TranslationTables::PC1[i] - 1];
	}

	uint64_t pc1 = Mirror(result.to_ullong(), 56);
	//std::cout << "56b Key:\t" << std::bitset<56>{result} << std::endl;
	//std::cout << "56b Key:\t" << std::hex << pc1 << std::endl;

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

	std::bitset<56> preKey = { Mirror(toPC2, 56) };
	std::bitset<48> result{ 0x0 };

	for (int i = 0; i < result.size(); i++) {
		result[i] = preKey[TranslationTables::PC2[47 - i] - 1];
	}

	//std::cout << "PC2:\t" << std::bitset<48>{result} << std::endl;

	return result.to_ullong();
}