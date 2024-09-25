class Solution {
public:
    int rob(TreeNode* root) {
        // Estructura para almacenar el resultado de la maximización
        pair<int, int> result = dfs(root);
        return max(result.first, result.second); // Retorna el máximo de las dos opciones
    }

private:
    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0}; // Si el nodo es nulo, devuelve 0 en ambas opciones
        
        // Recurre en los hijos izquierdo y derecho
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        
        // Cuando robamos el nodo actual, no podemos robar a sus hijos
        int robCurrent = node->val + left.second + right.second;
        
        // Cuando no robamos el nodo actual, podemos elegir robar o no a sus hijos
        int skipCurrent = max(left.first, left.second) + max(right.first, right.second);
        
        return {robCurrent, skipCurrent}; // Retorna el resultado para este nodo
    }
};
