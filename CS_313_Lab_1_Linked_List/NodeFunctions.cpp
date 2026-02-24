#pragma once
#include "Node.h"
#include <iostream>
#include <string>
#include <fstream>

void insertNode(Node** head, int newValue)
{
	Node* tempNodePtr = NULL;
	tempNodePtr = (Node*)malloc(sizeof(Node));
	if (tempNodePtr == NULL)
	{
		return;
	}
	tempNodePtr->value = newValue;
	tempNodePtr->next = *head;
	*head = tempNodePtr;
	return;
}

Node* searchList(Node* head, int searchValue)
{
	Node* tempNodePtr = NULL;
	if (head == NULL)
	{
		return NULL;
	}
	tempNodePtr = head;
	do
	{
		if (tempNodePtr->value == searchValue)
		{
			return tempNodePtr;
		}
		tempNodePtr = tempNodePtr->next;
	} while (tempNodePtr != NULL);
	return NULL;
}

//delete ALL nodes containing the value
void deleteNode(Node* &head, int delValue)
{
	//here on is original code
	Node* priorNodePtr = NULL;
	Node* targetNodePtr = NULL;
	//search for nodes that contain the target value
	//repeat until the end of list
	do
	{
		//getPriorNode returns the target node if it is the first item in the list, handle this case
		priorNodePtr = getPriorNode(head, delValue);
		if (priorNodePtr != NULL && priorNodePtr->value == delValue)
		{
			head = priorNodePtr->next;
			free(priorNodePtr);
		}
		else if (priorNodePtr != NULL)
		{
			targetNodePtr = priorNodePtr->next;
			//replace prior node->next with target->next, so that it points at the value after the target
			priorNodePtr->next = targetNodePtr->next;
			//remove the original node to free memory (destructor?)
			free(targetNodePtr);
		}
	} while (priorNodePtr != NULL);
}

//same as search, but returns the node prior to the found value
Node* getPriorNode(Node* head, int searchValue)
{
	Node* tempNodePtr = NULL;
	Node* priorPtr = NULL;
	if (head == NULL)
	{
		return NULL;
	}
	tempNodePtr = head;
	priorPtr = head;
	do
	{
		if (tempNodePtr->value == searchValue)
		{
			return priorPtr;
		}
		priorPtr = tempNodePtr;
		tempNodePtr = tempNodePtr->next;
	} while (tempNodePtr != NULL);
	return NULL;
}

//go through the list and free every node
void deleteList(Node** head)
{
	Node* targetNodePtr = NULL;
	Node* nextNodePtr = NULL;
	if (*head == NULL)
	{
		//originally had a free(head) line here but removed it for the reason explained at the end of the function.
		return;
	}
	else
	{
		targetNodePtr = *head;
		do
		{
			nextNodePtr = NULL;
			//save the pointer at the next node if it's not null
			if (targetNodePtr->next != NULL)
			{
				nextNodePtr = targetNodePtr->next;
			}
			//free the current node
			free(targetNodePtr);
			//repeat
			targetNodePtr = nextNodePtr;
		} while (targetNodePtr != NULL);
		//I originally had this line here, thinking that I needed to free the head. However, it keeps breaking, and when I pause the program and check the value, it shows a "node" with
		//a value of -572662307 and an evidently NULL next. I searched and -572662307 is not in the list, so my best guess is that by this point, head is pointing at nothing and
		//interpreting whatever's there as junk for the value and pointer. What's concerning to me is the consistency; value is ALWAYS -572662307 and next is ALWAYS 0xddddddddddd...., it never changes like I'd expect junk to.
		//but it works after I remove this line, so I guess it's fine...? I just hope there's not still a small memory leak.

		//free(head);
		return;
	}
}

//read a file and fill the list, returning true if successful and false if the file opening failed
bool createList(std::string fileName, Node* &head)
{
	std::ifstream numbersFile;
	numbersFile.open(fileName);
	if (numbersFile.is_open())
	{
		//populate the list with the file's data, then close the file
		std::string strCurrentNum;
		int currentNum;
		do
		{
			std::getline(numbersFile, strCurrentNum);
			if (strCurrentNum != "")
			{
				currentNum = std::stoi(strCurrentNum);
				insertNode(&head, currentNum);
			}
			else
			{
				break;
			}
		} while (!numbersFile.eof());

		numbersFile.close();
		return true;
	}
	else
	{
		return false;
	}
}
