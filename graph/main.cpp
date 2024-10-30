#include <iostream>
#include <vector>
#include <climits> //indica el valor máximo de un entero usando INT_MAX

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
    struct Node {
        std::vector<std::pair<int, int>> adj; //lista adyacencia par (hijo, peso)
    };

    std::vector<Node> nodes; //vector de nodos

public:
    //agrega nodo a grafo
    void addNode() {
        nodes.emplace_back(Node());
    }

    //agrega arista entre nodos a y b con peso
    void addEdge(int a, int b, int weight) {
        nodes[a].adj.emplace_back(b, weight);
    }

    //breadth first search para recorrer grafo desde nodo fuente
    void BFS(int src) {
        Queue<int> q;
        std::vector<bool> visited(nodes.size(), false);

        q.enqueue(src);
        visited[src] = true;

        while (!q.isEmpty()) {
            int node = q.dequeue();
            std::cout << node << " ";

            //recorre cada hijo del nodo actual
            for (const auto& child : nodes[node].adj) {
                if (!visited[child.first]) {
                    q.enqueue(child.first);
                    visited[child.first] = true;
                }
            }
        }
    }

    //depth first search para recorrer el grafo desde un nodo fuente
    void DFS(int src) {
        Stack<int> s;
        std::vector<bool> visited(nodes.size(), false);

        s.push(src);
        while (!s.isEmpty()) {
            int node = s.pop();

            if (!visited[node]) {
                std::cout << node << " ";
                visited[node] = true;

                //recorre cada hijo del nodo actual en orden inverso
                for (auto it = nodes[node].adj.rbegin(); it != nodes[node].adj.rend(); ++it) {
                    if (!visited[it->first]) {
                        s.push(it->first);
                    }
                }
            }
        }
    }

    //verifica si el grafo es bipartito
    bool isBipartite() {
        std::vector<int> color(nodes.size(), -1);

        for (int i = 0; i < nodes.size(); ++i) {
            if (color[i] == -1) {
                Queue<int> q;
                q.enqueue(i);
                color[i] = 0;

                while (!q.isEmpty()) {
                    int u = q.dequeue();

                    //verifica si el nodo vecino tiene el mismo color
                    for (const auto& [v, _] : nodes[u].adj) {
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
        return true;
    }

    //algoritmo dijkstra camino mas corto desde nodo fuente
    std::vector<int> dijkstra(int src) {
        int n = nodes.size();
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

            for (const auto& [v, weight] : nodes[u].adj) {
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        return dist;
    }
};

int main() {
    Graph g;
    g.addNode();
    g.addNode();
    g.addNode();
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
