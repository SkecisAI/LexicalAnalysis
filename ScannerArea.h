#pragma once
#include <iostream>
#include "MyDefinitions.h"
#include "AnalysisResult.h"
#define MAX_SCANNER_SIZE 50   // the max length of scanner
#define BOUNDARY_SIZE 25      // the max length of identifier
#define BLANK_SIGN '#'
using namespace std;


class ScannerArea
{
public:
	ScannerArea();
	char operator[](int i) { return scanner_area_[i]; }
	bool PutValueIn(int i, char c);
	void CheckArea();
	bool IsAreaBlank();
	void Anaylzer(Result* res, bool is_word_tail);
	void PeekArea();
	WordType JudgeFirstChar(char c);
	WordType JudgeFollowedChars(char c, WordType last);
private:
	char scanner_area_[MAX_SCANNER_SIZE]="";
	static bool area_is_full;
	static int start;
	static int seek;
};
bool ScannerArea::area_is_full = false;
int ScannerArea::start = 0;
int ScannerArea::seek = 0;

ScannerArea::ScannerArea()
{
	for (int i = 0; i < MAX_SCANNER_SIZE; i++)
	{
		scanner_area_[i] = BLANK_SIGN;
	}
}

void ScannerArea::PeekArea()
{
	cout << "Scanner Area('#' as blank):  ";
	for (int i = 0; i < MAX_SCANNER_SIZE; i++)
	{
		cout << this->scanner_area_[i];
	}
	cout << endl;
}

bool ScannerArea::PutValueIn(int i, char c)
{
	int index = i % MAX_SCANNER_SIZE;
	if (!area_is_full && scanner_area_[index] == BLANK_SIGN)
	{
		this->scanner_area_[index] = c;
		this->CheckArea();
		return true;
	}
	else
	{
		return false;
	}
}

void ScannerArea::CheckArea()
{
	area_is_full = true;
	for (int i = 0; i < MAX_SCANNER_SIZE; i++)
	{
		if (this->scanner_area_[i] == BLANK_SIGN)
		{
			area_is_full = false;
			return;
		}
	}
}

void ScannerArea::Anaylzer(Result* res_now, bool is_word_tail)
{
	seek = start;			            // the start point of analysis
	WordType start_type=WordType::wrongtype, last_type=WordType::wrongtype;
	int length=1;
	char read_char;
	char* s = NULL;
	Result* word;
	while (this->scanner_area_[seek] != BLANK_SIGN)
	{
		read_char = this->scanner_area_[seek];
		if (seek == start)
		{
			start_type = this->JudgeFirstChar(read_char);
			last_type = start_type;
			length = 1;
		}
		else
		{
			last_type = start_type;
			start_type = this->JudgeFollowedChars(read_char, last_type);
			length++;
		}
		// identify a word with last type
		if (start_type!=last_type)
		{
			s = (char*)malloc(sizeof(char) * (length - 1));
			int count = 0;
			while (count < length - 1)
			{
				s[count] = this->scanner_area_[(start + count) % MAX_SCANNER_SIZE];
				this->scanner_area_[(start + count) % MAX_SCANNER_SIZE] = BLANK_SIGN;
				count++;
			};
			if (last_type==WordType::identifiers)
			{
				if (IS_KEYWORD(s, length-1))
				{
					last_type = WordType::keywords;
				}
			}
			word = new Result(last_type, s, length - 1);
			res_now->SetNextOfNow(word);

			start = seek;                       // only change the start after getting a result
			area_is_full = false;
			continue;
		}
		if (last_type == WordType::bounds)
		{
			s = (char*)malloc(sizeof(char));
			s[0] = this->scanner_area_[(start + 0) % MAX_SCANNER_SIZE];
			this->scanner_area_[(start + 0) % MAX_SCANNER_SIZE] = BLANK_SIGN;
			word = new Result(last_type, s, 1);
			res_now->SetNextOfNow(word);

			seek++;
			start = seek;                       // only change the start after getting a result
			area_is_full = false;
			continue;
		}
		seek++;
		seek = seek % MAX_SCANNER_SIZE;         // circulation
	}

	if (is_word_tail && !this->IsAreaBlank())  // if the end of word
	{
		s = (char*)malloc(sizeof(char) * length);
		int count = 0;
		while (count < length)
		{
			s[count] = this->scanner_area_[(start + count) % MAX_SCANNER_SIZE];
			this->scanner_area_[(start + count) % MAX_SCANNER_SIZE] = BLANK_SIGN;
			count++;
		};
		if (last_type == WordType::identifiers)
		{
			if (IS_KEYWORD(s, length - 1))
			{
				last_type = WordType::keywords;
			}
		}
		word = new Result(last_type, s, length);
		res_now->SetNextOfNow(word);
	}

	if (this->IsAreaBlank())  // reflesh scanner area
	{
		start = 0;
		seek = 0;
	}
}

WordType ScannerArea::JudgeFirstChar(char c)
{
	if (IS_IDENTIFIER(c))
	{
		return WordType::identifiers;
	}
	else if (IS_NUMBER(c))
	{
		return WordType::constants;
	}
	else if (IS_OPERATOR(c))
	{
		return WordType::operators;
	}
	else if (IS_BOUND(c))
	{
		return WordType::bounds;
	}
	else
	{
		return WordType::wrongtype;
	}
}

WordType ScannerArea::JudgeFollowedChars(char c, WordType last)
{
	if (IS_ID_PLUS(c))
	{
		return WordType::identifiers;
	}
	else if (IS_NUM_PLUS(c))
	{
		return WordType::constants;
	}
	else if (IS_OPERATOR(c))
	{
		return WordType::operators;
	}
	else if (IS_BOUND(c))
	{
		return WordType::bounds;
	}
	else if (IS_NUM_FOLLOWWED(c))
	{
		if (last == WordType::identifiers || last == WordType::constants)
		{
			return last;
		}
		else
		{
			return WordType::constants;
		}
	}
	else
	{
		return WordType::wrongtype;
	}
}

bool ScannerArea::IsAreaBlank()
{
	bool area_is_blank = true;
	for (int i = 0; i < MAX_SCANNER_SIZE; i++)
	{
		if (this->scanner_area_[i] != BLANK_SIGN)
		{
			area_is_blank = false;
			break;
		}
	}
	return area_is_blank;
}