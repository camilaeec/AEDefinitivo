#include <iostream>
#include <vector>
#include <climits>

#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

///////////////////////////////////////////CLASE STACK///////////////////////////////////////////
template <typename T>
class Stack {
private:
    T list[MAX_STACK_SIZE];
    int top_index;

public:
    Stack() : top_index(-1) {}

    bool isFull() const {
        return top_index >= MAX_STACK_SIZE - 1;
    }

    bool isEmpty() const {
        return top_index == -1;
    }

    T top() const {
        return list[top_index];
    }

    void push(T e) {
        if (!isFull()) {
            list[++top_index] = e;
        }
    }

    T pop() {
        T item = top();
        if (!isEmpty()) {
            --top_index;
        }
        return item;
    }

    int size() const {
        return top_index + 1;
    }
};

///////////////////////////////////////////CLASE QUEUE///////////////////////////////////////////
template <typename T>
class Queue {
private:
    T list[MAX_QUEUE_SIZE];
    int front_index, rear_index;

public:
    Queue() : front_index(0), rear_index(0) {}

    bool isFull() const {
        return front_index == ((rear_index + 1) % MAX_QUEUE_SIZE);
    }

    bool isEmpty() const {
        return front_index == rear_index;
    }

    T front() const {
        return list[(front_index + 1) % MAX_QUEUE_SIZE];
    }

    void enqueue(T e) {
        if (!isFull()) {
            rear_index = (rear_index + 1) % MAX_QUEUE_SIZE;
            list[rear_index] = e;
        }
    }

    T dequeue() {
        T item = front();
        if (!isEmpty()) {
            front_index = (front_index + 1) % MAX_QUEUE_SIZE;
        }
        return item;
    }

    int size() const {
        return (rear_index - front_index + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    }
};

///////////////////////////////////////////CLASE GRAPH///////////////////////////////////////////
class Graph {
private:
    std::vector<std::vector<int>> adj; // Matriz de adyacencia para almacenar el grafo con pesos

public:
    Graph(int nodes) : adj(nodes, std::vector<int>(nodes, INT_MAX)) {
        for (int i = 0; i < nodes; ++i) {
            adj[i][i] = 0;
        }
    }

    // Agrega arista entre nodos a y b con peso
    void addEdge(int a, int b, int weight) {
        adj[a][b] = weight;
    }

    // BFS para recorrer grafo desde nodo fuente
    void BFS(int src) {
        Queue<int> q;
        std::vector<bool> visited(adj.size(), false);

        q.enqueue(src);
        visited[src] = true;

        while (!q.isEmpty()) {
            int node = q.dequeue();
            std::cout << node << " ";

            for (int i = 0; i < adj[node].size(); ++i) {
                if (adj[node][i] != INT_MAX && !visited[i]) {
                    q.enqueue(i);
                    visited[i] = true;
                }
            }
        }
    }

    // DFS para recorrer el grafo desde un nodo fuente
    void DFS(int src) {
        Stack<int> s;
        std::vector<bool> visited(adj.size(), false);

        s.push(src);
        while (!s.isEmpty()) {
            int node = s.pop();

            if (!visited[node]) {
                std::cout << node << " ";
                visited[node] = true;

                for (int i = adj[node].size() - 1; i >= 0; --i) {
                    if (adj[node][i] != INT_MAX && !visited[i]) {
                        s.push(i);
                    }
                }
            }
        }
    }

    // Verifica si el grafo es bipartito
    bool isBipartite() {
        std::vector<int> color(adj.size(), -1);

        for (int i = 0; i < adj.size(); ++i) {
            if (color[i] == -1) {
                Queue<int> q;
                q.enqueue(i);
                color[i] = 0;

                while (!q.isEmpty()) {
                    int u = q.dequeue();

                    for (int v = 0; v < adj[u].size(); ++v) {
                        if (adj[u][v] != INT_MAX) {
                            if (color[v] == -1) {
                                color[v] = 1 - color[u];
                                q.enqueue(v);
                            } else if (color[v] == color[u]) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    // Algoritmo Dijkstra para camino más corto desde un nodo fuente
    std::vector<int> dijkstra(int src) {
        int n = adj.size();
        std::vector<int> dist(n, INT_MAX);
        std::vector<bool> sptSet(n, false);

        dist[src] = 0;

        for (int count = 0; count < n - 1; ++count) {
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!sptSet[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }

            sptSet[u] = true;

            for (int v = 0; v < n; ++v) {
                if (adj[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
        return dist;
    }
};

int main() {
    Graph g(3);
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 8);
    g.addEdge(0, 2, 10);

    std::cout << "BFS starting from node 0:\n";
    g.BFS(0);

    std::cout << "\nDFS starting from node 0:\n";
    g.DFS(0);

    std::cout << "\n\nIs the graph bipartite? " << (g.isBipartite() ? "Yes" : "No") << "\n";

    std::cout << "\nShortest paths from node 0 using Dijkstra:\n";
    auto dist = g.dijkstra(0);
    for (int i = 0; i < dist.size(); ++i) {
        std::cout << "Distance to node " << i << ": " << dist[i] << "\n";
    }

    return 0;
}
