#pragma once
#include "common.h"
#include "Key_scheduler.h"
#include "SBox.h"

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
	std::vector<SBox> sBoxes;

protected:

public:
	DES_encrypter() :  dataBlock{ 0x0, 0x0 }, message(""), scheduler() { 
		sBoxes.push_back(SBox(TranslationTables::S1));
		sBoxes.push_back(SBox(TranslationTables::S2));
		sBoxes.push_back(SBox(TranslationTables::S3));
		sBoxes.push_back(SBox(TranslationTables::S4));
		sBoxes.push_back(SBox(TranslationTables::S5));
		sBoxes.push_back(SBox(TranslationTables::S6));
		sBoxes.push_back(SBox(TranslationTables::S7));
		sBoxes.push_back(SBox(TranslationTables::S8));
	}

	void Encrypt(std::string, uint64_t);
	uint64_t InitialPermutation(std::string);
	uint64_t StrToAscii(std::string);
	void Round();
	uint32_t Ffunction(uint32_t);
	uint64_t Expand(uint32_t);
};