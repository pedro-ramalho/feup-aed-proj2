#include "../../headers/graphs/graph.h"

Graph::Graph(int num, bool has_dir) : n(num), has_dir(has_dir), nodes(num + 1) {}

void Graph::add_edge(int src, int dest, double weight, std::string line) {
    if (src < 1 || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!has_dir) nodes[dest].adj.push_back({src, weight, line});
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
    nodes[v].dist = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        std::cout << u << " "; //show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
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
    nodes[a].dist = 0;

    std::vector<int> vec;

    while (!q.empty()) {
        int u = q.front(); 
        vec.push_back(u);
        q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
                if (w == b) {
                    for (auto x : vec) std::cout << x << std::endl;
                    return nodes[w].dist - nodes[a].dist;
                }
            }
        }
    }

    return -1;
}

std::list<int> Graph::bfs_path(int a, int b) {
    for (int i = 1; i < this->n; i++) nodes[i].visited = false;

    std::queue<int> q = std::queue<int>();
    std::list<int> path = std::list<int>();

    this->nodes[a].visited = true;
    this->nodes[a].dist = 0;
    this->nodes[a].pred = a;
    q.push(a);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            if (!nodes[v].visited) {
                nodes[v].pred = u;
                
                nodes[v].visited = true;
                q.push(v);
            }
        }
    }
    
    int i = b;
    while (nodes[i].pred != i) {
        path.push_front(i);
        i = nodes[i].pred;
    }

    path.push_front(i);
    return path;
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

void Graph::dijkstra(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            } 
        }
    }
}

int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}

std::list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra(a);
    std::list<int> path;
    if (nodes[b].dist == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}