#pragma once
#include "common.h"
#include "Key_scheduler.h"
#include "SBox.h"

struct DataBlock {
	uint32_t L;
	uint32_t R;
};

class DesEncrypter {
private:
	DataBlock	 dataBlock = {0x0, 0x0};
	KeyScheduler scheduler;
	std::string  message = {""};
	int			 round = { 1 };

	std::vector<SBox> sBoxes;

public:
	DesEncrypter() : scheduler() {
		sBoxes.push_back(SBox(TranslationTables::S1));
		sBoxes.push_back(SBox(TranslationTables::S2));
		sBoxes.push_back(SBox(TranslationTables::S3));
		sBoxes.push_back(SBox(TranslationTables::S4));
		sBoxes.push_back(SBox(TranslationTables::S5));
		sBoxes.push_back(SBox(TranslationTables::S6));
		sBoxes.push_back(SBox(TranslationTables::S7));
		sBoxes.push_back(SBox(TranslationTables::S8));
	}

	uint64_t Encrypt	(uint64_t, uint64_t);
	uint64_t Decrypt	(uint64_t, uint64_t);

	uint64_t InitialPermutation	(uint64_t);
	uint64_t FinalPermutation	(uint32_t, uint32_t);

	uint32_t Feisnel	(uint32_t);
	uint64_t Expansion	(uint32_t);
	uint32_t Permutation(uint32_t);
};