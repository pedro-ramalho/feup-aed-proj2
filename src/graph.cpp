#include "../headers/graph.h"

Graph::Graph(int num, bool has_dir) : n(num), has_dir(has_dir), nodes(num + 1) {}

void Graph::add_edge(int src, int dest, int weight) {
    if (src < 1 || dest < 1 || dest > n) return;
    nodes[src].adj.push_back( {dest, weight} );
    if (!has_dir) nodes[dest].adj.push_back({src, weight});
}

void Graph::dfs(int v) {
    std::cout << v << " "; //show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) dfs(w);
    }
}

void Graph::dfs_topological(int v, std::list<int>& order) {
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) dfs_topological(w, order);
    }

    order.push_front(v);
}

int Graph::dfs_counter(int v) {
    int counter = 1;
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) counter += dfs_counter(w);
    }
    
    return counter;
}

void Graph::bfs(int v) {
    for (int i = 1; i < n; i++) nodes[i].visited = false;
    std::queue<int> q = std::queue<int>();
    q.push(v);

    nodes[v].visited = true;
    nodes[v].distance = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        std::cout << u << " "; //show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}

int Graph::bfs_distances(int a, int b) {
    if (a == b) return 0;

    for (int i = 1; i < n; i++) nodes[i].visited = false;
    std::queue<int> q = std::queue<int>();
    q.push(a);

    nodes[a].visited = true;
    nodes[a].distance = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                if (w == b) return nodes[w].distance - nodes[a].distance;
            }
        }
    }

    return -1;
}

int Graph::out_degree(int v) {
    if (v < 1 || v > n) return -1;
    return nodes[v].adj.size();
}

int Graph::connected_components() {
    int counter = 0;

    for (int i = 1; i <= n; i++) nodes[i].visited = false;

    for (int v = 1; v <= n; v++)
        if (!nodes[v].visited) {
            counter++;
            dfs(v);
        }
    
    return counter;
}

int Graph::giant_component() {
    int max = 0;

    for (int i = 1; i <= n; i++) nodes[i].visited = false;

    for (int v = 1; v <= n; v++) {
        int num_nodes = dfs_counter(v);
        if (num_nodes > max) max = num_nodes;
    }

    return max;
}

std::list<int> Graph::topological_sorting() {
    std::list<int> order = std::list<int>();

    for (int i = 1; i <= n; i++) nodes[i].visited = false;

    for (int v = 1; v <= n; v++)
        if (!nodes[v].visited)
            dfs_topological(v, order);

    for (auto elem : order) std::cout << elem << " "; //show possible order

    return order;
}

int Graph::distance(int a, int b) {
    return bfs_distances(a, b);
}
