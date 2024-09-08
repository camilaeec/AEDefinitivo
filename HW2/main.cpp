#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    //retorna el elemento al comienzo
    T front() {
        if (empty()) throw std::out_of_range("La lista está vacía");
        return head->data;
    }

    //retorna el elemento al final
    T back() {
        if (empty()) throw std::out_of_range("La lista está vacía");
        return tail->data;
    }

    //agrega un elemento al comienzo
    void push_front(T val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    //agrega un elemento al final
    void push_back(T val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    //remueve el elemento al comienzo
    T pop_front() {
        if (empty()) throw std::out_of_range("La lista está vacía");
        Node* temp = head;
        T val = temp->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        count--;
        return val;
    }

    //remueve el elemento al final
    T pop_back() {
        if (empty()) throw std::out_of_range("La lista está vacía");
        Node* temp = tail;
        T val = temp->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        count--;
        return val;
    }

    //inserta un elemento en cualquier posición
    void insert(T val, int pos) {
        if (pos < 0 || pos > count) throw std::out_of_range("Índice fuera de rango");
        if (pos == 0) {
            push_front(val);
            return;
        } else if (pos == count) {
            push_back(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        count++;
    }

    //remueve un elemento en cualquier posición
    void remove(int pos) {
        if (pos < 0 || pos >= count) throw std::out_of_range("Índice fuera de rango");
        if (pos == 0) {
            pop_front();
            return;
        } else if (pos == count - 1) {
            pop_back();
            return;
        }
        Node* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }

    //retorna el elemento en la posición indicada
    T operator[](int pos) {
        if (pos < 0 || pos >= count) throw std::out_of_range("Índice fuera de rango");
        Node* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->data;
    }

    //retorna si la lista está vacía o no
    bool empty() {
        return count == 0;
    }

    //retorna el tamaño de la lista
    int size() {
        return count;
    }

    //elimina todos los elementos de la lista
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    //revierte la lista
    void reverse() {
        if (empty()) return;
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }
};
