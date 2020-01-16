import random
import copy
import collections

def choose_nodes(choosen, target_nodes, edges):
    """
    choose `edges` nodes from `target_nodes`, whitout `chossen` and doubled nodes
    Function is side effect free
    
    @param choosen list of already chossen elements
    @param list to choose elements from
    @param edges amount of edged
    @return nodes to pick
    """
    target_nodes = copy.deepcopy(target_nodes)
    for elem in choosen:
        target_nodes.remove(elem)
        
    for _ in range(edges):
        node = random.choice(target_nodes)
        target_nodes.remove(node)
        yield node

def gen_directed_graph(nodes = 1000, edge_factor = 2, costs = (1,1)):
    """
    generates a dicrected graph with `nodes` nodes and `edge_factor` edges per node
    
    @param nodes amount of nodes
    @param edge_factor edges per node
    @param cost expects a tuple with (mu,sigma) for the normal distribution which generates the cost
    @retrun dict in the form dict[node] = [(node_1, cost), (node_2, cost), (node_3, cost)]
    """
    graph = {}
    node_list = list(range(nodes))
    for node_1 in range(nodes):
        graph[node_1] = []
        for node_2 in choose_nodes([node_1], node_list, edge_factor):
            cost = random.gauss(costs[0],costs[1])
            graph[node_1].append((node_2,cost))
    return graph

def gen_directed_graph_rand(nodes = 1000, edge_factor = 3, costs = (1,1)):
    """
    generates a dicrected graph with `nodes` nodes and up to `edge_factor` edges per node
    
    @param nodes amount of nodes
    @param edge_factor up to `edge_factor` edges per node
    @param cost expects a tuple with (mu,sigma) for the normal distribution which generates the cost
    @retrun dict in the form dict[node] = [(node_1, cost), (node_2, cost), (node_3, cost)]
    """
    graph = {}
    node_list = list(range(nodes))
    for node_1 in range(nodes):
        graph[node_1] = []
        edges = random.randint(1,edge_factor)
        for node_2 in choose_nodes([node_1], node_list, edges):
            cost = random.gauss(costs[0],costs[1])
            graph[node_1].append((node_2,cost))
            
    return graph

def gen_undirected_graph(nodes = 1000, edge_factor = 2, costs = (1,1)):
    """
    generates an undicrected graph with `nodes` nodes and around `edge_factor` edges per node
    
    @param nodes amount of nodes 
    @param edge_factor approximate edges per node, might happen that some nodes have more edges
    @param cost expects a tuple with (mu,sigma) for the normal distribution which generates the cost
    @retrun dict in the form dict[node] = [(node_1, cost), (node_2, cost), (node_3, cost)]
    """
    graph = collections.defaultdict(list)
    node_list = list(range(nodes))
    for node_1 in range(nodes):
        
        if node_1 not in graph:
            graph[node_1] = []
        
        edges = edge_factor - len(graph[node_1]) 
        choosen = list(map(lambda x: x[0], graph[node_1]))
        choosen.append(node_1)
        
        for node_2 in choose_nodes(choosen, node_list, edges):
            cost = random.gauss(costs[0],costs[1])
            graph[node_1].append((node_2,cost))
            graph[node_2].append((node_1,cost))
            
    return graph

def gen_undirected_graph_rand(nodes = 1000, edge_factor = 3, costs = (1,1)):
    """
    generates an undicrected graph with `nodes` nodes and up to `edge_factor` edges per node
    
    @param nodes amount of nodes
    @param edge_factor up to `edge_factor` edges per node
    @param cost expects a tuple with (mu,sigma) for the normal distribution which generates the cost
    @retrun dict in the form dict[node] = [(node_1, cost), (node_2, cost), (node_3, cost)]
    """
    graph = collections.defaultdict(list)
    node_list = list(range(nodes))
    for node_1 in range(nodes):
        
        if node_1 not in graph:
            graph[node_1] = []
        
        edges = random.randint(1,edge_factor)
        edges = edges - len(graph[node_1])
        choosen = list(map(lambda x: x[0], graph[node_1]))
        choosen.append(node_1)
        
        
        for node_2 in choose_nodes(choosen, node_list, edges):
            cost = random.gauss(costs[0],costs[1])
            graph[node_1].append((node_2,cost))
            graph[node_2].append((node_1,cost))
            
    return graph

