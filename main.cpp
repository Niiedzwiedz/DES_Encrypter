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
	std::string message = "Hello";
	uint64_t key = 0xDC41346232A10023;
	DES_encrypter encrypter;
	encrypter.Encrypt(message, key);
	
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