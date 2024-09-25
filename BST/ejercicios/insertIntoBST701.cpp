class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // Caso base: si el árbol está vacío, creamos un nuevo nodo con el valor
        if (root == nullptr) {
            return new TreeNode(val);
        }
        
        // Si el valor es menor que el valor del nodo actual, insertamos en el subárbol izquierdo
        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        }
        // Si el valor es mayor, insertamos en el subárbol derecho
        else {
            root->right = insertIntoBST(root->right, val);
        }
        
        // Devolvemos la raíz actualizada
        return root;
    }
};
