#include<iostream>

const int MAX_STACK_SIZE = 100;
const int MAX_Q_SIZE = 100;

using namespace std;

template <typename T>
class Stack {
private:
    T list[MAX_STACK_SIZE];
    int top_index;

public:
    Stack() : top_index(-1) {}

    bool isFull() const {
        return top_index >= MAX_STACK_SIZE - 1;
    }

    bool isEmpty() const {
        return top_index == -1;
    }

    T top() {
        if (isEmpty()) throw runtime_error("Cannot access top. Stack is empty.");
        return list[top_index];
    }

    void push(T e) {
        if (isFull()) throw runtime_error("Cannot push. Stack is full.");
        list[++top_index] = e;
    }

    T pop() {
        if (isEmpty()) throw runtime_error("Cannot pop. Stack is empty.");
        return list[top_index--];
    }

    int size() const {
        return top_index + 1;
    }
};

template <typename T>
class Queue {
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    Queue() : front_index(0), rear_index(0) {}

    bool isFull() const {
        return front_index == (rear_index + 1) % MAX_Q_SIZE;
    }

    bool isEmpty() const {
        return front_index == rear_index;
    }

    T front() {
        if (isEmpty()) throw runtime_error("Cannot access front. Queue is empty.");
        return list[(front_index + 1) % MAX_Q_SIZE];
    }

    void enqueue(T e) {
        if (isFull()) throw runtime_error("Cannot enqueue. Queue is full.");
        rear_index = (rear_index + 1) % MAX_Q_SIZE;
        list[rear_index] = e;
    }

    T dequeue() {
        if (isEmpty()) throw runtime_error("Cannot dequeue. Queue is empty.");
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return list[front_index];
    }

    int size() const {
        return (rear_index - front_index + MAX_Q_SIZE) % MAX_Q_SIZE;
    }
};

template<typename T>
class BinaryTree{
private:
    struct Node{
        T data;
        Node* left;
        Node* right;

        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };   

    Node* root;

    void clear(Node* node) {
        if (node == nullptr) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

    bool find(Node* node, T value){
        if(node == nullptr) return false;
        else if(value < node->data) return find(node->left, value);
        else if(value > node->data) return find(node->right, value);
        else return true;
    }

    Node* insertBST(Node* node, T value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertBST(node->left, value);
        } else if (value > node->data) {
            node->right = insertBST(node->right, value);
        }

        return node;
    }

    Node* insertBT(Node* node, T value) {
        // Si el árbol está vacío, crea un nuevo nodo y lo convierte en raíz
        if (node == nullptr) {
            return new Node(value);
        }

        Queue<Node*> q;  // Usamos una cola para el recorrido por niveles
        q.enqueue(node); // Comenzamos con la raíz

        while (!q.isEmpty()) {
            Node* temp = q.front();  // Obtiene el nodo frontal
            q.dequeue();             // Lo saca de la cola

            // Si el nodo izquierdo está vacío, inserta el nuevo nodo allí
            if (temp->left == nullptr) {
                temp->left = new Node(value);
                return node; // Retorna la raíz original
            } else {
                q.enqueue(temp->left); // Agrega el nodo izquierdo a la cola
            }

            // Si el nodo derecho está vacío, inserta el nuevo nodo allí
            if (temp->right == nullptr) {
                temp->right = new Node(value);
                return node; // Retorna la raíz original
            } else {
                q.enqueue(temp->right); // Agrega el nodo derecho a la cola
            }
        }

        return node; // Retorna la raíz original
    }

    Node* getMinValue(Node* node) {
        if(node == nullptr) return nullptr;
        else if (node->left == nullptr) return node;
        return getMinValue(node->left);
    }

    Node* getMaxValue(Node* node) {
        if(node == nullptr) return nullptr;
        else if (node->right == nullptr) return node;
        return getMaxValue(node->right);
    }

    Node* remove(Node* node, T value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = getMinValue(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    void preOrder(Node* node) {
        if (node == nullptr) return;

        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node* node) {
        if (node == nullptr) return;

        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == nullptr) return;

        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    int depth(Node* node) {
        if(node == nullptr) {
            return 0;
        } else {
            int left_depth = depth(node->left);
            int right_depth = depth(node->right);
            return max(left_depth, right_depth) + 1;
        }
    }

    Node* findParent(Node* node, Node* child) {
        if (node == nullptr || node == child) return nullptr;

        if (node->left == child || node->right == child) {
            return node;
        }

        if (child->data < node->data) {
            return findParent(node->left, child);
        } else {
            return findParent(node->right, child);
        }
    }

    Node* getPredecessor(Node* node) {
        if (node == nullptr) return nullptr;

        // Caso 1: Si hay subárbol izquierdo, el predecesor es el máximo valor de ese subárbol
        if (node->left != nullptr) {
            return getMaxValue(node->left);
        }

        // Caso 2: Si no hay subárbol izquierdo, buscar en los ancestros
        Node* ancestor = root;
        Node* predecessor = nullptr;

        while (ancestor != node) {
            if (node->data > ancestor->data) {
                predecessor = ancestor;
                ancestor = ancestor->right;
            } else {
                ancestor = ancestor->left;
            }
        }
        return predecessor;
    }

    Node* getSuccessor(Node* node) {
        if (node == nullptr) return nullptr;

        // Caso 1: Si hay subárbol derecho, el sucesor es el valor mínimo de ese subárbol
        if (node->right != nullptr) {
            return getMinValue(node->right);
        }

        // Caso 2: Si no hay subárbol derecho, buscar en los ancestros
        Node* ancestor = root;
        Node* successor = nullptr;

        while (ancestor != node) {
            if (node->data < ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }

    Node* findNode(Node* node, T value) {
        if (node == nullptr) return nullptr;
        if (value < node->data) return findNode(node->left, value);
        else if (value > node->data) return findNode(node->right, value);
        else return node;
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        clear(root);
    }

    bool find(T value) {
        return find(root, value);
    }

    void insertBST(T value) {
        root = insertBST(root, value);
    }

    void insertBT(T value) {
        root = insertBT(root, value);
    }

    T getMinValue() {
        Node* node = getMinValue(root);
        if (node == nullptr) throw runtime_error("Tree is empty.");
        return node->data;
    }

    T getMaxValue() {
        Node* node = getMaxValue(root);
        if (node == nullptr) throw runtime_error("Tree is empty.");
        return node->data;
    }

    void remove(T value) {
        root = remove(root, value);
    }

    void preOrder() {
        preOrder(root);
        cout << endl;
    }

    void inOrder() {
        inOrder(root);
        cout << endl;
    }

    void postOrder() {
        postOrder(root);
        cout << endl;
    }

    void breadthFirstSearch() {
        Queue<Node*> q;
        q.enqueue(this->root);

        while(!q.isEmpty()) {
            Node* node = q.dequeue();
            cout << node->data << " ";

            if(node->left != nullptr) {
                q.enqueue(node->left);
            }
            if(node->right != nullptr) {
                q.enqueue(node->right);
            }
        }
        cout << endl;
    }

    void depthFirstSearch() {
        Stack<Node*> stack;
        stack.push(this->root);

        while(!stack.isEmpty()) {
            Node* node = stack.pop();
            cout << node->data << " ";

            if(node->right != nullptr) {
                stack.push(node->right);
            }

            if(node->left != nullptr) {
                stack.push(node->left);
            }
        }
        cout << endl;
    }

    int depth() {
        return depth(root);
    }

    T getPredecessor(T value) {
        Node* node = findNode(root, value);
        Node* predNode = getPredecessor(node);
        if (predNode == nullptr) throw runtime_error("Predecessor not found.");
        return predNode->data;
    }

    T getSuccessor(T value) {
        Node* node = findNode(root, value);
        Node* succNode = getSuccessor(node);
        if (succNode == nullptr) throw runtime_error("Successor not found.");
        return succNode->data;
    }

    void clear() {
        clear(root);
        root = nullptr; 
    }

};

int main(){
    BinaryTree<int> bst;
    bst.insertBST(20);
    bst.insertBST(10);
    bst.insertBST(30);
    bst.insertBST(5);
    bst.insertBST(15);

    cout << "In-order Traversal: ";
    bst.inOrder();

    bst.breadthFirstSearch();
    bst.depthFirstSearch();

    cout << "Predecessor of 15: " << bst.getPredecessor(15) << endl;
    cout << "Successor of 15: " << bst.getSuccessor(15) << endl;

    cout << "Minimum Value: " << bst.getMinValue() << endl;
    cout << "Maximum Value: " << bst.getMaxValue() << endl;

    cout << "Depth: " << bst.depth() << endl;

    if (bst.find(1) == true) cout << "Encontrado";
    else cout << "No encontrado";

}