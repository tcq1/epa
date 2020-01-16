/*
 * main.cpp
 *
 *  Created on: 17.01.2019
 *      Author: gocht
 */
#include "epa_graphs.hpp"
#include <vector>
#include <iostream>

struct Node {
	int key;
	std::vector<std::tuple<int, double>> neighbours;
};


struct Node* create_node(int key, std::vector<std::tuple<int, double>> neighbours) {
	struct Node *node = (struct Node *) malloc(sizeof(struct Node));
	node->key = key;
	node->neighbours = neighbours;

	return node;
}


std::vector<Node*> convert_node(const epa::graph::graph_t &graph, int n) {
	std::vector<Node*> nodes(n);

	for (const auto &line : graph) {
		int key = line.first;
		std::vector<std::tuple<int, double>> neighbours(n); 
		for (const auto &elem : line.second) {
			neighbours[key-1] = (std::make_tuple(std::get<0>(elem), std::get<1>(elem)));
		}

		if (nodes[key] != NULL) {
			nodes[key] = create_node(key, neighbours);
		}
	}

	return nodes;
}

void print_nodes(std::vector<Node*> nodes) {
	std::cout << "Printing nodes:\n";
	for (int i = 0; i < nodes.size(); i++) {
		std::cout << nodes[i]->key << ": (";
		for (int j = 0; j < nodes[i]->neighbours.size(); i++) {
			std::cout << std::get<0>(nodes[i]->neighbours[j]) << ", ";
			std::cout << std::get<1>(nodes[i]->neighbours[j]) << ")";
		}
		std::cout << "]\n";
	}
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

void get_min_span(epa::graph::graph_t &graph) {
	
	
	/**for(auto &line : graph) {
		line.second = find_min_dist(line.second);
	}*/
	print_graph(graph);
}

int main()
{
    std::cout << "gen_directed_graph" << std::endl;
    {
        auto graph = epa::graph::gen_directed_graph(5, 2);
        print_graph(graph);
	//std::cout << "\n\n";
	//get_min_span(graph);
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
