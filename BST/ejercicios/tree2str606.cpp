class Solution {
public:
    string tree2str(TreeNode* root) {
        if (!root) return ""; // Caso base: si el nodo es nulo, retorna una cadena vacía.

        string result = to_string(root->val); // Agrega el valor del nodo actual.

        // Si el nodo tiene un hijo izquierdo, procesa el hijo izquierdo.
        if (root->left) {
            result += "(" + tree2str(root->left) + ")"; // Agrega el hijo izquierdo entre paréntesis.
        } else if (root->right) {
            // Si hay un hijo derecho pero no un hijo izquierdo, agrega un paréntesis vacío.
            result += "()"; 
        }

        // Si el nodo tiene un hijo derecho, procesa el hijo derecho.
        if (root->right) {
            result += "(" + tree2str(root->right) + ")"; // Agrega el hijo derecho entre paréntesis.
        }

        return result; // Retorna la representación en cadena del árbol.
    }
};
