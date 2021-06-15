#include "common.h"
#include "DES_Encrypter.h"

uint64_t StrToAscii(std::string toconvert) {
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

std::string AsciiToStr(uint64_t toconvert) {
	std::string result = "";
	int i = 0;
	while (i < 8) {
		result += ((char)(toconvert & 255UL));
		toconvert >>= 8;
		i++;
	}
	for (int i = 0; i < 4; i++) {
		std::swap(result[i], result[7 - i]);
	}
	return result;
}


int main(int argc, char* argv[]) {
	DesEncrypter encrypter;

	std::cout << "Wprowadz wiadomosc do zakodowania: ";

	std::string inMessage;
	std::cin >> inMessage;

	std::vector<uint64_t> message;
	std::vector<uint64_t> keys;
	while (!inMessage.empty()) {
		//Get token
		message.push_back(StrToAscii(inMessage.substr(0, 8)));
		inMessage.erase(0, 8);
	}

	std::ifstream is("key.bin", std::ifstream::binary);

	for (int i = 0; i < message.size(); i++) {
		char buffer[8];
		is.read(buffer, 8);

		uint64_t key = 0x0;
		for (int i = 0; i < 8; i++) {
			key <<= 8;
			key |= buffer[i];
		}
		keys.push_back(key);

		std::cout << "[Str] Message:\t" << AsciiToStr(message[i]) << std::endl;
		std::cout << "[Hex] Key:    \t" << std::hex << keys[i] << std::endl;

		uint64_t result = encrypter.Encrypt(message[i], keys[i]);

		std::cout << "[Hex] Encoded:\t" << std::hex << result << std::endl;

		result = encrypter.Decrypt(result, keys[i]);

		std::cout << "[Hex] Decoded:\t" << std::hex << result << std::endl;

		std::cout << "================================" << std::endl;
	}

	return 0;
}