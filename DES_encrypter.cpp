#include "DES_encrypter.h"

void DES_encrypter::Encrypt(std::string toEncrypt, uint64_t key) {
	message = toEncrypt;
	scheduler.SetNewKey(key);
	round = 1;
	while (!toEncrypt.empty()) {
		//Get token
		std::string token = toEncrypt.substr(0, 8);
		toEncrypt.erase(0, 8);

		//Initial Permutatuion
		uint64_t bitBlock = InitialPermutation(token);

		//Save Data Before 16 rounds
		dataBlock.R = (bitBlock & 0x00000000FFFFFFFF);
		bitBlock >>= 32;
		dataBlock.L = (bitBlock & 0x00000000FFFFFFFF);

		while (round <= 16) {
			Round();
			round++;
		}
	}
}

uint64_t DES_encrypter::InitialPermutation(std::string token) {
	std::bitset<64> plainText = { StrToAscii(token) };
	std::bitset<64> result = { 0x0 };
	for (int i = 0; i < result.size(); i++) {
		result[i] = plainText[TranslationTables::IP[i] - 1];
	}
	return result.to_ullong();
}

uint64_t DES_encrypter::StrToAscii(std::string toconvert) {
	uint64_t result = 0x0;
	int i = 0;
	while (i < toconvert.length()) {
		result <<= 8;
		result |= ((int)(char)toconvert.at(i) & 255UL);
		i++;
	}
	result <<= 8 * (8 - i);
	return result;
}


void DES_encrypter::Round() {
	uint32_t l = dataBlock.L, r = dataBlock.R;
	dataBlock.L = r;
	dataBlock.R = l ^ Ffunction(r);
}

uint32_t DES_encrypter::Ffunction(uint32_t r) {
	uint64_t xorResult = Expand(r) ^ scheduler.getSheduledKey(round);
	/*TO DO S-Blocks*/
	/*TO DO Permutation*/
	return 0x0;
}

uint64_t DES_encrypter::Expand(uint32_t toExpand) {
	std::bitset<64> target = { toExpand };
	std::bitset<48> result = { 0x0 };
	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::E[i] - 1];
	}
	return result.to_ullong();
}