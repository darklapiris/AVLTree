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
	void findRangeHelper(int lowkey, int highkey, vector<int>& toReturn, TreeNode* recurNode) {
		if (recurNode) {
			if (recurNode->keyInt > lowkey) findRangeHelper(lowkey, highkey, toReturn, recurNode->leftChild);
			if (recurNode->keyInt >= lowkey && recurNode->keyInt <= highkey) {
				toReturn.push_back(recurNode->keyInt);
				toReturn.push_back(recurNode->intMap[recurNode->keyInt]);
			}
			if (recurNode->keyInt < highkey) findRangeHelper(lowkey, highkey, toReturn, recurNode->rightChild);
		}
	}
	//inorder traversal of the tree with an indentation int
	void printHelper(TreeNode* recurNode, int indent) {
		if (recurNode) {
			string ind;
			for (int i = 0; i < indent; i++)
			{
				ind += "	";
			}
			printHelper(recurNode->rightChild, indent + 1);
			cout << ind << recurNode->keyInt << ", " << recurNode->intMap[recurNode->keyInt] << endl;
			printHelper(recurNode->leftChild, indent + 1);
		}
	}
	//moves around pointers for single left rotation(I may have mismatched the names, I didn't feel like checking lecture slides to get the names right)
	TreeNode* sLR(TreeNode* problemNode) {
		TreeNode* hookNode = problemNode->leftChild;
		TreeNode* toMove = hookNode->rightChild;

		if (rootNode == problemNode)rootNode = hookNode;

		hookNode->rightChild = problemNode;
		problemNode->leftChild = toMove;

		if (problemNode->leftChild) {
			problemNode->leftBalance = (problemNode->rightChild->leftBalance > problemNode->rightChild->rightBalance)
				? problemNode->rightChild->leftBalance : problemNode->rightChild->rightBalance;
			problemNode->leftBalance++;
		}
		else {
			problemNode->leftBalance = 0;
		}
		hookNode->rightBalance = (problemNode->leftBalance > problemNode->rightBalance) ? problemNode->leftBalance : problemNode->rightBalance;
		hookNode->rightBalance++;

		return hookNode;
	}
	//moves around pointers for single right rotation(I may have mismatched the names, I didn't feel like checking lecture slides to get the names right)
	TreeNode* sRR(TreeNode* problemNode) {
		TreeNode* hookNode = problemNode->rightChild;
		TreeNode* toMove = hookNode->leftChild;

		if (rootNode == problemNode)rootNode = hookNode;

		hookNode->leftChild = problemNode;
		problemNode->rightChild = toMove;

		if (problemNode->rightChild) {
			problemNode->rightBalance = (problemNode->rightChild->leftBalance > problemNode->rightChild->rightBalance)
				? problemNode->rightChild->leftBalance : problemNode->rightChild->rightBalance;
			problemNode->rightBalance++;
		}
		else {
			problemNode->rightBalance = 0;
		}
		hookNode->leftBalance = (problemNode->leftBalance > problemNode->rightBalance) ? problemNode->leftBalance : problemNode->rightBalance;
		hookNode->leftBalance++;

		return hookNode;
	}
	//recursion to count the nodes in the tree
	void getSizeHelper(int& toReturn, TreeNode* recurNode) {
		if (recurNode) {
			toReturn++;
			getSizeHelper(toReturn, recurNode->leftChild);
			getSizeHelper(toReturn, recurNode->rightChild);
		}
	}
	//returns the parent of childNode using recusion
	TreeNode* getParentHelper(TreeNode* recurNode, TreeNode* childNode) {
		if (recurNode->keyInt > childNode->keyInt) {
			if (recurNode->leftChild == childNode) return recurNode;
			else {
				return getParentHelper(recurNode->leftChild, childNode);
			}
		}
		if (recurNode->keyInt < childNode->keyInt) {
			if (recurNode->rightChild == childNode) return recurNode;
			else {
				return getParentHelper(recurNode->rightChild, childNode);
			}
		}
		else {
			return nullptr;
		}
	}
	bool insertHelper(int key, int value, TreeNode*& recurNode) {
		bool toReturn;
		TreeNode *currChild, *parentNode;
		int balance, rightChildBalance, leftChildBalance;

		if (key > recurNode->keyInt) {
			if (!recurNode->rightChild) {	//if no right child can just insert
				TreeNode* newNode = new TreeNode(key, value);
				recurNode->rightChild = newNode;
				toReturn = true;
			}

			else {
				toReturn = insertHelper(key, value, recurNode->rightChild); //if there is a right child call this function on it
			}
			currChild = recurNode->rightChild;
			recurNode->rightBalance = (currChild->leftBalance > currChild->rightBalance) ? currChild->leftBalance : currChild->rightBalance;
			recurNode->rightBalance++;
		}

		if (key < recurNode->keyInt) {	//same thing as previous if but now with left child
			if (!recurNode->leftChild) {		
				TreeNode* newNode = new TreeNode(key, value);
				recurNode->leftChild = newNode;
				toReturn = true;
			}

			else {
				toReturn = insertHelper(key, value, recurNode->leftChild);
			}
			currChild = recurNode->leftChild;
			recurNode->leftBalance = (currChild->leftBalance > currChild->rightBalance) ? currChild->leftBalance : currChild->rightBalance;
			recurNode->leftBalance++;
		}

		if (key == recurNode->keyInt) return false;	//can't have duplicate values

		balance = recurNode->leftBalance - recurNode->rightBalance;	//calculating balance of calling function and its children
		if (recurNode->rightChild) {
			rightChildBalance = recurNode->rightChild->leftBalance - recurNode->rightChild->rightBalance;
		}
		if (recurNode->leftChild) {
			leftChildBalance = recurNode->leftChild->leftBalance - recurNode->leftChild->rightBalance;
		}

		if (balance == -2) {	//if balance is off calls appropriate rotation
			if (rightChildBalance == 1) {	//when double rotation is needed call opposite rotate on what would be hook node
				recurNode->rightChild = sLR(recurNode->rightChild);
			}
			parentNode = getParent(recurNode);
			if (parentNode) {
				if (recurNode->keyInt > parentNode->keyInt) {
					parentNode->rightChild = sRR(recurNode);
				}
				else {
					parentNode->leftChild = sRR(recurNode);
				}
			}
			else {
				sRR(recurNode);
			}
		}

		if (balance == 2) {	//same as previous if statement but with opposite signed balance
			if (leftChildBalance == -1) {
				recurNode->leftChild = sRR(recurNode->leftChild);
			}
			parentNode = getParent(recurNode);
			if (parentNode) {
				if (recurNode->keyInt > parentNode->keyInt) {
					parentNode->rightChild = sLR(recurNode);
				}
				else {
					parentNode->leftChild = sLR(recurNode);
				}
			}
			else {
				sLR(recurNode);
			}
		}
		return toReturn;
	}
	bool findHelper(int key, int& value, TreeNode* recurNode)
	{
		if (recurNode == NULL)
		{	//the key doesn't exist in the tree
			return false;
		}
		if (recurNode->keyInt == key)
		{	//the key exists and value is set to the value corresponding in the map
			value = recurNode->intMap[key];
			return true;
		}
		if (key >= recurNode->keyInt) //recursive calls
		{
			return findHelper(key, value, recurNode->rightChild);
		}
		else
		{
			return findHelper(key, value, recurNode->leftChild);
		}
	}
public:
	int getSize() {
		int toReturn = 0;
		getSizeHelper(toReturn, rootNode);	//helper does pretty much everything
		return toReturn;
	}
	int getHeight() {
		return (rootNode->leftBalance > rootNode->rightBalance) ? rootNode->leftBalance : rootNode->rightBalance;
	}
	vector<int> findRange(int lowkey, int highkey) {
		vector<int> toReturn;
		findRangeHelper(lowkey, highkey, toReturn, rootNode); //make vector to eventually return and call helper function
		return toReturn;
	}
	void print() {
		printHelper(rootNode, 0); //call recursive print function
	}
	TreeNode* getParent(TreeNode* childNode) {
		return getParentHelper(rootNode, childNode);	//call helper function
	}

	bool insert(int key, int value) {
		if (!rootNode) {
			TreeNode* newNode = new TreeNode(key, value);	//if this is first thing inserted font need to call helper
			rootNode = newNode; 
			return true;
		}
		else {
			return insertHelper(key, value, rootNode); //if not call helper
		}
	}
	//logn find using recursive helper function
	bool find(int key, int& value) 
	{
		return findHelper(key, value, rootNode);
	}
	AVLTree();
	~AVLTree();
};