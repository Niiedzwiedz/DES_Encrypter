#include "DES_encrypter.h"

uint64_t DesEncrypter::Encrypt(uint64_t toEncrypt, uint64_t key) {
	scheduler.SetNewKey(key);
	round = 1;

	//Initial Permutatuion
	uint64_t ip = InitialPermutation(toEncrypt);

	dataBlock.R = ip & 0x00000000FFFFFFFF;
	dataBlock.L = (ip >> 32) & 0x00000000FFFFFFFF;

	//Rounds
	while (round <= 16) {
		uint32_t r = dataBlock.R, l = dataBlock.L;
		dataBlock.R = l ^ Mirror(Feisnel(r), 32);
		dataBlock.L = r;
		round++;
	}

	//Final Permutation
	return Mirror(FinalPermutation(dataBlock.R, dataBlock.L), 64);
}

uint64_t DesEncrypter::InitialPermutation(uint64_t token) {
	std::bitset<64> plainText = { Mirror(token, 64) };
	std::bitset<64> result = { 0x0 };
	//Translation
	for (int i = 0; i < result.size(); i++) {
		result[i] = plainText[TranslationTables::IP[i] - 1];
	}
	return Mirror(result.to_ullong(), 64);
}

uint32_t DesEncrypter::Feisnel(uint32_t r) {
	//Expansion
	uint64_t e = Expansion(r);
	e = Mirror(e, 48);

	//XOR-ing
	e ^= scheduler.GetRoundKey(round);
	
	//S-Boxes
	uint8_t SBoxResults[8];
	for (int i = 7; i >= 0; i--) {
		SBoxResults[i] = (sBoxes[i].Substitute(e & 63UL));
		e >>= 6;
	}

	//Merge output
	uint32_t result = 0x0;
	for (int i = 0; i < 8; i++) {
		result <<= 4;
		result |= SBoxResults[i] & 0b1111;
	}

	//Permutation
	return Permutation(result);
}

uint64_t DesEncrypter::Expansion(uint32_t in) {
	std::bitset<32> target = { Mirror(in, 32) };
	std::bitset<48> result = { 0x0 };
	//Translation
	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::E[i] - 1];
	}
	return result.to_ullong();
}

uint32_t DesEncrypter::Permutation(uint32_t in) {
	std::bitset<32> target = { Mirror(in, 32) };
	std::bitset<32> result = { 0x0 };
	//Translation
	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::P[i] - 1];
	}
	return result.to_ulong();
}

uint64_t DesEncrypter::FinalPermutation(uint32_t l, uint32_t r) {
	uint64_t input = (((uint64_t)l << 32) | r);
	std::bitset<64> target = { Mirror(input, 64) };
	std::bitset<64> result = { 0x0 };
	//Translation
	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::FP[i] - 1];
	}
	return result.to_ullong();
}


uint64_t DesEncrypter::Decrypt(uint64_t toEncrypt, uint64_t key) {
	scheduler.SetNewKey(key);
	round = 16;

	//Initial Permutatuion
	uint64_t ip = InitialPermutation(toEncrypt);

	dataBlock.R = ip & 0x00000000FFFFFFFF;
	dataBlock.L = (ip >> 32) & 0x00000000FFFFFFFF;

	//Rounds
	while (round >= 1) {
		uint32_t r = dataBlock.R, l = dataBlock.L;
		dataBlock.R = l ^ Mirror(Feisnel(r), 32);
		dataBlock.L = r;
		round--;
	}

	//Final Permutation
	return Mirror(FinalPermutation(dataBlock.R, dataBlock.L), 64);
}