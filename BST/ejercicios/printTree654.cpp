class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
        // 1. Calcular la altura del árbol
        int height = getHeight(root);
        int rows = height + 1;
        int cols = (1 << rows) - 1; // 2^(height+1) - 1

        // 2. Inicializar la matriz con cadenas vacías
        vector<vector<string>> res(rows, vector<string>(cols, ""));

        // 3. Llamar a la función recursiva para colocar los nodos
        fill(res, root, 0, 0, cols - 1, height);
        return res;
    }

private:
    int getHeight(TreeNode* node) {
        if (!node) return -1;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    void fill(vector<vector<string>>& res, TreeNode* node, int row, int left, int right, int height) {
        if (!node) return;
        int col = (left + right) / 2;
        res[row][col] = to_string(node->val);
        fill(res, node->left, row + 1, left, col - 1, height);
        fill(res, node->right, row + 1, col + 1, right, height);
    }
};
