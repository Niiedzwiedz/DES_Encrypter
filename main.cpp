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

void getFromKeyboard(std::vector<uint64_t>& result) {	//If no args
	std::cout << "Type message to encode: ";
	std::string inMessage;
	std::getline(std::cin, inMessage);

	while (!inMessage.empty()) {
		//Get token
		result.push_back(StrToAscii(inMessage.substr(0, 8)));
		inMessage.erase(0, 8);
	}
}

void getFromFile(std::vector<uint64_t>& result, std::string file) { //If 1 arg
	std::cout << "Reading From File: " << file << std::endl;
	
	std::ifstream is(file, std::ifstream::binary);
	char buffer[8];
	while (is.good()) {
		for (int i = 0; i < 8; i++) buffer[i] = 0;
		is.read(buffer, 8);

		uint64_t token = 0x0;
		for (int i = 0; i < 8; i++) {
			token <<= 8;
			token |= (uint8_t)buffer[i];
		}
		result.push_back(token);

		if (is.eof()) break;
	}
}

int main(int argc, char* argv[]) {
	//Check input
	std::vector<uint64_t> message;
	if (argc < 2) getFromKeyboard(message);
	else getFromFile(message, argv[1]);

	DesEncrypter encrypter;
	std::vector<uint64_t> encrypted;
	std::vector<uint64_t> keys;
	std::ifstream is("key.bin", std::ifstream::binary);

	//Encrypt Data Blocks
	for (int i = 0; i < message.size(); i++) {

		std::cout << "======== Block no. " << std::setfill('0') << std::setw(size_t(4)) << std::dec << i+1 << " ========" << std::endl;

		//Read Key From File;
		char buffer[8];
		is.read(buffer, 8);
		uint64_t key = 0x0;
		for (int i = 0; i < 8; i++) {
			key <<= 8;
			key |= (uint8_t)buffer[i];
		}
		keys.push_back(key);

		//Encryption
		encrypted.push_back(encrypter.Encrypt(message[i], keys[i]));
		//Control Decryption
		uint64_t decrypted = encrypter.Decrypt(encrypted[i], keys[i]);

		//Printing
		std::cout << "[Str] Message:\t" << AsciiToStr(message[i]) << std::endl;
		std::cout << "[Hex] Message:\t" << std::hex << message[i] << std::endl;
		std::cout << "[Hex] Key:    \t" << std::hex << keys[i] << std::endl;
		std::cout << "[Hex] Encoded:\t" << std::hex << std::setfill('0') << std::setw(16) << encrypted[i] << std::endl;
		std::cout << "[Hex] Decoded:\t" << std::hex << decrypted;

		if (decrypted == message[i]) std::cout << " OK" << std::endl;
		else std::cout << " FAILURE" << std::endl;
	}

	std::cout << "======= [Hex] Encrypted: =======" << std::endl;

	//Save result to file
	std::ofstream os("out.bin", std::ifstream::binary);
	for (int i = 0; i < encrypted.size(); i++) {
		std::cout << std::setfill('0') << std::setw(16) << encrypted[i];
		os << encrypted[i];
		if (i % 2 == 1  && i+1 < encrypted.size()) std::cout << std::endl;
	}

	os.close();
	is.close();

	std::cout << std::endl << "================================" << std::endl;
	std::cout << std::endl << "Press Enter to close program.";

	getchar();
	return 0;
}