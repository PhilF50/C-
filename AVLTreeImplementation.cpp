// AVLTrees1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Philip Fahey - K00217355

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "AVlTree.h"

using namespace std;

template<class ItemType>
struct TreeNode;

void ShowMenu();
void Exit();


TreeType<string> AVLTree;

int main()
{
	
	int option;
	string item;

	do {
		ShowMenu();
		cout << "\tPlease select a Menu option: \n";
		cout << "\tOption: ";
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "\tEnter Item: ";
			cin >> item;
			AVLTree.InsertItem(item);
			system("cls");
			break;
		case 2:
			AVLTree.PrintTree();
			system("PAUSE");
			system("cls");
			break;

		case 3:
			cout << "\tEnter Item: ";
			cin >> item;
			AVLTree.SearchTree(item);
			system("PAUSE");
			system("cls");
			break;

		case 5:
			Exit();
			system("cls");
			break;
		default:
			cout << "\tThat is not a valid Menu Option!\n";
			system("PAUSE");
			system("cls");
		}
	} while (option != 6);
}

void ShowMenu()
{
	cout << "\t--AVL Tree--\n\n";
	cout << "\t1. Insert Item\n";
	cout << "\t2. Print Tree\n";
	cout << "\t3. Search Tree\n";
	cout << "\t5. Exit Application\n";
}

void Exit()
{
	system("cls");
	cout << "\t--AVL Tree--\n\n";
	cout << "\tThank you for using!\n";
	system("PAUSE");
	exit(0);
}


