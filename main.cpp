/*
 * main.cpp
 *
 *  Created on: 17.01.2019
 *      Author: gocht
 */
#include "epa_graphs.hpp"
#include <vector>
#include <iostream>
#include <tuple>

struct Node {
	int key;
	int visited;
	std::vector<std::tuple<int, double>> neighbours;
};


struct Node* create_node(int key, std::vector<std::tuple<int, double>> neighbours) {
	struct Node *node = (struct Node *) malloc(sizeof(struct Node));
	node->key = key;
	node->visited = 0;
	node->neighbours = neighbours;

	return node;
}


void print_nodes(std::vector<Node*> nodes) {
	std::cout << "Printing nodes:\n";
	for (int i = 0; i < nodes.size(); i++) {	
		std::cout << nodes[i]->key << ": [";
		for (int j = 0; j < nodes[i]->neighbours.size(); j++) {
			std::cout << "(" << std::get<0>(nodes[i]->neighbours[j]) << ", ";
			std::cout << std::get<1>(nodes[i]->neighbours[j]) << ")";
		}
		std::cout << "]\n";
	}
	std::cout << "\n\n";
}

std::vector<Node*> convert(const epa::graph::graph_t &graph, int n, int b) {
	std::vector<Node*> nodes(n);

	for (const auto &line : graph) {
		int key = line.first;
		std::vector<std::tuple<int, double>> neighbours(b);
		int i = 0;
		for (const auto &elem : line.second) {
			neighbours[i] = std::make_tuple(std::get<0>(elem), std::get<1>(elem));
			i++;
		}

		nodes[key] = create_node(key, neighbours);
	}

	return nodes;
}


void print_graph(const epa::graph::graph_t &graph)
{
    for (const auto &line : graph)
    {
        std::cout << line.first << ": [";
        for (const auto &elem : line.second)
        {
            std::cout << "(" << std::get<0>(elem) << ", " << std::get<1>(elem) << ")";
        }
        std::cout << "]" << std::endl;
    }
}

std::vector<std::tuple<int, double>> find_min_dist(std::vector<std::tuple<int, double>> neighbours) {
	std::tuple<int, double> min = neighbours[0];
	for (int i = 1; i < neighbours.size(); i++) {
		if (std::get<1>(neighbours[i]) < std::get<1>(min)) {
			min = neighbours[i];
		}
	}

	std::vector<std::tuple<int, double>> min_dist(1);
	min_dist[0] = min;

	return min_dist;
}

struct Node* set_new_neighbours(struct Node* node) {
	node->neighbours = find_min_dist(node->neighbours);
	
	return node;
}

std::tuple<int, double> closest_neighbour(struct Node* node) {
	auto min = node->neighbours[0];

	for (int i = 1; i < node->neighbours.size(); i++) {
		if (std::get<1>(node->neighbours[i]) < std::get<1>(min)) {
			min = node->neighbours[i];
		}
	}

	return min;
}

struct Node* find_next_node(std::vector<Node*> nodes) {
	return NULL;
}

void get_min_span(std::vector<Node*> nodes, int start) {
	std::vector<Node*> min_span(nodes.size());
	
	min_span[start] = nodes[start];
	min_span[start] = set_new_neighbours(min_span[start]);
	
	

	/*for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->neighbours = find_min_dist(nodes[i]->neighbours);
	}*/
}

int main()
{
    int n = 10;
    int b = 2;
    std::cout << "gen_directed_graph" << std::endl;
    {
        auto graph = epa::graph::gen_directed_graph(n, b);
        print_graph(graph);
	std::cout << "\n\n";
	std::vector<Node*> nodes = convert(graph, n, b);
	print_nodes(nodes);
	get_min_span(nodes, 0);
    }
    /**
    std::cout << "gen_directed_graph_rand" << std::endl;
    {
        auto graph = epa::graph::gen_directed_graph_rand(10, 2);
        print_graph(graph);
    }
    std::cout << "gen_undirected_graph" << std::endl;
    {
        auto graph = epa::graph::gen_undirected_graph(10, 2);
        print_graph(graph);
    }
    std::cout << "gen_undirected_graph_rand" << std::endl;
    {
        auto graph = epa::graph::gen_undirected_graph_rand(10, 2);
        print_graph(graph);
    }*/
    std::cout << "Bye Bye" << std::endl;
}
