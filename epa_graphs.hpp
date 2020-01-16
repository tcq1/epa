/*
 * epa_graphs.hpp
 *
 *  Created on: 17.01.2019
 *      Author: gocht
 */

#ifndef GRAPHEN_EPA_GRAPHS_HPP_
#define GRAPHEN_EPA_GRAPHS_HPP_

#include <algorithm>
#include <iostream>
#include <random>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace epa
{
namespace graph
{

using graph_t = std::unordered_map<int, std::vector<std::tuple<int, double>>>;

/*  choose `edges` nodes from `target_nodes`, whitout `chossen` and doubled nodes
 *  Function is side effect free
 *
 *  @param choosen list of already chossen elements
 *  @param list to choose elements from
 *  @param edges amount of edged
 *  @return nodes to pick
 */
inline std::unordered_set<int> choose_nodes(
    const std::unordered_set<int> &choosen, const std::unordered_set<int> &target_nodes, std::size_t edges)
{
    auto tmp_target_nodes = target_nodes;
    for (const auto &elem : choosen)
    {
        tmp_target_nodes.erase(elem);
    }

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::unordered_set<int> result;

    std::sample(tmp_target_nodes.begin(), tmp_target_nodes.end(), std::inserter(result, result.begin()), edges, gen);

    return result;
}

/**generates a dicrected graph with `nodes` nodes and `edge_factor` edges per node
 *
 * @param nodes amount of nodes
 * @param edge_factor edges per node
 * @param cost expects a tuple with (mu,sigma) for the normal distribution which generates the cost
 * @retrun graph_t in the form graph_t[node] = [(node_1, cost), (node_2, cost), (node_3, cost)]
 */
inline graph_t gen_directed_graph(
    std::size_t nodes = 1000, size_t edge_factor = 2, double cost_mu = 1, double cost_sig = 1)
{
    graph_t graph;
    std::unordered_set<int> node_list;
    int i = 0;
    std::generate_n(std::inserter(node_list, node_list.begin()), nodes, [&i]() { return i++; });

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> costs{cost_mu, cost_sig};

    for (const auto &node_1 : node_list)
    {
        graph[node_1] = std::vector<std::tuple<int, double>>();
        auto connect_nodes = choose_nodes(std::unordered_set<int>({node_1}), node_list, edge_factor);
        for (const auto &node_2 : connect_nodes)
        {
            auto cost = std::abs(costs(gen));
            graph[node_1].push_back(std::make_tuple(node_2, cost));
        }
    }

    return graph;
}

/** generates a dicrected graph with `nodes` nodes and up to `edge_factor` edges per node
 *
 * @param nodes amount of nodes
 * @param edge_factor up to `edge_factor` edges per node
 * @param cost expects a tuple with (mu,sigma) for the normal distribution which generates the cost
 * @retrun graph_t in the form graph_t[node] = [(node_1, cost), (node_2, cost), (node_3, cost)]
 */
inline graph_t gen_directed_graph_rand(
    std::size_t nodes = 1000, size_t edge_factor = 2, double cost_mu = 1, double cost_sig = 1)
{
    graph_t graph;
    std::unordered_set<int> node_list;
    int i = 0;
    std::generate_n(std::inserter(node_list, node_list.begin()), nodes, [&i]() { return i++; });

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> costs{cost_mu, cost_sig};
    std::uniform_int_distribution<> edges{1, static_cast<int>(edge_factor)};

    for (const auto &node_1 : node_list)
    {
        graph[node_1] = std::vector<std::tuple<int, double>>();
        auto connect_nodes = choose_nodes(std::unordered_set<int>({node_1}), node_list, edges(gen));
        for (const auto &node_2 : connect_nodes)
        {
            auto cost = std::abs(costs(gen));
            graph[node_1].push_back(std::make_tuple(node_2, cost));
        }
    }

    return graph;
}

/**generates an undicrected graph with `nodes` nodes and around `edge_factor` edges per node
 *
 * @param nodes amount of nodes
 * @param edge_factor approximate edges per node, might happen that some nodes have more edges
 * @param cost expects a tuple with (mu,sigma) for the normal distribution which generates the cost
 * @retrun graph_t in the form graph_t[node] = [(node_1, cost), (node_2, cost), (node_3, cost)]
 */

inline graph_t gen_undirected_graph(
    std::size_t nodes = 1000, size_t edge_factor = 2, double cost_mu = 1, double cost_sig = 1)
{
    graph_t graph;
    std::vector<int> node_list;
    std::unordered_set<int> node_list_set;
    int i = 0;
    std::generate_n(std::inserter(node_list, node_list.begin()), nodes, [&i]() { return i++; });
    std::copy(node_list.begin(), node_list.end(), std::inserter(node_list_set, node_list_set.begin()));

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> costs{cost_mu, cost_sig};

    for (const auto &node_1 : node_list)
    {
        int edges = edge_factor - graph[node_1].size();
        if (edges <= 0)
        {
            continue;
        }

        std::unordered_set<int> choosen_nodes;
        std::transform(graph[node_1].begin(),
            graph[node_1].end(),
            std::inserter(choosen_nodes, choosen_nodes.begin()),
            [](std::tuple<int, double> val) -> int { return std::get<0>(val); });
        choosen_nodes.insert(node_1);

        auto connect_nodes = choose_nodes(choosen_nodes, node_list_set, edges);
        for (const auto &node_2 : connect_nodes)
        {
            auto cost = std::abs(costs(gen));
            graph[node_1].push_back(std::make_tuple(node_2, cost));
            graph[node_2].push_back(std::make_tuple(node_1, cost));
        }
    }

    return graph;
}
/**generates an undicrected graph with `nodes` nodes and up to `edge_factor` edges per node
 *
 * @param nodes amount of nodes
 * @param edge_factor up to `edge_factor` edges per node
 * @param cost expects a tuple with (mu,sigma) for the normal distribution which generates the cost
 * @retrun graph_t in the form graph_t[node] = [(node_1, cost), (node_2, cost), (node_3, cost)]
 */
inline graph_t gen_undirected_graph_rand(
    std::size_t nodes = 1000, size_t edge_factor = 2, double cost_mu = 1, double cost_sig = 1)
{
    graph_t graph;
    std::unordered_set<int> node_list;
    int i = 0;
    std::generate_n(std::inserter(node_list, node_list.begin()), nodes, [&i]() { return i++; });

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> costs{cost_mu, cost_sig};
    std::uniform_int_distribution<> edges{1, static_cast<int>(edge_factor)};

    for (const auto &node_1 : node_list)
    {
        int tmp_edges = edges(gen) - graph[node_1].size();
        if (tmp_edges <= 0)
        {
            continue;
        }

        std::unordered_set<int> choosen_nodes;
        std::transform(graph[node_1].begin(),
            graph[node_1].end(),
            std::inserter(choosen_nodes, choosen_nodes.begin()),
            [](std::tuple<int, double> val) -> int { return std::get<0>(val); });
        choosen_nodes.insert(node_1);

        auto connect_nodes = choose_nodes(choosen_nodes, node_list, tmp_edges);
        for (const auto &node_2 : connect_nodes)
        {
            auto cost = std::abs(costs(gen));
            graph[node_1].push_back(std::make_tuple(node_2, cost));
            graph[node_2].push_back(std::make_tuple(node_1, cost));
        }
    }

    return graph;
}

} // namespace graph
} // namespace epa

#endif /* GRAPHEN_EPA_GRAPHS_HPP_ */
