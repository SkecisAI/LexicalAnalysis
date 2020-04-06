#pragma once
#include <string>
#define KEYWORDS_NUM 13
#define OPERATORS_NUM 11
#define BOUNDS_NUM 9

#define IS_IDENTIFIER(start) (('a'<=start && start<='z') || ('A'<=start && start<='Z') || (start=='_'))
#define IS_ID_PLUS(start) (('a'<=start && start<='z') || ('A'<=start && start<='Z') || (start=='_'))

#define IS_NUMBER(start) (('0'<=start && start<='9') || (start=='-'))
#define IS_NUM_PLUS(start) (start=='.')

#define IS_OPERATOR(start) is_operator(start)
#define IS_BOUND(start) is_bound(start)
#define IS_KEYWORD(start, size) is_keyword(start, size)

#define IS_NUM_FOLLOWWED(start) ('0'<=start && start<='9')
using namespace std;

enum class WordType
{
	wrongtype = 0,
	identifiers = 1,
	keywords = 2,
	operators = 3,
	constants = 4,
	bounds = 5
};
const string word_type_names[] = { "wrong type!", "identifiers", "keywords", "operators", "constants", "bounds" };

const string keywords_array[] = { "int", "char", "decimal", "bool", "const", "while", "if", "elif", "else", "main", "print", "True", "False" };
const string operators_array[] = { "-", "+", "*", "/", "!=", ">=", "<=", "==", "=", "<", ">" };
const string bounds_array[] = { ";", ",", "(", ")", "[", "]", "{", "}", "'" };

bool is_operator(char s)
{
	bool ans = false;
	for (int i = 0; i < OPERATORS_NUM; i++)
	{
		if (operators_array[i][0] == s)
		{
			ans = true;
			break;
		}
	}
	return ans;
}

bool is_bound(char s)
{
	bool ans = false;
	for (int i = 0; i < OPERATORS_NUM; i++)
	{
		if (bounds_array[i][0] == s)
		{
			ans = true;
			break;
		}
	}
	return ans;
}

bool is_keyword(char* s, int size)
{
	bool ans = false;
	for (int i = 0; i < KEYWORDS_NUM; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (keywords_array[i][j] == s[j])
			{
				ans = true;
			}
			else
			{
				ans = false;
				break;
			}
		}
		if (ans)
		{
			break;
		}
	}
	return ans;
}