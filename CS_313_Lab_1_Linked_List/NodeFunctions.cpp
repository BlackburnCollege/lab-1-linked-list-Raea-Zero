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
void deleteNode(Node* head, int delValue)
{
	//here on is original code
	Node* priorNodePtr = NULL;
	Node* targetNodePtr = NULL;
	//search for nodes that contain the target value
	//repeat until the end of list
	do
	{
		priorNodePtr = getPriorNode(head, delValue);
		
		if (priorNodePtr != NULL)
		{
			targetNodePtr = priorNodePtr->next;
			//replace prior node->next with target->next, so that it points at the value after the target
			if (targetNodePtr != NULL)
			{
				//I added this extra check because it crashed and told me it was because this line failed due to targetNodePtr being null
				priorNodePtr->next = targetNodePtr->next;
			}

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
		free(*head);
		return;
	}
	else
	{
		do
		{
			targetNodePtr = *head;
			//save the pointer at the next node if it's not null
			nextNodePtr = targetNodePtr->next;
			//free the current node
			free(targetNodePtr);
			//repeat
			targetNodePtr = nextNodePtr;
		} while (targetNodePtr != NULL);
		free(*head);
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
