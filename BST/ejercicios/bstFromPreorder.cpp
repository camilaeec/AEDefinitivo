struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    //aux-construir BST
    TreeNode* buildBST(vector<int>& preorder, int& index, int lower, int upper) {
        //si ya finalizado o elemento actual no en los limites, nullptr
        if (index == preorder.size() || preorder[index] < lower || preorder[index] > upper) {
            return nullptr;
        }

        //valor actual de preorder es la raiz del subarbol
        int val = preorder[index++];
        TreeNode* root = new TreeNode(val);

        //construir subBST izquierdo (con el lim superior igual al valor actual)
        root->left = buildBST(preorder, index, lower, val);

        //construir subBST derecho (con el lim igual al valor actual)
        root->right = buildBST(preorder, index, val, upper);

        return root;
    }

    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int index = 0;
        return buildBST(preorder, index, INT_MIN, INT_MAX);
    }
};
