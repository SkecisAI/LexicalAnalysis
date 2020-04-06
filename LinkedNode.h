#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "ScannerArea.h"
#include "AnalysisResult.h"
using namespace std;

class LinkedList
{
public:
	LinkedList(Node *p, string filename);
	void AddOneNode(Node *p);
	Node* GetHeadOfList() { return this->head_node_; }
	int GetLengthOfList() { return this->list_len_; }
	Node* GetNextNode();
	void PeekWords();
	void ReadText2List(ifstream* ins);
	void LexicalAnalysis();
private:
	Node* head_node_ = NULL;
	int list_len_;
	static Node* current_node_;
};

Node* LinkedList::current_node_ = NULL;

LinkedList::LinkedList(Node *p, string filename)
{
	head_node_ = p;
	current_node_ = head_node_;
	list_len_ = 0;
	// read text file
	ifstream infile;
	infile.open(filename);
	this->ReadText2List(&infile);
	infile.close();
}

void LinkedList::AddOneNode(Node *p)
{
	Node* tmp = this->head_node_;
	while (tmp)
	{
		if (!tmp->GetNext())
		{
			tmp->SetNextNode(p);
			this->list_len_ += 1;
			break;
		}
		tmp = tmp->GetNext();
	}
}

Node* LinkedList::GetNextNode()
{
	current_node_ = current_node_->GetNext(); 
	return current_node_;
}

void LinkedList::PeekWords()
{
	Node* p = this->head_node_;
	while (p)
	{
		if (p->GetNext())
		{
			cout << p->GetNext()->GetStringVal() << endl;
		}
		p = p->GetNext();
	}
}

void LinkedList::ReadText2List(ifstream* instream)
{
	string codestring = "";
	while (!(*instream).eof())
	{
		*instream >> codestring;                     // read a word separated by space
		Node* p = new Node(codestring, NULL);
		this->AddOneNode(p);
	}
}

void LinkedList::LexicalAnalysis()
{
	ScannerArea scanner_area;
	Result* result_head = new Result(WordType::wrongtype);
	Node* tmp = this->GetNextNode();
	string s;
	while (tmp)
	{
		s = tmp->GetStringVal();
		for (int i = 0; i < (int)s.length(); i++)
		{
			if (!scanner_area.PutValueIn(i, s[i]))          // while area is full
			{
				scanner_area.Anaylzer(result_head->GetLast(), false);
			}
		}
		scanner_area.Anaylzer(result_head->GetLast(), true);      // until the word's end
		tmp = tmp->GetNext();
	}
	result_head->PrintResult();
}
