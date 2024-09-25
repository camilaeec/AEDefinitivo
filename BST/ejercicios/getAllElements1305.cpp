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
    // Función para recorrer el árbol en inorden y almacenar los valores en un vector
    void inorderTraversal(TreeNode* root, vector<int>& elements) {
        if (root == nullptr) return;
        inorderTraversal(root->left, elements);
        elements.push_back(root->val);
        inorderTraversal(root->right, elements);
    }

    //merge vectores ordenados
    vector<int> mergeSortedArrays(const vector<int>& arr1, const vector<int>& arr2) {
        vector<int> merged;
        int i = 0, j = 0;
        while (i < arr1.size() && j < arr2.size()) {
            if (arr1[i] < arr2[j]) {
                merged.push_back(arr1[i++]);
            } else {
                merged.push_back(arr2[j++]);
            }
        }
        // Agregar los elementos restantes de arr1
        while (i < arr1.size()) {
            merged.push_back(arr1[i++]);
        }
        // Agregar los elementos restantes de arr2
        while (j < arr2.size()) {
            merged.push_back(arr2[j++]);
        }
        return merged;
    }

    //solucion
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> tree1Elements;
        vector<int> tree2Elements;
        
        // Obtener los elementos en orden ascendente de ambos árboles
        inorderTraversal(root1, tree1Elements);
        inorderTraversal(root2, tree2Elements);
        
        // Fusionar ambos vectores ordenados
        return mergeSortedArrays(tree1Elements, tree2Elements);
    }
};
