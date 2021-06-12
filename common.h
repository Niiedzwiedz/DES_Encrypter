#pragma once
#include <iostream>
#include <iomanip>
#include <bitset>
#include <bit>
#include <cstdint>
#include <string>
#include <vector>

class TranslationTables {
public:
	static const unsigned int IP[64];
	static const unsigned int FP[64];
	static const unsigned int E[48];
	static const unsigned int P[32];
	static const uint8_t S1[4][16];
	static const uint8_t S2[4][16];
	static const uint8_t S3[4][16];
	static const uint8_t S4[4][16];
	static const uint8_t S5[4][16];
	static const uint8_t S6[4][16];
	static const uint8_t S7[4][16];
	static const uint8_t S8[4][16];
	static const unsigned int PC1[56];
	static const unsigned int PC2[48];
};

const unsigned int TranslationTables::IP[64] = {
		58, 50, 42, 34, 26, 18, 10,  2,
		60, 52, 44, 36, 28, 20, 12,  4,
		62, 54, 46, 38, 30, 22, 14,  6,
		64, 56, 48, 40, 32, 24, 16,  8,
		57, 49, 41, 33, 25, 17,  9,  1,
		59, 51, 43, 35, 27, 19, 11,  3,
		61, 53, 45, 37, 29, 21, 13,  5,
		63, 55, 47, 39, 31, 23, 15,  7
};

const unsigned int TranslationTables::FP[64] = {
	40,  8, 48, 16, 56, 24, 64, 32,
	39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30,
	37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28,
	35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26,
	33,  1, 41,  9, 49, 17, 57, 25
};

const unsigned int TranslationTables::E[48] = {
	32,  1,  2,  3,  4,  5,
	 4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32,  1
};

const unsigned int TranslationTables::P[32] = {
	16,  7, 20, 21, 29, 12, 28, 17,
	 1, 15, 23, 26,  5, 18, 31, 10,
	 2,  8, 24, 14, 32, 27,  3,  9,
	19, 13, 30,  6, 22, 11,  4, 25
};

const uint8_t TranslationTables::S1[4][16] = {
	{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
	{ 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
	{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
	{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
};

const uint8_t TranslationTables::S2[4][16] = {
	{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
	{ 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
	{ 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
	{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
};

const uint8_t TranslationTables::S3[4][16] = {
	{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
	{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
	{13,  6,  4,  9,  8, 15,  3,  0,  1,  1,  2, 12,  5, 10, 14,  7},
	{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
};

const uint8_t TranslationTables::S4[4][16] = {
	{},
	{},
	{},
	{}
};

const uint8_t TranslationTables::S5[4][16] = {
	{},
	{},
	{},
	{}
};

const uint8_t TranslationTables::S6[4][16] = {
	{},
	{},
	{},
	{}
};

const uint8_t TranslationTables::S7[4][16] = {
	{},
	{},
	{},
	{}
};

const uint8_t TranslationTables::S8[4][16] = {
	{},
	{},
	{},
	{}
};

const unsigned int TranslationTables::PC1[56] = {
	57, 49, 41, 33, 25, 17,  9,  1,
	58, 50, 42, 34, 26, 18, 10,  2,
	59, 51, 43, 35, 27, 19, 11,  3,
	60, 52, 44, 36, 63, 55, 47, 39,
	31, 23, 15,  7, 62, 54, 46, 38,
	30, 22, 14,  6, 61, 53, 45, 37,
	29, 21, 13,  5, 28, 20, 12,  4
};

const unsigned int TranslationTables::PC2[48] = {
	14, 17, 11, 24,  1,  5,  3, 28,
	15,  6, 21, 10, 23, 19, 12,  4,
	26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32
};

//==========================================================//
//						  CLI COLORS						//
//==========================================================//

#define RESET	"\033[0m"	//Reset
#define BLACK	"\033[30m"	//Black
#define RED		"\033[31m"	//Red
#define GREEN	"\033[32m"	//Green
#define YELLOW	"\033[33m"	//Yellow
#define BLUE	"\033[34m"	//Blue
#define MAGENTA	"\033[35m"	//Magenta
#define CYAN	"\033[36m"	//Cyan
#define WHITE	"\033[37m"	//White

#define BRIGHTBLACK		"\033[90m"	//Bright Black
#define BRIGHTRED		"\033[91m"	//Bright Red
#define BRIGHTGREEN		"\033[92m"	//Bright Green
#define BRIGHTYELLOW	"\033[93m"	//Bright Yellow
#define BRIGHTBLUE		"\033[94m"	//Bright Blue
#define BRIGHTMAGENTA	"\033[95m"	//Bright Magenta
#define BRIGHTCYAN		"\033[96m"	//Bright Cyan
#define BRIGHTWHITE		"\033[97m"	//Bright White