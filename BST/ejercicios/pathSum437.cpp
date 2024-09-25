class Solution {
public:
    int countPaths(TreeNode* root, int currentSum, int targetSum) {
        if (!root) return 0;

        currentSum += root->val;

        int totalPaths = (currentSum == targetSum) ? 1 : 0;

        totalPaths += countPaths(root->left, currentSum, targetSum);
        totalPaths += countPaths(root->right, currentSum, targetSum);

        return totalPaths;
    }

    void findPaths(TreeNode* root, int targetSum, int* totalCount) {
        if (!root) return;

        *totalCount += countPaths(root, 0, targetSum);

        findPaths(root->left, targetSum, totalCount);
        findPaths(root->right, targetSum, totalCount);
    }

    int pathSum(TreeNode* root, int targetSum) {
        int totalCount = 0;
        findPaths(root, targetSum, &totalCount);
        return totalCount;
    }
};
