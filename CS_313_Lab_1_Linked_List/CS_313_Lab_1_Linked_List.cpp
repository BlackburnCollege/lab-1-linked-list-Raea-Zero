#include <iostream>
#include "Node.h"
#include <fstream>
#include <string>

int main()
{
    //create the list head, get the file name, fill the list
    Node* numList = NULL;
    std::string fileName;
    bool readSuccess;
    std::cout << "Welcome to the integer list editor!\n\nPlease enter a file name (default: numbers.csv): ";
    std::getline(std::cin, fileName);
    if (fileName == "")
    {
        fileName = "numbers.csv";
    }
    readSuccess = createList(fileName, numList);
    while (readSuccess = false)
    {
        std::cout << "\nI'm sorry, that file doesn't seem to exist. Please enter a new file name: ";
        std::getline(std::cin, fileName);
        if (fileName == "")
        {
            fileName = "numbers.csv";
        }
        readSuccess = createList(fileName, numList);
    }

    //Present the menu
    int choice;
    do
    {
        std::string strChoice;
        std::cout << "Welcome to the main menu!\nNOTE: PLEASE EXIT THE PROGRAM THROUGH THE MENU TO AVOID MEMORY LEAK\n\n1) Search For Value\n2) Add Value\n3) Delete Value\n4) Exit\n\nYour Selection: ";
        std::getline(std::cin, strChoice);
        choice = std::stoi(strChoice);
        while (choice < 1 || choice > 4)
        {
            std::cout << "\nI'm sorry, please enter a valid menu option (1-4): ";
            std::getline(std::cin, strChoice);
            choice = std::stoi(strChoice);
        }
        if (choice == 1)
        {
            int searchValue;
            std::string strSearchValue;
            std::cout << "\nPlease enter the integer you would like to search for: ";
            std::getline(std::cin, strSearchValue);
            searchValue = std::stoi(strSearchValue);
            Node* resultPtr = NULL;
            resultPtr = searchList(numList, searchValue);
            if (resultPtr == NULL)
            {
                std::cout << "\nFALSE: I'm sorry, " << searchValue << " is not in the list.\n\n";
            }
            else
            {
                std::cout << "\nTRUE: " << searchValue << " is in the list.\n\n";
            }
        }
        else if (choice == 2)
        {
            int newValue;
            std::string strNewValue;
            std::cout << "\nPlease enter the integer you would like to add to the list: ";
            std::getline(std::cin, strNewValue);
            newValue = std::stoi(strNewValue);
            insertNode(&numList, newValue);
            std::cout << "\nAdded!\n\n";
        }
        else if (choice == 3)
        {
            int removeValue;
            std::string strRemoveValue;
            std::cout << "\nPlease enter the integer you would like to remove from the list: ";
            std::getline(std::cin, strRemoveValue);
            removeValue = std::stoi(strRemoveValue);
            deleteNode(numList, removeValue);
            std::cout << "\nAll instances of " << removeValue << " removed from the list.\n\n";
        }
        else
        {
            deleteList(&numList);
            std::cout << "\nList deleted, memory cleared. Have a nice day!";
        }
    } while (choice != 4);
}

