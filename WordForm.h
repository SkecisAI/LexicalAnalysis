#pragma once
#include <iostream>
#include <fstream>
#include "MyDefinitions.h"
using namespace std;

class WordsForm
{
public:
	WordsForm(const string s[], int len, WordType tp);
	int GetIdOfWord(string word);
	int GetLengthOfForm() { return this->form_len_; }
	WordType GetNameOfForm() { return this->form_type_; }
private:
	const string* words_form_ = NULL;
	WordType form_type_;
	int form_len_ = 0;
};

WordsForm::WordsForm(const string s[], int len, WordType tp)
{
	words_form_ = s;
	form_len_ = len;
	form_type_ = tp;
}

int WordsForm::GetIdOfWord(string word)
{
	for (int i = 0; i < this->form_len_; i++)
	{
		const char* s1 = this->words_form_[i].c_str();
		const char* s2 = word.c_str();
		if (strcmp(s1, s2) == 0)
		{
			return i;
		}
	}
	return -1;
}