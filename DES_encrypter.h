#pragma once
#include "common.h"
#include "Key_scheduler.h"

struct TextBlock {
	uint32_t L;
	uint32_t R;
};

class DES_encrypter {
private:
	TextBlock dataBlock;
	std::string message;
	KeyScheduler scheduler;
	int round = { 1 };

protected:

public:
	DES_encrypter() :  dataBlock{ 0x0, 0x0 }, message(""), scheduler() {  }

	void Encrypt(std::string, uint64_t);
	uint64_t InitialPermutation(std::string);
	uint64_t StrToAscii(std::string);
	void Round();
	uint32_t Ffunction(uint32_t);
	uint64_t Expand(uint32_t);
};