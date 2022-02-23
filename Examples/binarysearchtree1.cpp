#include <iostream>
#include <limits>
#include <queue>
#include <algorithm> // for max
using namespace std;

struct Node {
	Node *parent, *left, *right;
	int level, data;

	Node(int level, int data) :
		parent{nullptr}, left{nullptr}, right{nullptr},
		level{level}, data(data) { }

	Node(Node *parent, int level, int data) :
		parent{parent}, left{nullptr}, right{nullptr},
		level{level}, data{data} { }
};

// O(tree height) (and the tree height is O(n))
Node* insert_helper(Node **proot, int x, Node *parent, int level) {
	if(*proot == nullptr) {
		return *proot = new Node(parent, level, x);
	}
	if((*proot)->data == x) {
		return nullptr;
	}
	if(x < (*proot)->data) {
		return insert_helper(&(*proot)->left, x, *proot, level + 1);
	} else {
		return insert_helper(&(*proot)->right, x, *proot, level + 1);
	}
}

Node* insert(Node **proot, int x) {
	return insert_helper(proot, x, nullptr, 0);
}

// Θ(n)
void display_sideways(Node *node) {
	if(node != nullptr) {
		display_sideways(node->right);
		if(node->level == 0) {
			cout << "-> ";
		} else {
			cout << "   ";
		}
		for(int i = 0; i < node->level; ++i) {
			cout << "   ";
		}
		cout << node->data << endl;
		display_sideways(node->left);
	}
}

// O(tree height) (and the tree height is O(n))
Node* find(Node *root, int x) {
	if(root == nullptr) {
		return nullptr;
	}
	if(root->data == x) {
		return root;
	}
	if(x < root->data) {
		return find(root->left, x);
	} else {
		return find(root->right, x);
	}
}

// Sum all integers in the BST
int sum(Node *root) {
	if(root == nullptr) {
		return 0;
	} else {
		return root->data + sum(root->left) + sum(root->right);
	}
}

// Θ(n)
void decrement_levels(Node *root) {
	if(root) {
		root->level--;
		decrement_levels(root->left);
		decrement_levels(root->right);
	}
}

// Deletes and returns as result the minimum node in the non-empty tree.
// Since the tree is non-empty, such minimum node must exist.
// This code is similar to findMin except that we do not have to test
// the Null case since we know that the tree is non-empty.
// O(tree height) (and the tree height is O(n))
Node *delete_min(Node **proot) {
	if((*proot)->left == nullptr) {
		// root is the minimum node, remove it from the tree and return it
		Node *min = *proot;
		decrement_levels((*proot)->right);
		*proot = (*proot)->right;
		return min;
	} else {
		// Keep moving down-left
		return delete_min(&(*proot)->left);
	}
}

// O(tree height) (and the tree height is O(n))
bool delete_node(Node **proot, int x){
	if(*proot == nullptr) {
		// Cannot find x, deletion fails
		return false;
	}
	if((*proot)->data == x) {
		// Case 1: the node is a leaf
		// Note: this case is in fact a special case of the next one (case 2-a
		// or case 2-b) so this code could be merged with the next case.
		// We keep this case separate here for clarity.
		if((*proot)->left == nullptr && (*proot)->right == nullptr) {
			delete *proot;
			*proot = nullptr;
			return true;
		}
		// Case 2-a: the node has one left child
		if((*proot)->left != nullptr && (*proot)->right == nullptr) {
			Node *tmp = *proot;
			decrement_levels((*proot)->left);
			*proot = (*proot)->left;
			delete tmp;
			return true;
		}
		// Case 2-b: the node has one right child
		if((*proot)->left == nullptr && (*proot)->right != nullptr) {
			Node *tmp = *proot;
			decrement_levels((*proot)->right);
			*proot = (*proot)->right;
			delete tmp;
			return true;
		}
		// Case 3: the node has two children
		// We replace the root with the minimum node in the right subtree
		// (The maximum node in the left subtree would work too.)
		if((*proot)->left != nullptr && (*proot)->right != nullptr) {
			Node *tmp = *proot;
			// Find the smallest node in the right subtree:
			Node *min = delete_min(&(*proot)->right);
			// Replace the root with the min:
			min->parent = (*proot)->parent;
			min->level = (*proot)->level;
			min->left = (*proot)->left;
			min->right = (*proot)->right;
			*proot = min;
			delete tmp;
			return true;
		}
	}
	if((*proot)->data > x) {
		return delete_node(&(*proot)->left, x);
	} else {
		return delete_node(&(*proot)->right, x);
	}
}

// Θ(n)
void delete_bst(Node *root) {
	if(root != nullptr) {
		delete_bst(root->left);
		delete_bst(root->right);
		delete root;
	}
}

// Create a balanced BST from a sorted array.
// Θ(n)
Node* create_bst_helper(int data[], int low, int high, Node *parent, int level) {
	if(low > high) {
		return nullptr;
	}
	int mid = low + (high - low) / 2;
	Node *new_node = new Node(parent, level, data[mid]);
	new_node->left = create_bst_helper(data, low, mid - 1, new_node, level + 1);
	new_node->right = create_bst_helper(data, mid + 1, high, new_node, level + 1);
	return new_node;
}

Node* create_bst(int data[], int length) {
	return create_bst_helper(data, 0, length - 1, nullptr, 0);
}

bool is_bst_helper(Node* p, int min, int max){
	if(p == nullptr){
		return true;
	}
	if(p->data <min || p->data > max){
		return false;
	}
	return is_bst_helper(p->left, min, p->data);
	return is_bst_helper(p->right, p->data, max);
}

bool is_bst(Node* p){
	return is_bst_helper(p, std::numeric_limits<int>::min(), std::numeric_limits<int>::max())
}

Node* lowest_common_ancestor(Node* p, Node* q){
	if(p == nullptr || q == nullptr){
		return nullptr;
	}
	if(p==q){
		return p;
	}
	if(p->level < q->level){
		return lowest_common_ancestor(p, q->parent);
	}
	if(p->level > q->level){
		return lowest_common_ancestor(p->parent, q);
	}
	return lowest_common_ancestor(p->parent, q->parent);
	
}

int max_width(Node *root){
	if(root == nullptr){
		return 0;
	}
	queue<Node*> q;
	q.push(root)
	int max_width = 0;

	while(!q.empty()){
		int width = q.size();
		max_width = max(max_width, width);

		for(int i = 0; i<width, i++){
			Node *current = q.front();
			q.pop()
			if(current->left != nullptr){
				q.push(current->left);
			}
			if(current->right != nullptr){
				q.push(current->right);
			}
		}
	}
	return max_width;
}

Node* find_min(Node *root){
	if(root == nullptr){
		return nullptr;
	}
	if(root->left == nullptr){
		return root;
	}else{
		return find_min(root->left);
	}

}


Node* successor(Node *node){
	if(node == nullptr){
		return nullptr;
	}
	if(node->right != nullptr){
		return find_min(node->right);
	}else{
		Node *parent = node->parent;
		while(parent->data < node->data && parent != nullptr){
			node = parent;
			parent = node->parent;
		}
		return parent;
	}
}

int main(int argc, const char *argv[]) {
	Node *bst1 = nullptr;
	insert(&bst1, 3);
	insert(&bst1, 5);
	insert(&bst1, 2);
	display_sideways(bst1);
	cout << endl;
	cout << "finding " << find(bst1, 5)->data << endl;
	cout << "sum is " << sum(bst1) << endl;
	cout << "deleting 3:" << endl << endl;
	delete_node(&bst1, 3);
	display_sideways(bst1);
	cout << endl;
	cout << "deleting 5:" << endl << endl;
	delete_node(&bst1, 5);
	display_sideways(bst1);
	cout << endl;
	delete_bst(bst1);
	bst1 = nullptr;

	int data[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	Node *bst2 = create_bst(data, 15);
	display_sideways(bst2);

	delete_bst(bst2);
	return 0;
}
