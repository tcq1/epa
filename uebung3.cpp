#include <iostream>
#include <vector>
#include <chrono>

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

struct Node* init_nodes(int n) {
	std::vector<Node*> nochildren;
	struct Node *nodes[n-1];
	for (int i = 0; i < n-1; i++) {
		nodes[i] = create_node(i+1, rand()%1000, nochildren);
	}
	
	std::vector<Node*> children(n-1);
	for (int i = 0; i < n-1; i++) {
		//children.push_back(nodes[i]);
		children[i] = nodes[i];
	}
	
	struct Node *root = create_node(0, 42, children);

	/*
	// Root has 1 and 2 as children
	std::vector<Node*> rootchildren {nodes[0], nodes[1]};
	struct Node *root = create_node(0, 42, rootchildren);

	// 1 has 3 and 4 as children	
	std::vector<Node*> clist1 {nodes[2], nodes[3]};
	nodes[0]->children = clist1;

	// 2 has 5 and 6 as children	
	std::vector<Node*> clist2 {nodes[4], nodes[5]};
	nodes[1]->children = clist2;

	// 3 has 7 as child	
	std::vector<Node*> clist3 {nodes[6]};
	nodes[2]->children = clist3;

	// 4 has 8 as child	
	std::vector<Node*> clist4 {nodes[7]};
	nodes[3]->children = clist4;

	// 5 has 9 as child
	std::vector<Node*> clist5 {nodes[8]};
	nodes[4]->children = clist5;
	*/

	return root;	
}

void init_tree_vect(int n) {
	std::vector<Node*> nochildren;
	std::vector<Node*> rootchildren;
	struct Node *root = create_node(0, 42, rootchildren);
	
	int current_index = 1;
	
	while (n > 0) {
		
	}
}

void get_node_details(struct Node* node) {
	std::cout << "Key: " << node->key << " | Value: " << node->value << "\n";
	if (node->children.size() > 0) {
		std::cout << "Children of " << node->key << ": " << node->children[0]->key;
		for (int i = 1; i < node->children.size(); ++i) {
			std::cout << " | " << node->children[i]->key;
		}
	} else { 
		std::cout << node->key << " has no children!";
	}

	std::cout << "\n \n";
}

void traverse(struct Node* node) {
	//DFS traversation
	
	get_node_details(node);
	for (int i = 0; i < node->children.size(); ++i) {
		traverse(node->children[i]);
	}
}

int get_sum(struct Node* node) {
	int sum = 0;
	for (int i = 0; i < node->children.size(); ++i) {
		sum = sum + get_sum(node->children[i]);
	}

	return node->value + sum;
}

void benchmark_tree(int size) {
        using namespace std::chrono;

	std::cout << "Tree size " << size << ": \n"; 
	struct Node *root = init_nodes(size);
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
 
	std::cout << "Sum of all values of the tree is : " << get_sum(root) << "\n";

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

        std::cout << "Calculation took " << time_span.count() << " seconds.\n \n";
}

int main() {
	benchmark_tree(10);
	benchmark_tree(100);
	benchmark_tree(1000);
	benchmark_tree(10000);

	return 0;
}
