# AVLTree
AVLTree ADT class

TreeNodes contain a map<int, int>
The map has a key and a corresponding value.
The keys are what is used to traverse the BST, 
while the values are a mapped integer that corresponds
to the given key. 

Supported AVLTree functions:

int getSize() - returns an int of current number of nodes in the tree - 0(n)

int getHeight() - returns current height of the tree - 0(n)

vector<int> findRange(int lowkey, int highkey) - returns vector of all corresponding values 
that fall within the range of lowkey and highkey

void print() - prints a properly formatted version of the current tree - 0(n)

TreeNode* getParent(TreeNode* childNode) - returns a pointer to the parent of the given childNode

bool insert(int key, int value) creates a new TreeNode using the given key and value to map to it,
the BST will stay balanced through this process. Returns true if the node is successfully inserted, 
and will return false if the given key is already in the tree. (duplicate values are not allowed) - 0(logn)

bool find(int key, int& value) - looks for a treenode with the given key, and then sets the passed value
equal to the corresponding treenode mapped value. 0(logn)
