#include <iostream>
#include <vector>
#include <bits/stdc++.h>

struct Node {
	int key;
	std::vector<int> data;
	std::vector<Node*> children;
	struct Node *parent;
};


struct Node* create_node(int key, int k, struct Node* parent) {
	struct Node *node = (struct Node *) malloc(sizeof(struct Node));
	node->key = key;
	node->parent = parent;

	std::vector<int> data(k);
	for (int i = 0; i < k; i++) {
		data[i] = -1;
	}
	node->data = data;
	node->children = std::vector<Node*>(k+1);

	return node;
}

void get_node_details(struct Node* node) {
	std::cout << "Key: " << node->key << "\n" << "Data: ";
	for (int i = 0; i < node->data.size(); i++) {
		std::cout << node->data[i] << " ";
	}
	std::cout << "\nChildren: ";
	for (int i = 0; i < node->children.size(); i++) {
		if (node->children[i] != NULL) {
			std::cout << node->children[i]->key << " ";
		} else {
			std::cout << "0 ";
		}
	}

	if (node->parent != NULL) {
		std::cout << "\nParent: " << node->parent->key;
	} else {
		std::cout <<"\nNode is root";
	}

	std::cout << "\n\n";
}

int node_full(struct Node *node) {
	for (int i = 0; i < node->data.size(); i++) {
		if (node->data[i] == -1) return 0;
	}	

	return 1;
}

int node_empty(struct Node *node) {
	for (int i = 0; i < node->data.size(); i++) {
		if (node->data[i] != -1) return 0;
	}

	return 1;
}

int node_is_leaf(struct Node *node) {
	for (int i = 0; i < node->children.size(); i++) {
		if (node->children[i] != NULL) return 0;
	}

	return 1;
}

void add_elem(struct Node *node, int elem) {
	for (int i = 0; i < node->data.size(); i++) {
		if (node->data[i] == -1) {
			node->data[i] = elem;
			break;		
		}
	}
	
	std::sort(node->data.begin(), node->data.end());
}

struct Node* get_root(struct Node *node) {
	if (node->parent == NULL) return node;
	return get_root(node->parent);
}

struct Node* push_elem_in_node(struct Node *node, int elem, int k) {
	struct Node *root;
	if (!node_full(node)) {
		add_elem(node, elem);
		root = get_root(node);
	} else {
		// Overflow
		node->data[node->data.size()] = elem;
		std::sort(node->data.begin(), node->data.end());
		
		int move_up = node->data[node->data.size()/2];
	
		struct Node *left = create_node(node->key - 1, k, NULL);
		struct Node *right = create_node(node->key + 1, k, NULL);

		for (int i = 0; i < node->data.size()/2; i++) {
			add_elem(left, node->data[i]); 
		}

		for (int i = node->data.size(); i > node->data.size()/2; i--) {
			add_elem(right, node->data[i]);
		}
	
		if (node->parent == NULL) {
			std::vector<Node*> children(k+1);
			children[k] = right;
			children[k-1] = left;
			struct Node *parent = create_node(node->key, k, NULL);
			parent->children = children;
			add_elem(parent, move_up);
		} else {
			push_elem_in_node(node->parent, move_up, k);
		}
		root = get_root(node);
		free(node);
	}

	return root;
}

struct Node* push_elem_in_tree(struct Node *node, int elem, int k) {
	struct Node* root;
	if (node_is_leaf(node)) {
		root = push_elem_in_node(node, elem, k);
	} else {
		for (int i = 0; i < node->data.size(); i++) {
			if (elem < node->data[i]) {
				root = push_elem_in_tree(node->children[i], elem, k);
				break;
			}	
		}

		if (elem >= node->data[node->data.size()]) {
			root = push_elem_in_tree(node->children[node->children.size()-1], elem, k);
		}
	}

	return root;
}

void display_tree(struct Node *node) {
	get_node_details(node);
	for (int i = 0; i < node->children.size(); i++) {
		if (node->children[i] != NULL) {
			display_tree(node->children[i]);
		}
	}
}

int main() {
	int k = 4;

	struct Node *root = create_node(50, k, NULL);
	
	for (int i = 1; i < 20; i++) {
		root = push_elem_in_tree(root, i, k);
	}
	
	display_tree(root);

	return 0;
}
