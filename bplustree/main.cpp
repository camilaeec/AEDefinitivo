#include <iostream>

#define MIN_DEGREE 2
#define MAX_KEYS (2 * MIN_DEGREE - 1)

struct BPlusTree {
    struct Node {
        int keys[MAX_KEYS];
        Node* children[MAX_KEYS + 1];
        int numKeys;
        bool isLeaf;

        Node(bool leaf) {
            isLeaf = leaf;
            numKeys = 0;
            for (int i = 0; i < MAX_KEYS + 1; i++) {
                children[i] = nullptr;
            }
        }
    };

    Node* root;

    BPlusTree() {
        root = new Node(true);
    }

    Node* search(Node* node, int key) {
        int i = 0;
        while (i < node->numKeys && key > node->keys[i]) {
            i++;
        }
        if (i < node->numKeys && node->keys[i] == key) {
            return node; // Clave encontrada en el nodo actual
        }
        if (node->isLeaf) {
            return nullptr; // No encontrado
        }
        return search(node->children[i], key); // Buscar en el hijo apropiado
    }

    void insert(int key) {
        if (root->numKeys == MAX_KEYS) {
            Node* newRoot = new Node(false);
            newRoot->children[0] = root;
            splitChild(newRoot, 0, root);
            int i = (newRoot->keys[0] < key) ? 1 : 0;
            insertNonFull(newRoot->children[i], key);
            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }

    void insertNonFull(Node* node, int key) {
        int i = node->numKeys - 1;
        if (node->isLeaf) {
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->numKeys++;
        } else {
            while (i >= 0 && node->keys[i] > key) {
                i--;
            }
            i++;
            if (node->children[i]->numKeys == MAX_KEYS) {
                splitChild(node, i, node->children[i]);
                if (node->keys[i] < key) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    void splitChild(Node* parent, int i, Node* fullChild) {
        Node* newChild = new Node(fullChild->isLeaf);
        newChild->numKeys = MIN_DEGREE - 1;

        for (int j = 0; j < MIN_DEGREE - 1; j++) {
            newChild->keys[j] = fullChild->keys[j + MIN_DEGREE];
        }

        if (!fullChild->isLeaf) {
            for (int j = 0; j < MIN_DEGREE; j++) {
                newChild->children[j] = fullChild->children[j + MIN_DEGREE];
            }
        }

        fullChild->numKeys = MIN_DEGREE - 1;

        for (int j = parent->numKeys; j >= i + 1; j--) {
            parent->children[j + 1] = parent->children[j];
        }

        parent->children[i + 1] = newChild;

        for (int j = parent->numKeys - 1; j >= i; j--) {
            parent->keys[j + 1] = parent->keys[j];
        }

        parent->keys[i] = fullChild->keys[MIN_DEGREE - 1];
        parent->numKeys++;
    }

    void remove(Node* node, int key) {
        int i = 0;
        while (i < node->numKeys && node->keys[i] < key) {
            i++;
        }

        if (i < node->numKeys && node->keys[i] == key) {
            if (node->isLeaf) {
                for (int j = i; j < node->numKeys - 1; j++) {
                    node->keys[j] = node->keys[j + 1];
                }
                node->numKeys--;
            } else {
                std::cout << "Eliminar de nodo no hoja aún no implementado\n";
            }
        } else {
            if (node->isLeaf) {
                std::cout << "Clave no encontrada\n";
            } else {
                remove(node->children[i], key);
            }
        }
    }

    void print(Node* node) {
        if (!node) return;
        for (int i = 0; i < node->numKeys; i++) {
            if (!node->isLeaf) {
                print(node->children[i]);
            }
            std::cout << node->keys[i] << " ";
        }
        if (!node->isLeaf) {
            print(node->children[node->numKeys]);
        }
    }

    void printTree() {
        print(root);
        std::cout << std::endl;
    }
};

int main() {
    BPlusTree tree;
    
    // Inserciones de prueba
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    std::cout << "Arbol B+ tras inserciones: ";
    tree.printTree();

    // Ejemplo de eliminación de una clave en hoja
    tree.remove(tree.root, 6);
    std::cout << "Arbol B+ tras eliminar 6: ";
    tree.printTree();

    // Búsqueda de clave
    BPlusTree::Node* found = tree.search(tree.root, 10);
    if (found) {
        std::cout << "Clave 10 encontrada\n";
    } else {
        std::cout << "Clave 10 no encontrada\n";
    }

    return 0;
}
