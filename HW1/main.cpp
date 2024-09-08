#include <iostream>

// nodo de la lista con template
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

// forwardList/lista enlazada
template <typename T>
class forwardList {
private:
    Node<T>* head; // puntero al inicio de la lista
    int listSize;

    // funciones aux para merge sort
    Node<T>* merge(Node<T>* left, Node<T>* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data <= right->data) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next);
            return right;
        }
    }

    Node<T>* split(Node<T>* start) {
        Node<T>* slow = start;
        Node<T>* fast = start->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node<T>* mid = slow->next;
        slow->next = nullptr;
        return mid;
    }

    Node<T>* mergeSort(Node<T>* start) {
        if (!start || !start->next) return start;

        Node<T>* mid = split(start);
        Node<T>* left = mergeSort(start);
        Node<T>* right = mergeSort(mid);

        return merge(left, right);
    }

public:
    forwardList() : head(nullptr), listSize(0) {}

    ~forwardList() {
        clear();
    }

    // front_ elemento del inicio
    T front() const {
        if (!head) throw std::runtime_error("La lista está vacía");
        return head->data;
    }

    // back_ último elemento
    T back() const {
        if (!head) throw std::runtime_error("La lista está vacía");

        Node<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp->data;
    }

    // método push_front
    void push_front(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;

        listSize++;
    }

    // método push_back
    void push_back(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        listSize++;
    }

    // pop_front
    T pop_front() {
        if (!head) throw std::runtime_error("La lista está vacía");

        Node<T>* temp = head;
        T val = temp->data;
        head = head->next;
        delete temp;

        listSize--;
        return val;
    }

    // pop_back
    T pop_back() {
        if (!head) throw std::runtime_error("La lista está vacía");

        if (!head->next) {
            T val = head->data;
            delete head;
            head = nullptr;
            listSize--;
            return val;
        }

        Node<T>* temp = head;
        while (temp->next && temp->next->next) {
            temp = temp->next;
        }
        T val = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        listSize--;
        return val;
    }

    // elemento en posición dentro de []
    T operator[](int index) const {
        if (index < 0 || index >= listSize) throw std::out_of_range("Índice fuera del rango");
        Node<T>* temp = head;

        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    // método empty/lista vacía
    bool empty() const {
        return head == nullptr;
    }

    // método size/tamaño de la lista
    int size() const {
        return listSize;
    }

    // método clear/elimina todos los elementos
    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }

    // Método para ordenar la lista usando Merge Sort
    void sort() {
        if (!head || !head->next) return; // Lista vacía o con un solo elemento ya está ordenada
        head = mergeSort(head);
    }

    // Ordena la lista usando el algoritmo Bubble Sort
    
    void bubble_sort(){
        if(empty() || head->next == nullptr){
            return;
        }
        
        bool swapped;
        do{
            swapped = false;
            Node<T>* current = head;
            
            while(current->next != nullptr){
                if(current->data > current->next->data){
                    // Intercambiar los valores
                    swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        }while(swapped);
    }
    
    
    // método print/imprime la lista
    void print() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};
