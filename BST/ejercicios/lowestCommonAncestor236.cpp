
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            return root; // Si el nodo es nulo o igual a p o q, devolver root
        }

        // Buscar en el subárbol izquierdo y derecho
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // Si ambos subárboles devuelven un nodo no nulo, este nodo es el LCA
        if (left && right) {
            return root;
        }

        // Devolver el nodo que no es nulo, o nulo si ambos son nulos
        return left ? left : right;
    }
};
