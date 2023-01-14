#pragma once
/**
	Description :
	Templated Binary Search Tree Class
**/

#include<iostream>

template <class KeyType, class ValueType>
struct TreeNode {
	KeyType key;
	ValueType value;
	TreeNode <KeyType, ValueType>* parent = nullptr;
	TreeNode <KeyType, ValueType>* right = nullptr;
	TreeNode <KeyType, ValueType>* left = nullptr;
};

template <class KeyType, class ValueType>
class BinarySearchTree
{
public:
	// recursive helper for destrutor to delete nodes
	void destroy(TreeNode <KeyType, ValueType>*& root);
	~BinarySearchTree() { destroy(root); }

	void remove(KeyType key, ValueType value) { removeHelper(root, key, value); }

	int height() { return bstHeight(root); }
	int bstHeight(TreeNode<KeyType, ValueType>*& node);
	TreeNode<KeyType, ValueType>* inorderPredecessor(TreeNode<KeyType, ValueType>*& node);
	TreeNode<KeyType, ValueType>* inorderSuccessor(TreeNode<KeyType, ValueType>*& node);
	void insert(KeyType key, ValueType value) { iterativeInsertHelper(root, key, value); }
	TreeNode<KeyType, ValueType>* parentFinder(TreeNode <KeyType, ValueType>*& node, KeyType key, ValueType value);
	// returns the min (left-most leaf)
	KeyType minKey();
	// returns the max (right-most leaf)
	KeyType maxKey();
	int returnCount() { return count; }
	// recursive or iterative key search
	bool search(KeyType key) { return searchHelper(root, key); }
	void printInorder() { inorder(root); }
	void printPostorder() { postorder(root); }
	void printPreorder() { preorder(root); }
private:
	// recursive inorder traversal
	void inorder(TreeNode<KeyType, ValueType>* n);
	// recursive postorder traversal
	void postorder(TreeNode<KeyType, ValueType>* n);
	// recursive preorder traversal
	void preorder(TreeNode<KeyType, ValueType>* n);
	// recursive insert helper function
	void recursiveInsertHelper(TreeNode <KeyType, ValueType>*& node, KeyType key, ValueType value);
	// iterative insert helper function
	void iterativeInsertHelper(TreeNode <KeyType, ValueType>*& root, KeyType key, ValueType value);
	// search helper
	bool searchHelper(TreeNode<KeyType, ValueType>*& node, KeyType key);
	// remove helper
	TreeNode<KeyType, ValueType>* removeHelper(TreeNode<KeyType, ValueType>*& node, KeyType key, ValueType value);

	TreeNode<KeyType, ValueType>* root = nullptr; // trees root
	int count = 0; // node count
};

template <class KeyType, class ValueType>
void BinarySearchTree<KeyType, ValueType>::recursiveInsertHelper(TreeNode<KeyType, ValueType>*& node, KeyType key, ValueType value)
{
	TreeNode<KeyType, ValueType>* new_node = nullptr;
	if (!root) // create root node 
	{
		new_node = new TreeNode<KeyType, ValueType>;
		new_node->key = key;
		new_node->value = value;
		root = new_node;
		count++;
	}
	else if (!node) // create non-root node
	{
		new_node = new TreeNode<KeyType, ValueType>;
		new_node->key = key;
		new_node->value = value;
		new_node->parent = parentFinder(root, key, value); // identify parent, then assign
		if (key < new_node->parent->key)
			new_node->parent->left = new_node; // assign as left child of parent
		if (key > new_node->parent->key)
			new_node->parent->right = new_node; // assign as right child of parent
		count++;
	}
	// find insertion location
	else if (key < node->key)
		recursiveInsertHelper(node->left, key, value);
	else if (key > node->key)
		recursiveInsertHelper(node->right, key, value);
}

template <class KeyType, class ValueType>
void BinarySearchTree<KeyType, ValueType>::iterativeInsertHelper(TreeNode<KeyType, ValueType>*& root, KeyType key, ValueType value)
{
	TreeNode<KeyType, ValueType>* temp = root;
	TreeNode<KeyType, ValueType>* trailing_ptr = nullptr;
	TreeNode<KeyType, ValueType>* new_node = nullptr;

	if (!root) // create root node
	{
		new_node = new TreeNode<KeyType, ValueType>;
		new_node->key = key;
		new_node->value = value;
		root = new_node;
		count++;
		return;
	}
	// else, find location to insert
	while (temp != nullptr)
	{
		trailing_ptr = temp;
		if (key < temp->key)
			temp = temp->left; // move left
		else if (key > temp->key)
			temp = temp->right; // move right
		else // key is found
			return;
	}
	// create new node
	new_node = new TreeNode<KeyType, ValueType>;
	new_node->key = key;
	new_node->value = value;
	new_node->left = new_node->right = nullptr;
	count++;

	//link new_node
	if (key < trailing_ptr->key) {
		trailing_ptr->left = new_node;
		new_node->parent = trailing_ptr;
	}
	else {
		trailing_ptr->right = new_node;
		new_node->parent = trailing_ptr;
	}

}

template <class KeyType, class ValueType>
void BinarySearchTree<KeyType, ValueType>::inorder(TreeNode<KeyType, ValueType>* n)
{
	if (n)
	{
		inorder(n->left);
		std::cout << "Key : " << n->key << " Value : " << n->value << "\n";
		inorder(n->right);
	}
}

template <class KeyType, class ValueType>
void BinarySearchTree<KeyType, ValueType>::postorder(TreeNode<KeyType, ValueType>* n)
{
	if (n)
	{
		postorder(n->left);
		postorder(n->right);
		std::cout << "Key : " << n->key << " Value : " << n->value << "\n";
	}
}

template <class KeyType, class ValueType>
void BinarySearchTree<KeyType, ValueType>::preorder(TreeNode<KeyType, ValueType>* n)
{
	if (n)
	{
		std::cout << "Key : " << n->key << " Value : " << n->value << "\n";
		preorder(n->left);
		preorder(n->right);
	}
}

template <class KeyType, class ValueType>
TreeNode<KeyType, ValueType>* BinarySearchTree<KeyType, ValueType>::parentFinder(TreeNode<KeyType, ValueType>*& node, KeyType key, ValueType value)
{
	while (key < node->key)
	{
		if (node->left == nullptr)
			return node;
		return parentFinder(node->left, key, value);
	}
	while (key > node->key)
	{
		if (node->right == nullptr)
			return node;
		return parentFinder(node->right, key, value);
	}
	return nullptr;
}

template <class KeyType, class ValueType>
KeyType BinarySearchTree<KeyType, ValueType>::minKey()
{
	TreeNode<KeyType, ValueType>* traverse_ptr = root;
	KeyType minimum_key = traverse_ptr->key;
	while (traverse_ptr)
	{
		traverse_ptr = traverse_ptr->left;
		if (traverse_ptr) {
			minimum_key = traverse_ptr->key;
		}
	}
	return minimum_key;
}

template <class KeyType, class ValueType>
KeyType BinarySearchTree<KeyType, ValueType>::maxKey()
{
	TreeNode<KeyType, ValueType>* traverse_ptr = root;
	KeyType maximum_key = traverse_ptr->key;
	while (traverse_ptr)
	{
		traverse_ptr = traverse_ptr->right;
		if (traverse_ptr) {
			maximum_key = traverse_ptr->key;
		}
	}
	return maximum_key;
}

template <class KeyType, class ValueType>
void BinarySearchTree<KeyType, ValueType>::destroy(TreeNode <KeyType, ValueType>*& node)
{
	if (node)
	{
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

template <class KeyType, class ValueType>
TreeNode<KeyType, ValueType>* BinarySearchTree<KeyType, ValueType>::inorderPredecessor(TreeNode<KeyType, ValueType>*& node)
{
	while (node && node->right != nullptr)
		node = node->right;

	return node;
}

template <class KeyType, class ValueType>
TreeNode<KeyType, ValueType>* BinarySearchTree<KeyType, ValueType>::inorderSuccessor(TreeNode<KeyType, ValueType>*& node)
{
	TreeNode<KeyType, ValueType>* temp = node;
	while (temp && temp->left != nullptr)
		temp = temp->left;

	return temp;
}


template <class KeyType, class ValueType>
int BinarySearchTree<KeyType, ValueType>::bstHeight(TreeNode<KeyType, ValueType>*& node)
{
	int x = 0, y = 0;
	if (node == 0)
		return -1;
	x = bstHeight(node->left);
	y = bstHeight(node->right);
	if (x > y)
		return x + 1;
	else
		return y + 1;

}

template <class KeyType, class ValueType>
bool BinarySearchTree<KeyType, ValueType>::searchHelper(TreeNode<KeyType, ValueType>*& node, KeyType key)
{
	if (node == nullptr)
		return false;
	if (key == node->key)
		return true;
	else if (key < node->key)
		return searchHelper(node->left, key);
	else
		return searchHelper(node->right, key);
}

template <class KeyType, class ValueType>
TreeNode<KeyType, ValueType>* BinarySearchTree<KeyType, ValueType>::removeHelper(TreeNode<KeyType, ValueType>*& node, KeyType key, ValueType value)
{
	TreeNode<KeyType, ValueType>* temp;
	if (node == nullptr)
		return nullptr;
	// delete node
	if (node->left == nullptr && node->right == nullptr) // if leaf node
	{
		if (node == root)
			root = nullptr;
		delete node;
		count--;
		return nullptr;
	}
	// search for key
	if (key < node->key)
		node->left = removeHelper(node->left, key, value);
	else if (key > node->key)
		node->right = removeHelper(node->right, key, value);
	// remove element from left or right subtree depending on height
	else
	{
		if (bstHeight(node->left) > bstHeight(node->right))
		{
			temp = inorderPredecessor(node->left);
			node->key = temp->key; node->value = temp->value;
			node->left = removeHelper(node->left, temp->key, temp->value);
		}
		else
		{
			temp = inorderSuccessor(node->right);
			node->key = temp->key; node->value = temp->value;
			node->right = removeHelper(node->right, temp->key, temp->value);
		}
	}
	return node;
}
