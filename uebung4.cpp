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

void add_elem(struct Node *node, int elem) {
	for (int i = 0; i < node->data.size(); i++) {
		if (node->data[i] == -1) {
			node->data[i] = elem;
			break;		
		}
	}
	
	std::sort(node->data.begin(), node->data.end());
}

void push_elem_in_node(struct Node *node, int elem, int k) {
	if (!node_full(node)) {
		add_elem(node, elem);
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
	
		get_node_details(left);
		get_node_details(right);

		if (node->parent == NULL) {
			std::vector<Node*> children = {left, right};
			struct Node *parent = create_node(node->key, k, NULL);
			parent->children = children;
			add_elem(parent, move_up);
			get_node_details(parent);
		} else {
			push_elem_in_node(node->parent, move_up, k);
		}

		free(node);
	}
}

int main() {
	int k = 4;

	struct Node *root = create_node(50, k, NULL);
	push_elem_in_node(root, 2, k);
	push_elem_in_node(root, 1, k);
	push_elem_in_node(root, 4, k);
	push_elem_in_node(root, 3, k);
	push_elem_in_node(root, 5, k);

	return 0;
}
