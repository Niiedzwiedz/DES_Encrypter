#include "common.h"
#include "DES_Encrypter.h"

int main() {
	DesEncrypter encrypter;
	uint64_t result = encrypter.Encrypt(0x0123456789ABCDEF, 0x133457799BBCDFF1);
	encrypter.Decrypt(result, 0x133457799BBCDFF1);
	return 0;
}