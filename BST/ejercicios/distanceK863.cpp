class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<TreeNode*, TreeNode*> parentMap;  // Para registrar los padres de cada nodo.
        markParents(root, parentMap);  // Llenar el mapa de padres.
        
        unordered_set<TreeNode*> visited;  // Para evitar volver a visitar los nodos.
        queue<TreeNode*> q;
        q.push(target);  // Comenzamos desde el nodo objetivo.
        visited.insert(target);

        int currentLevel = 0;
        
        while (!q.empty()) {
            int size = q.size();
            if (currentLevel == k) break;  // Si alcanzamos la distancia k, terminamos.
            
            currentLevel++;
            
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                // Revisar los hijos.
                if (node->left && !visited.count(node->left)) {
                    visited.insert(node->left);
                    q.push(node->left);
                }
                if (node->right && !visited.count(node->right)) {
                    visited.insert(node->right);
                    q.push(node->right);
                }
                
                // Revisar el padre.
                if (parentMap[node] && !visited.count(parentMap[node])) {
                    visited.insert(parentMap[node]);
                    q.push(parentMap[node]);
                }
            }
        }
        
        // Guardar el resultado.
        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front()->val);
            q.pop();
        }
        
        return result;
    }
    
private:
    // Función para registrar los padres de cada nodo.
    void markParents(TreeNode* node, unordered_map<TreeNode*, TreeNode*>& parentMap) {
        if (!node) return;
        
        if (node->left) {
            parentMap[node->left] = node;
            markParents(node->left, parentMap);
        }
        
        if (node->right) {
            parentMap[node->right] = node;
            markParents(node->right, parentMap);
        }
    }
};
