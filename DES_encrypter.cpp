#include "DES_encrypter.h"

uint64_t DesEncrypter::Encrypt(uint64_t toEncrypt, uint64_t key) {
	scheduler.SetNewKey(key);
	round = 1;

	std::cout << "To Encrypt:\t" << std::hex << toEncrypt << std::endl;

	//Initial Permutatuion
	uint64_t ip = InitialPermutation(toEncrypt);

	dataBlock.R = ip & 0x00000000FFFFFFFF;
	dataBlock.L = (ip >> 32) & 0x00000000FFFFFFFF;

	//std::cout << "L:\t" << std::bitset<32>{dataBlock.L} << std::endl;
	//std::cout << "R:\t" << std::bitset<32>{dataBlock.R} << std::endl;


	while (round <= 16) {
		uint32_t r = dataBlock.R, l = dataBlock.L;
		dataBlock.R = l ^ Mirror(Feisnel(r), 32);
		dataBlock.L = r;
		round++;

		//std::cout << "L" << round - 1 << ":\t" << std::bitset<32>{dataBlock.L} << std::endl;
		//std::cout << "R" << round - 1 << ":\t" << std::bitset<32>{dataBlock.R} << std::endl;
	}


	std::cout << "Encrypted:\t" << std::hex << Mirror(FinalPermutation(dataBlock.R, dataBlock.L), 64) << std::endl;
	return Mirror(FinalPermutation(dataBlock.R, dataBlock.L), 64);
}

uint64_t DesEncrypter::InitialPermutation(uint64_t token) {

	//std::cout << "M:\t" << std::bitset<64>{token} << std::endl;

	std::bitset<64> plainText = { Mirror(token, 64) };
	std::bitset<64> result = { 0x0 };

	for (int i = 0; i < result.size(); i++) {
		result[i] = plainText[TranslationTables::IP[i] - 1];
	}

	//std::cout << "IP:\t" << std::bitset<64>{Mirror(result.to_ullong(), 64)} << std::endl;

	return Mirror(result.to_ullong(), 64);
}

uint32_t DesEncrypter::Feisnel(uint32_t r) {
	uint64_t e = Expansion(r);
	e = Mirror(e, 48);

	//std::cout << "K: \t" << std::bitset<48>{scheduler.GetRoundKey(round)} << std::endl;
	//std::cout << "E(R):\t" << std::bitset<48>{e} << std::endl;

	e ^= scheduler.GetRoundKey(round);

	//std::cout << "K+E: \t" << std::bitset<48>{e} << std::endl;

	uint8_t SBoxResults[8];
	for (int i = 7; i >= 0; i--) {
		//std::cout << "SBOX " << i << ":\t" << std::bitset<4>{sBoxes[i].Substitute(e & 63UL)} << std::endl;
		SBoxResults[i] = (sBoxes[i].Substitute(e & 63UL));
		e >>= 6;
	}

	uint32_t result = 0x0;
	for (int i = 0; i < 8; i++) {
		result <<= 4;
		result |= SBoxResults[i] & 0b1111;
	}

	//std::cout << "SBOX:\t" << std::bitset<32>{result} << std::endl;

	return Permutation(result);
}

uint64_t DesEncrypter::Expansion(uint32_t in) {
	std::bitset<32> target = { Mirror(in, 32) };
	std::bitset<48> result = { 0x0 };

	//std::cout << "R: \t" << std::bitset<32>{in} << std::endl;

	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::E[i] - 1];
	}

	//std::cout << "E(R):\t" << std::bitset<48>{Mirror(result.to_ullong(), 48)} << std::endl;

	return result.to_ullong();
}

uint32_t DesEncrypter::Permutation(uint32_t in) {
	std::bitset<32> target = { Mirror(in, 32) };
	std::bitset<32> result = { 0x0 };

	//std::cout << "S:\t" << std::bitset<32>{in} << std::endl;

	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::P[i] - 1];
	}

	//std::cout << "P:\t" << std::bitset<32>{Mirror(result.to_ullong(), 32)} << std::endl;

	return result.to_ulong();
}

uint64_t DesEncrypter::FinalPermutation(uint32_t l, uint32_t r) {
	uint64_t input = (((uint64_t)l << 32) | r);
	std::bitset<64> target = { Mirror(input, 64) };
	std::bitset<64> result = { 0x0 };

	//std::cout << "R16:\t" << std::bitset<64>{input} << std::endl;

	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::FP[i] - 1];
	}

	//std::cout << "IP-1:\t" << std::bitset<64>{Mirror(result.to_ullong(), 64)} << std::endl;

	return result.to_ullong();
}


uint64_t DesEncrypter::Decrypt(uint64_t toEncrypt, uint64_t key) {
	scheduler.SetNewKey(key);
	round = 16;

	std::cout << "To Decrypt:\t" << std::hex << toEncrypt << std::endl;

	//Initial Permutatuion
	uint64_t ip = InitialPermutation(toEncrypt);

	dataBlock.R = ip & 0x00000000FFFFFFFF;
	dataBlock.L = (ip >> 32) & 0x00000000FFFFFFFF;

	//std::cout << "L:\t" << std::bitset<32>{dataBlock.L} << std::endl;
	//std::cout << "R:\t" << std::bitset<32>{dataBlock.R} << std::endl;


	while (round >= 1) {
		uint32_t r = dataBlock.R, l = dataBlock.L;
		dataBlock.R = l ^ Mirror(Feisnel(r), 32);
		dataBlock.L = r;
		round--;

		//std::cout << "L" << round - 1 << ":\t" << std::bitset<32>{dataBlock.L} << std::endl;
		//std::cout << "R" << round - 1 << ":\t" << std::bitset<32>{dataBlock.R} << std::endl;
	}


	std::cout << "Decrypted:\t" << std::hex << Mirror(FinalPermutation(dataBlock.R, dataBlock.L), 64) << std::endl;
	return Mirror(FinalPermutation(dataBlock.R, dataBlock.L), 64);
}