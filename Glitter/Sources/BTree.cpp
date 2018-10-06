#include "BTree.hpp"

BTree::BTree(){
	root = NULL;
}

BTree::~BTree(){
	destroy_tree();
}

void BTree::destroy_tree(Node *leaf){
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void BTree::insert(int key, Node *leaf){
	if (key < leaf->value) {
		if(leaf->left != NULL) {
			insert(key, leaf->left);
		} else {
			leaf->left = new Node;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}
    if (key >= leaf->value) {
		if(leaf->right != NULL){
			insert(key, leaf->right);
		} else {
			leaf->right = new Node;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}
	}
}

void BTree::insert(int key){
	if(root != NULL) {
		insert(key, root);
	} else {
		root = new Node;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

Node *BTree::search(int key, Node *leaf){
    if (leaf == NULL) {
        return NULL;
    }
	if(key == leaf->value){
		return leaf;
	}
	if(key < leaf->value){
		return search(key, leaf->left);
	} else {
		return search(key, leaf->right);
	}
}

Node *BTree::search(int key){
	return search(key, root);
}

void BTree::destroy_tree(){
	destroy_tree(root);
}

void BTree::inorder_print(){
	inorder_print(root);
	std::cout << "\n";
}

void BTree::inorder_print(Node *leaf){
	if (leaf != NULL) {
		inorder_print(leaf->left);
		std::cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

void BTree::postorder_print() {
	postorder_print(root);
	std::cout << "\n";
}

void BTree::postorder_print(Node *leaf) {
	if (leaf != NULL) {
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		std::cout << leaf->value << ",";
	}
}

void BTree::preorder_print(){
	preorder_print(root);
	std::cout << "\n";
}

void BTree::preorder_print(Node *leaf) {
    if (leaf != NULL) {
        std::cout << leaf->value << ",";
        inorder_print(leaf->left);
        inorder_print(leaf->right);
    }
}
/*
int main(){
	//BTree tree;
	BTree *tree = new BTree();

	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);

	tree->preorder_print();
	tree->inorder_print();
	tree->postorder_print();
	delete tree;
}
*/
