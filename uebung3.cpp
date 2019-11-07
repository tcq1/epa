#include <iostream>
#include <vector>

struct Node {
	int key;
	int value;
	std::vector<Node*> children;
};

struct Node* create_node(int key, int value, std::vector<Node*> children) {
	struct Node *node = (struct Node *) malloc(sizeof(struct Node));
	node->key = key;
	node->value = value;
	node->children = children;

	return node;
}

struct Node* init_nodes() {
	std::vector<Node*> children;
	struct Node *root = create_node(0, 42, children);

	return root;	
}

void get_node_details(struct Node* node) {
	std::cout << "Key: " << node->key << " | Value: " << node->value << "\n";
}

int main() {
	struct Node *root = init_nodes();
	get_node_details(root);

	return 0;
}
