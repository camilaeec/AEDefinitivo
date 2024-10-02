#include <iostream>

template <typename T>
class AVLTree {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        int balanceFactor;  //bf (recordatorio: (-) derecha; (+) izquierda)

        Node(T k) : key(k), left(nullptr), right(nullptr), balanceFactor(0) {}
    };

    Node* root;

    //altura del nodo
    int height(Node* node) {
        if (node == nullptr) {
            return -1;  //arbol vacio
        }
        return 1 + std::max(height(node->left), height(node->right));
    }

    //actualizar bF de un nodo
    void updateBalanceFactor(Node* node) {
        if (node != nullptr) {
            node->balanceFactor = height(node->left) - height(node->right);
        }
    }

    //simple R rotation
    Node* rotateRight(Node* y) {
        Node* yLeft = y->left;
        Node* yLRight = yLeft->right;

        //rotacion
        yLeft->right = y;
        y->left = yLRight;

        //actualizar bF
        updateBalanceFactor(y);
        updateBalanceFactor(yLeft);

        return yLeft;
    }

    //simple L rotation
    Node* rotateLeft(Node* x) {
        Node* xRight = x->right;
        Node* x2Right = xRight->left;

        //rotacion
        xRight->left = x;
        x->right = x2Right;

        //actualizar bF
        updateBalanceFactor(x);
        updateBalanceFactor(xRight);

        return xRight;
    }

    //insert nodo en el árbol AVL
    Node* insert(Node* node, T key) {
        //insert normal
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else  //no key duplicadas
            return node;

        updateBalanceFactor(node);

        //ROTACIONES
        //1. simple R rotation
        if (node->balanceFactor > 1 && key < node->left->key)
            return rotateRight(node);

        //2. simple L rotation
        if (node->balanceFactor < -1 && key > node->right->key)
            return rotateLeft(node);

        //3. double LR (rotacion doble izquierda-derecha)
        if (node->balanceFactor > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        //4. double RL (rotacion doble derecha-izquierda)
        if (node->balanceFactor < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;  // return arbol balanceado
    }

    //buscar el nodo con el valor min
    Node* findMin(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    //eliminar un nodo de arbol AVL
    Node* remove(Node* node, T key) { //node: nodo actual; key: nodo a buscar
        if (node == nullptr) {
            std::cout << "Error: Nodo con la clave " << key << " no encontrado." << std::endl;
            return nullptr;
        }

        //buscar nodo a eliminar
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            //nodo con un solo hijo o sin hijos
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                //sintaxis del condicional
                //condicion ? valor_si_condicion_es_verdadera : valor_si_condicion_es_falsa;

                if (temp == nullptr) {
                    //sin hijos
                    temp = node;
                    node = nullptr;
                } else {
                    //con un solo hijo
                    *node = *temp;
                }
                delete temp;
            } else {
                //nodo con dos hijos: obtener el sucesor en inorden
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }

        //si el arbol tiene un solo nodo
        if (node == nullptr)
            return node;

        //actualizar balanceFactor
        updateBalanceFactor(node);

        //ROTACIONES

        //SIGNOS IGUALES
        //1. Caso simple R rotation
        if (node->balanceFactor > 1 && node->left->balanceFactor >= 0) //bF>1: grande hacia izquierda
            return rotateRight(node);

        //2. Caso simple L rotation
        if (node->balanceFactor < -1 && node->right->balanceFactor <= 0) //bF<-1: grande hacia derecha
            return rotateLeft(node);

        //SIGNOS DISTINTOS
        //3. Caso double L-R
        if (node->balanceFactor > 1 && node->left->balanceFactor < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        //4. Caso double R-L
        if (node->balanceFactor < -1 && node->right->balanceFactor > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    //busqueda recursiva de nodo en arbol AVL
    Node* search(Node* node, T key) {
        if (node == nullptr) {
            std::cout << "Error: Nodo con la clave " << key << " no encontrado." << std::endl;
            return nullptr;  //nodo no encontrado o arbol vacio
        }

        if (node->key == key) {
            return node;  //nodo encontrado
        }

        if (key < node->key) {
            return search(node->left, key);  //buscar en el subarbol izquierdo
        } else {
            return search(node->right, key);  //buscar en el subarbol derecho
        }
    }

    //recorrer en orden
    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            std::cout << root->key << " (BF: " << root->balanceFactor << ") ";
            inOrder(root->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T key) {
        root = insert(root, key);
    }

    void remove(T key) {
        root = remove(root, key);
    }

    Node* search(T key) {
        return search(root, key);
    }

    void inOrder() {
        inOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "Recorrido en orden del AVL Tree (int) con factor de balance:" << std::endl;
    tree.inOrder();

    tree.remove(40);

    std::cout << "Despues de eliminar el nodo 40:" << std::endl;
    tree.inOrder();

    return 0;
}
