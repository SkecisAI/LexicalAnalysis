#pragma once
#include <iostream>
#include "MyDefinitions.h"
using namespace std;

class Result
{
public:
	Result(WordType type, char* word, int size, Result* next);
	Result* GetNextWord() { return this->next_word_; }
	void SetNextOfNow(Result* next);
	void PrintResult();
	Result* GetLast() { return this->now; }
private:
	void PrintSelf_();
	WordType type_;                // number of type
	char* word_pt_ = NULL;         // the word
	int word_size_ = 0;            // size of word or number of words
	Result* next_word_ = NULL;     // next
	static Result* now;
};
Result* Result::now = NULL;

Result::Result(WordType type, char* word=NULL, int size=0, Result* next=NULL)
{
	type_ = type;
	word_pt_ = word;
	word_size_ = size;
	next_word_ = next;
	if (!now)
	{
		now = this;
	}
}

void Result::PrintSelf_()
{
	cout << '(' << (int)this->type_ << ", " << word_type_names[(int)this->type_] << ", ";
	cout << '"';
	for (int i = 0; i < this->word_size_; i++)
	{
		cout << word_pt_[i];
	}
	cout << '"';
	cout << ", " << this->word_size_ << ')' << endl;
}

void Result::SetNextOfNow(Result* next)
{
	this->now->next_word_ = next;
	this->now = next;
}

void Result::PrintResult()
{
	Result* tmp = this->GetNextWord();
	while (tmp)
	{
		tmp->PrintSelf_();
		tmp = tmp->GetNextWord();
	}
}