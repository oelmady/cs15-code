/*
 * BinarySearchTree.cpp
 * COMP15
 * Spring 2020
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include <cstring>
#include <iostream>
#include <limits>

#include "BinarySearchTree.h"

using namespace std;

// initializes a BST with root NULL
BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
}

// recursively deletes all nodes of the tree
BinarySearchTree::~BinarySearchTree()
{
	post_order_delete(root);
	root = nullptr; 
}

// recursively deletes all nodes in post order fashion
void BinarySearchTree::post_order_delete(Node *node)
{
	if (node == nullptr) return;

	if (node->left){
		post_order_delete(node->left);
	}
	if (node->right){
		post_order_delete(node->right);
	}
	delete node;
	node = nullptr;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
	root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source)
{
	if (&this->root == &source.root) return *this;
	this->post_order_delete(this->root);
	this->root = nullptr;
	this->root = this->pre_order_copy(source.root);
	return *this;
}

//recursively copies a tree from a given node in post order
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const
{
	if (node == nullptr) return nullptr;
	Node *copy  = new Node;
	copy->data  = node->data;
	copy->count = node->count;
	if (node->left){
		copy->left = pre_order_copy(node->left);
	}
	if (node->right){
		copy->right = pre_order_copy(node->right);
	}
	return copy;
}

// wrapper function
int BinarySearchTree::find_min() const
{
	if (root == nullptr)
		return numeric_limits<int>::max(); // INT_MAX

	return find_min(root)->data;
}
// recursive search starting from a non-nullptr root node
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const
{
	if (node->left == nullptr) return node;
	else return find_min(node->left);
}

// wrapper function
int BinarySearchTree::find_max() const
{
	if (root == nullptr) 
		return numeric_limits<int>::min(); 

	return find_max(root)->data;
}

// recursive search starting from a non-nullptr root node
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const
{
	if (node->right == nullptr) return node;
	else return find_max(node->right);
}

// wrapper function
bool BinarySearchTree::contains(int value) const
{
	if (root == nullptr) return false;
	
	return contains(root, value);
}

// O(logn) search 
bool BinarySearchTree::contains(Node *node, int value) const
{
	if (node == nullptr) return false;
	
	if (node->data == value) return true;
	else if (value < node->data){
		return contains(node->left, value);
	}
	else if (value > node->data){ 
		return contains(node->right, value);
	}
	else return false;
}

// wrapper
void BinarySearchTree::insert(int value)
{
	if (root == nullptr){
		root = createNode(value);
	}
	else insert(root, value);
}

//helper function creates new leaf nodes
BinarySearchTree::Node* BinarySearchTree::createNode(int value) {
	Node * leaf = new Node;
	leaf->data  = value;
	leaf->count = 1;
	leaf->left  = nullptr;
	leaf->right = nullptr;
	return leaf;
}

void BinarySearchTree::insert(Node *node, int value)
{
	if (node->data == value){
		node->count++;
	}
	else if (node->left == nullptr && node->data > value) { 
		node->left = createNode(value);
	}
	else if (node->right == nullptr && node->data < value) {
		node->right = createNode(value);
	}
	else if (node->data > value){
		insert(node->left, value);
	}
	else if (node->data < value){
		insert(node->right, value);
	}
}

bool BinarySearchTree::remove(int value)
{
	if (!contains(value)) return false;
	return remove(root, nullptr, value);
	//
	// return remove(root, &root, value);
}

// called on a value contained in the tree
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
	if (node->data == value) {
		node->count--;
		if (node->count == 0){
			if (node->left && node->right){
				Node * right_min = find_min(node->right);
				Node * right_parent = find_parent(node, right_min);
				node->data  = right_min->data;
				node->count = right_min->count;
				if (right_parent == node){
					node->right = right_min->right;
				} else {
					right_parent->left = right_min->right;
				}
				delete right_min;
			}
			else { // 1 child
				if (parent == nullptr){
					root = node->left ? node->left : node->right;
				} else {
					if (parent->data > node->data) {
						parent->left = node->left ? node->left : node->right;
					} else {
						parent->right = node->left ? node->left : node->right;
					}
				}
				delete node;
			}
		}
	}
	else if (node->data > value){
		return remove(node->left, node, value);
	} else if (node->data < value){
		return remove(node->right, node, value);
	}
	return true;
}

// bool BinarySearchTree::remove(Node *node, Node **ptr_to_ptr_to_me, int value)
// {
//         // TODO:  Students write code here
// }

// returns height from root
int BinarySearchTree::tree_height() const
{
	return tree_height(root) - 1;
}

int BinarySearchTree::tree_height(Node *node) const
{
	if (node == nullptr) return 0;
	int left  = tree_height(node->left);
	int right = tree_height(node->right);
	return 1 + max(left, right);
}

// returns the total number of nodes
int BinarySearchTree::node_count() const
{
	return node_count(root);
}

int BinarySearchTree::node_count(Node *node) const
{
	if (node == nullptr) return 0;
	return 1 + node_count(node->left) + node_count(node->right);
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
	return count_total(root);
}

int BinarySearchTree::count_total(Node *node) const
{
	if (node == nullptr) return 0;
	int count = node->data * node->count;
	count += count_total(node->left);
	count += count_total(node->right);
	return count;
}

BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
	if (node == nullptr)
		return nullptr;

	// if either the left or right is equal to the child,
	// we have found the parent
	if (node->left == child or node->right == child)
	{
		return node;
	}

	// Use the binary search tree invariant to walk the tree
	if (child->data > node->data)
	{
		return find_parent(node->right, child);
	}
	else
	{
		return find_parent(node->left, child);
	}
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
	size_t numLayers = tree_height() + 1;
	size_t levelWidth = 4;
	const char *rootPrefix = "-> ";

	// Need numLayers * levelWidth characters for each layer of tree.
	// Add an extra levelWidth characters at front to avoid if statement
	// 1 extra char for nul character at end
	char *start = new char[(numLayers + 1) * levelWidth + 1];

	print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
	delete[] start;
}

// Logic and Output Reference:
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
								  const char *const fullLine,
								  const char *const branch) const
{
	if (node == nullptr)
		return;

	// 4 characters + 1 for nul terminator
	using TreeLevel = char[5];
	static const int levelLength = sizeof(TreeLevel) - 1;
	static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
						   CONNECT = "   |";
	// Copies prev into dest and advances dest by strlen(prev)
	auto set = [](char *dest, const char *prev)
	{
		size_t p = strlen(prev);
		return (char *)memcpy(dest, prev, p) + p;
	};

	print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

	// Clear any characters that would immediate precede the "branch"
	// Don't need to check for root (i.e start of array),fullLine is padded
	set(currPos - levelLength, EMPTY);

	// Terminate fullLine at current level
	*currPos = '\0';

	std::cerr << fullLine << branch << node->data
			  << (node->count > 1 ? "*" : "") << endl;

	// Connect upper branch to parent
	if (branch == UP)
		set(currPos - levelLength, CONNECT);

	// Connect lower branch to parent
	print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}
