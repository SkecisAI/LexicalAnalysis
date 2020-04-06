#include <iostream>
#include "WordForm.h"
#include "LinkedNode.h"
#include "MyDefinitions.h"
using namespace std;


int main(void)
{
	WordsForm my_keywords(keywords_array, sizeof(keywords_array) / sizeof(keywords_array[0]), WordType::keywords);
	WordsForm my_operators(operators_array, sizeof(operators_array) / sizeof(operators_array[0]), WordType::operators);
	WordsForm my_bounds(bounds_array, sizeof(bounds_array) / sizeof(bounds_array[0]), WordType::bounds);
	Node* head_node = new Node("HEAD", NULL);
	string filename = "codes.txt";
	LinkedList my_codes(head_node, filename);

	my_codes.LexicalAnalysis();
	return 0;
}