#include <iostream>

template <typename T>
struct BSTree {
    struct NodeBT {
        T data;
        NodeBT *left;
        NodeBT *right;

        NodeBT() : left(nullptr), right(nullptr) {}
    };

    NodeBT *root;

    BSTree() : root(nullptr) {}

    ~BSTree() {
        clear(root);
    }

    // BUSCAR
    bool find(NodeBT* node, T value) {
        if (node == nullptr)
            return false;
        if (value < node->data)
            return find(node->left, value);
        else if (value > node->data)
            return find(node->right, value);
        else
            return true;
    }

    bool find(T value) {
        return find(root, value);
    }

    // INSERTAR
    NodeBT* insert(NodeBT* node, T value) {
        if (node == nullptr) {
            node = new NodeBT;
            node->data = value;
            if (root == nullptr) {
                root = node;
            }
            return node;
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    void insert(T value) {
        root = insert(root, value);
    }

    // Obtener el valor mínimo
    NodeBT* getMinValue(NodeBT* node) {
        NodeBT* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    // ELIMINAR
    NodeBT *remove(NodeBT *node, T value) {
        if (node == nullptr)
            return node;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr) {
                NodeBT *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                NodeBT *temp = node->left;
                delete node;
                return temp;
            }
            NodeBT *temp = getMinValue(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    void remove(T value) {
        root = remove(root, value);
    }

    // RECORRIDOS
    void inorder(NodeBT* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    void inorder() {
        inorder(root);
        std::cout << std::endl;
    }

    void preorder(NodeBT* node) {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void preorder() {
        preorder(root);
        std::cout << std::endl;
    }

    void postorder(NodeBT* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }

    void postorder() {
        postorder(root);
        std::cout << std::endl;
    }

    //LIMPIAR/BORRAR TODO
    void clear(NodeBT* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

int main() {
    BSTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    std::cout << "Inorder: ";
    bst.inorder();

    bst.remove(5);
    std::cout << "Inorder after removing 5: ";
    bst.inorder();

    return 0;
}
