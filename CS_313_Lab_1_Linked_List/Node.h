#pragma once
#include <fstream>

struct Node
{
	int value;
	Node* next;
};

void insertNode(Node** head, int newValue);

Node* searchList(Node* head, int searchValue);

void deleteNode(Node* head, int delValue);

//here on is original code
Node* getPriorNode(Node* head, int searchValue);

void deleteList(Node** head);

bool createList(std::string fileName, Node* &head);