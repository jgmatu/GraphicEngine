#include <iostream>

struct Node {
	int value;
	Node *left;
	Node *right;
};

class BTree {

public:
	BTree();
	~BTree();

	void insert(int key);
	Node *search(int key);

	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();

private:

	void destroy_tree(Node *leaf);
	void insert(int key, Node *leaf);

    Node *search(int key, Node *leaf);

    void inorder_print(Node *leaf);
	void postorder_print(Node *leaf);
	void preorder_print(Node *leaf);

	Node *root;
};
