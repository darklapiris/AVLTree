#include "stdafx.h"
#include <map>
#include "AVLTree.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	AVLTree test;
	test.insert(3, 7);
	test.insert(5, 221);
	test.insert(6, 18);
	test.insert(10, 54);
	test.insert(40, 12);
	test.insert(20, 16);
	test.insert(30, 16);
	test.insert(40, 12);
	test.insert(45, 72);
	test.insert(43, 40);
	test.insert(50, 11);
	test.insert(55, 30);
	test.insert(44, 35);

	int theValue = 0;
	if (test.find(9, theValue)) {

		cout << theValue << endl;
	}
	else {
		cout << "not found!" << endl;
	}
	test.print();
	vector<int> testy = test.findRange(3, 7);
	for (int i = 0; i < testy.size(); i++) {
		cout << testy[i] << endl;
	}
	system("pause");
    return 0;
}

