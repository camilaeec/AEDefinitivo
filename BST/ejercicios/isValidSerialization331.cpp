// Definición del nodo del árbol binario
struct TreeNodo {
    string value;
    TreeNodo* left;
    TreeNodo* right;

    TreeNodo(string val) : value(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNodo* root;

    Solution() : root(nullptr) {}

    bool isValidSerialization(string preorder) {
        int slots = 1; // Inicia con un espacio disponible para la raíz
        int n = preorder.length();
        
        for (int i = 0; i < n; ++i) {
            if (preorder[i] == ',') {
                continue; // Ignorar las comas
            }

            // Reducir un slot para cada nodo encontrado
            if (--slots < 0) {
                return false; // Si no hay suficientes slots
            }

            // Si es un nodo no nulo, genera dos slots más (dos hijos)
            if (preorder[i] != '#') {
                while (i < n && preorder[i] != ',') {
                    ++i; // Avanzar hasta el siguiente valor
                }
                slots += 2;
            }
        }

        return slots == 0; // Serialización válida si los slots se consumen exactamente
    }
};
