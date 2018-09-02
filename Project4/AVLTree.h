#pragma once
#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std; 

class TreeNode
{
public:
	map<int, int> intMap;
	int keyInt;
	TreeNode* leftChild;
	TreeNode* rightChild;
	int leftBalance;
	int rightBalance;
	TreeNode(int key, int value) 
	{
		keyInt = key;
		intMap[key] = value;
	}
};
class AVLTree
{
private:

	TreeNode* rootNode;
	//add things to vector if they are in the highkey and lowkey range (using recursion)
	void findRangeHelper(int lowkey, int highkey, vector<int>& toReturn, TreeNode* recurNode);

	//inorder traversal of the tree with an indentation int
	void printHelper(TreeNode* recurNode, int indent);

	//moves around pointers for single left rotation, when passed the appropriate problemNode
	TreeNode* sLR(TreeNode* problemNode);

	//moves around pointers for single right rotation, when passed the appropriate problemNode
	TreeNode* sRR(TreeNode* problemNode);

	//recursion to count the nodes in the tree
	void getSizeHelper(int& toReturn, TreeNode* recurNode);

	//returns the parent of childNode using recusion
	TreeNode* getParentHelper(TreeNode* recurNode, TreeNode* childNode);

	bool insertHelper(int key, int value, TreeNode*& recurNode);

	bool findHelper(int key, int& value, TreeNode* recurNode);

public:

	int getSize();

	int getHeight();

	//returns vector of all values within lowkey and highkey
	vector<int> findRange(int lowkey, int highkey);

	//prints entire tree recursively, move this to an ostream eventually
	void print();

	//returns parentNode of the childNode passed to the function
	TreeNode* getParent(TreeNode* childNode);

	bool insert(int key, int value);

	//logn find using recursive helper function
	bool find(int key, int& value);
	AVLTree();
	~AVLTree();
};