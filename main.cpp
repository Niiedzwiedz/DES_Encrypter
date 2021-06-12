#include "common.h"
#include "DES_encrypter.h"

/*
uint64_t strtoascii(std::string toconvert) {
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
*/

int main() {
	std::string message = "00000000";
	uint64_t key = 0x01E001E001F101F1;
	//uint64_t key = 0x0000000000000001;
	//uint64_t key = 0x000000000000000;
	DES_encrypter encrypter;
	std::cout << "setKey(" << std::hex << key << ")" << std::endl;
	std::cout << "Encrypted(hex):\t\t" << std::hex << encrypter.Encrypt(message, key) << std::endl;
	
	/*
	std::string message = "Hello";
	while (!message.empty()) {
		std::string token = message.substr(0, 8);
		message.erase(0, 8);
		std::cout << token << " -> ";
		std::cout << std::hex << strtoascii(token) << std::endl;
	}
	*/
	return 0;
}