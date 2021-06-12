#include "DES_encrypter.h"

uint64_t DES_encrypter::Encrypt(std::string toEncrypt, uint64_t key) {
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

		std::cout << "IP:\t" << std::hex << dataBlock.L << " " << dataBlock.R << std::endl;

		while (round <= 16) {
			Round();
			round++;
		}
		//Final Permutation
		uint32_t l = dataBlock.L, r = dataBlock.R;
		dataBlock.L = r;
		dataBlock.R = l;
		return FinalPermutation();
	}
}

uint64_t DES_encrypter::InitialPermutation(std::string token) {
	std::bitset<64> plainText = { StrToAscii(token) };
	std::bitset<64> result = { 0x0 };
	std::cout << "encryptDES(" << std::hex << plainText.to_ullong() << ")" << std::endl;
	for (int i = 0; i < result.size(); i++) {
		result[i] = plainText[TranslationTables::IP[i] - 1];
	}
	return result.to_ullong();
}

uint64_t DES_encrypter::FinalPermutation() {
	std::bitset<64> target = { (((uint64_t)dataBlock.L << 32) | dataBlock.R) };
	std::bitset<64> result = { 0x0 };
	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::FP[i] - 1];
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
	std::cout << "Rnd" << round << "\t (" << std::hex << dataBlock.R << " " << dataBlock.L << ")";
	uint32_t l = dataBlock.L, r = dataBlock.R;
	dataBlock.L = r;
	dataBlock.R = l ^ Ffunction(r);
}

uint32_t DES_encrypter::Ffunction(uint32_t r) {
	std::cout << "\tkey=" << std::hex << scheduler.getSheduledKey(round) << std::endl;
	uint64_t buffer = Expand(r) ^ scheduler.getSheduledKey(round);
	/*TO DO S-Blocks*/
	uint32_t s_result = 0x0;
	//for (int i = 0; i < sBoxes.size(); i++) {
	for (int i = sBoxes.size() - 1; i >= 0; i--){
		uint8_t toSBox = (buffer & 63UL);
		buffer >>= 6;
		std::cout << std::bitset<32>{s_result} << std::endl;
		s_result |= (sBoxes[i].Substitute(toSBox) & 0xF) << (4*(sBoxes.size() - 1 - i));
	}
	/*TO DO Permutation*/
	std::bitset<32> target = { s_result };
	std::bitset<32> result = { 0x0 };
	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::P[i] - 1];
	}
	return result.to_ulong();
}

uint64_t DES_encrypter::Expand(uint32_t toExpand) {
	std::bitset<32> target = { toExpand };
	std::bitset<48> result = { 0x0 };
	for (int i = 0; i < result.size(); i++) {
		result[i] = target[TranslationTables::E[i] - 1];
	}
	return result.to_ullong();
}