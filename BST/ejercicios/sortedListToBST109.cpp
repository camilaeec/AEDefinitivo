/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    // Función auxiliar para contar los nodos de la lista enlazada
    int getListLength(ListNode* head) {
        int len = 0;
        while (head) {
            len++;
            head = head->next;
        }
        return len;
    }

    // Función para construir el BST de forma recursiva
    TreeNode* sortedListToBSTHelper(ListNode*& head, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        // Encuentra el punto medio
        int mid = start + (end - start) / 2;

        // Construir el subárbol izquierdo
        TreeNode* left = sortedListToBSTHelper(head, start, mid - 1);

        // La raíz es el nodo actual de la lista
        TreeNode* root = new TreeNode(head->val);
        root->left = left;

        // Avanza al siguiente nodo en la lista enlazada
        head = head->next;

        // Construir el subárbol derecho
        root->right = sortedListToBSTHelper(head, mid + 1, end);

        return root;
    }

    // Función principal para convertir la lista enlazada en un BST
    TreeNode* sortedListToBST(ListNode* head) {
        int len = getListLength(head);
        return sortedListToBSTHelper(head, 0, len - 1);
    }
};

// Función para recorrer el árbol en orden y mostrar los nodos (para pruebas)
void inorderTraversal(TreeNode* root) {
    if (!root) return;
    inorderTraversal(root->left);
    std::cout << root->val << " ";
    inorderTraversal(root->right);
}
