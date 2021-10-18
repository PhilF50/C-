#pragma once

//#include "AVLTrees1.cpp"
//Philip Fahey - K00217355


#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;


typedef enum { LH, EH, RH } Balfactor;



template <class ItemType>
struct TreeNode
{
	ItemType info;
	TreeNode* left;
	TreeNode* right;
	ItemType root;
	Balfactor bf;
};



template<class ItemType>
class TreeType
{
private:
	TreeNode<ItemType>* root;
	void Insert(TreeNode<ItemType>*& tree, ItemType item, bool& taller);
	void Print(TreeNode<ItemType>*& tree);
	void Search(TreeNode<ItemType>*& tree, ItemType item);
	void RightBalance(TreeNode<ItemType>*& tree, bool& taller);
	void LeftBalance(TreeNode<ItemType>*& tree, bool& taller);
	void RotateLeft(TreeNode<ItemType>*& tree);
	void RotateRight(TreeNode<ItemType>*& tree);
	void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);

public:
	TreeType(); 	// constructor
	~TreeType(); 	// destructor


	void InsertItem(ItemType item);
	void PrintTree();
	void SearchTree(ItemType item);

};


template <class ItemType>//constructor
TreeType<ItemType>::TreeType()
{
	root = NULL;   // Initialize root to NULL
};

template <class ItemType>//destructor
TreeType<ItemType>::~TreeType()
{
	
}

template <class ItemType>
void TreeType<ItemType> ::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller;
	Insert(root, item, taller);
}

template <class ItemType>
void TreeType<ItemType>::Insert(TreeNode<ItemType>*& tree, ItemType item, bool& taller)
// Inserts item into tree.
// Post:	item is in tree; search property is maintained.
{
	if (tree == NULL)
	{					// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->left = NULL;
		tree->right = NULL;
		tree->info = item;
		tree->bf = EH;
		taller = true;
	}
	else if (item == tree->info)
	{
		cout << "Duplicate key is not allowed in AVL tree." << endl;
	}
	else if (item < tree->info)
	{
		Insert(tree->left, item, taller);
		if (taller)
			switch (tree->bf)
			{
			case LH: LeftBalance(tree, taller);
				break;
			case EH: tree->bf = LH;
				break;
			case RH: tree->bf = EH; taller = false;
				break;
			}
	}
	else if (item > tree->info)
	{
		Insert(tree->right, item, taller);
		if (taller)
			switch (tree->bf)
			{
			case RH: RightBalance(tree, taller); break;
			case EH: tree->bf = RH; break;
			case LH: tree->bf = EH; taller = false; break;
			}
	}

}

template <class ItemType>
void TreeType<ItemType>::RightBalance(TreeNode<ItemType>*& tree, bool& taller)
{
	TreeNode<ItemType>* rs = tree->right;
	TreeNode<ItemType>* ls;

	switch (rs->bf)
	{
	case RH:	tree->bf = rs->bf = EH;
		RotateLeft(tree);
		taller = false;
		break;
	case EH:	cout << "Tree already balanced " << endl;
		break;
	case LH:	ls = rs->left;
		switch (ls->bf)
		{
		case RH:	tree->bf = LH;
			rs->bf = EH;		break;
		case EH:	tree->bf = rs->bf = EH;	break;
		case LH:	tree->bf = EH;
			rs->bf = RH;		break;
		}
		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}

template <class ItemType>
void TreeType<ItemType>::LeftBalance(TreeNode<ItemType>*& tree, bool& taller)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;

	switch (ls->bf)
	{
	case LH:	tree->bf = ls->bf = EH;
		RotateRight(tree);
		taller = false;
		break;
	case EH:	cout << "Tree already balanced " << endl;
		break;
	case RH:	rs = ls->right;
		switch (rs->bf)
		{
		case LH:	
			tree->bf = RH;
			ls->bf = EH;		
			break;
		case EH:	
			tree->bf = ls->bf = EH;	
			break;
		case RH:	tree->bf = EH;
			ls->bf = LH;		
			break;
		}
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}

template <class ItemType>
void TreeType<ItemType>::RotateLeft(TreeNode<ItemType>*& tree)
{
	TreeNode<ItemType>* rs;

	if (tree == NULL)
		cout << "Cannot rotate an empty tree in RotateLeft" << endl;
	else if (tree->right == NULL)
		cout << "Cannot make an empty subtree the root in RotateLeft" << endl;
	else
	{
		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}

template <class ItemType>
void TreeType<ItemType>::RotateRight(TreeNode<ItemType>*& tree)
{
	TreeNode<ItemType>* ls;

	if (tree == NULL)
		cout << "Cannot rotate an empty tree in RotateRight" << endl;
	else if (tree->left == NULL)
		cout << "Cannot make an empty subtree the root in RotateRight" << endl;
	else
	{
		ls = tree->left;
		tree->left = ls->right;
		ls->right = tree;
		tree = ls;
	}
}

template <class ItemType>
void TreeType<ItemType>::GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->left;
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	data = tree->info;
}



template <class ItemType>
void TreeType<ItemType> ::Print(TreeNode<ItemType>*& tree)
{
	if (tree == NULL)
		return;
	string bf, left, right;
	Print(tree->left);

	cout << "\t" << tree->info << ":";

	if (tree->left == NULL)
	{
		left = "NULL";
		cout << "\tLeft: " << left;
	}
	else
		cout << "\tLeft: " << tree->left->info << "  ";

	if (tree->right == NULL)
	{
		right = "NULL";
		cout << "\tRight: " << right;
	}
	else
		cout << "\tRight: " << tree->right->info << "  ";

	switch (tree->bf)
	{
	case 0: bf = "LH";
		break;
	case 1: bf = "EH";
		break;
	case 2: bf = "RH";
		break;
	}
	cout << "\tBF: " << bf << endl;

	Print(tree->right);
}

template <class ItemType>
void TreeType<ItemType> ::SearchTree(ItemType item)
{
	Search(root, item);
}

template <class ItemType>
void TreeType<ItemType> ::Search(TreeNode<ItemType>*& tree, ItemType item)
{
	
	if (tree == NULL) {
		cout << "\t" << item << " not present in Tree\n";
		return;
	}
	if (tree->info == item) {
		cout << "\t" << item << " is present in Tree\n";
			
	}
	if (tree->info > item) {
		Search(tree->left, item);
	}
	if (tree->info < item)
		Search(tree->right, item);
	else
		cout << "\t" << item << " not present in Tree\n";
	
		
		
	
}

template <class ItemType>
void TreeType<ItemType> ::PrintTree()
{
	Print(root);
}




