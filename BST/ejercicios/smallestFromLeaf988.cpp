class Solution {
public:
    string smallestFromLeaf(TreeNode* root) {
        string result = "~"; // Inicializamos con un valor lexicográficamente mayor a cualquier posible cadena.
        dfs(root, "", result);
        return result;
    }

private:
    void dfs(TreeNode* node, string current, string &result) {
        if (!node) return;
        
        // Agregamos el carácter correspondiente al valor del nodo.
        current = char(node->val + 'a') + current;

        // Si estamos en una hoja, comparamos la cadena actual con el resultado.
        if (!node->left && !node->right) {
            if (current < result) {
                result = current;
            }
        }

        // Continuamos el recorrido en profundidad.
        dfs(node->left, current, result);
        dfs(node->right, current, result);
    }
};
