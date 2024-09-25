/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (!root) return nullptr; // Caso base
        
        // Si el valor del nodo es menor que el límite inferior, podar el subárbol izquierdo
        if (root->val < low) {
            return trimBST(root->right, low, high); // El subárbol derecho puede tener valores en el rango
        }
        
        // Si el valor del nodo es mayor que el límite superior, podar el subárbol derecho
        if (root->val > high) {
            return trimBST(root->left, low, high); // El subárbol izquierdo puede tener valores en el rango
        }
        
        // Si el valor del nodo está dentro del rango, podar recursivamente ambos subárboles
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        
        return root; // El nodo actual está en el rango, lo mantenemos
