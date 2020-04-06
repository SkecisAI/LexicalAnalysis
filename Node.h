#pragma once
#include <iostream>
using namespace std;
class Node
{
public:
	Node(string s, Node* p);
	Node* GetNext();
	void SetNextNode(Node* p);
	string GetStringVal() { return this->str_val_; }
private:
	string str_val_ = "#";
	Node* next = NULL;
};

Node::Node(string s, Node* p)
{
	this->str_val_ = s;
	this->next = p;
}

Node* Node::GetNext()
{
	return this->next;
}

void Node::SetNextNode(Node* p)
{
	this->next = p;
}