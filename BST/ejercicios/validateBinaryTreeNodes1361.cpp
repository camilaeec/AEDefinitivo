class Solution {
public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        vector<int> parentCount(n, 0);

        // Contar cuántos padres tiene cada nodo
        for (int i = 0; i < n; ++i) {
            if (leftChild[i] != -1) {
                parentCount[leftChild[i]]++;
                if (parentCount[leftChild[i]] > 1) return false; // Más de un padre
            }
            if (rightChild[i] != -1) {
                parentCount[rightChild[i]]++;
                if (parentCount[rightChild[i]] > 1) return false; // Más de un padre
            }
        }

        // Encontrar el nodo raíz
        int root = -1;
        for (int i = 0; i < n; ++i) {
            if (parentCount[i] == 0) {
                if (root != -1) return false; // Más de un nodo raíz
                root = i;
            }
        }
        if (root == -1) return false; // No hay nodo raíz

        // Verificar conectividad usando DFS o BFS
        vector<bool> visited(n, false);
        if (!dfs(root, leftChild, rightChild, visited)) return false;

        // Asegurar que todos los nodos fueron visitados
        for (bool v : visited) {
            if (!v) return false;
        }

        return true;
    }

private:
    bool dfs(int node, vector<int>& leftChild, vector<int>& rightChild, vector<bool>& visited) {
        if (visited[node]) return false;
        visited[node] = true;

        if (leftChild[node] != -1 && !dfs(leftChild[node], leftChild, rightChild, visited)) return false;
        if (rightChild[node] != -1 && !dfs(rightChild[node], leftChild, rightChild, visited)) return false;

        return true;
    }
};
