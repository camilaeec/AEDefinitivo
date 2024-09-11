#include <iostream>

using namespace std;

// Definimos un nodo genérico usando plantillas
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

// Implementación de la cola usando plantillas
template <typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;
    int capacity; // Capacidad máxima de la cola

public:
    // Constructor
    Queue(int cap) : front(nullptr), rear(nullptr), size(0), capacity(cap) {}

    // Verifica si la cola está vacía
    bool isEmpty() {
        return front == nullptr;
    }

    // Verifica si la cola está llena
    bool isFull() {
        return size == capacity;
    }

    // Agrega un elemento al final de la cola
    void enqueue(T val) {
        if (isFull()) {
            cout << "La cola está llena, no se puede agregar el elemento." << endl;
            return;
        }

        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Elimina un elemento del frente de la cola
    void dequeue() {
        if (isEmpty()) {
            cout << "La cola está vacía, no se puede hacer dequeue." << endl;
            return;
        }
        Node<T>* temp = front;
        front = front->next;
        delete temp;
        size--;

        if (front == nullptr) {
            rear = nullptr;
        }
    }

    // Muestra el elemento en el frente de la cola
    T peek() {
        if (isEmpty()) {
            cout << "La cola está vacía." << endl;
            return T();
        }
        return front->data;
    }

    // Muestra el último elemento de la cola sin eliminarlo
    T back() {
        if (isEmpty()) {
            cout << "La cola está vacía." << endl;
            return T();
        }
        return rear->data;
    }

    // Retorna el tamaño de la cola
    int getSize() {
        return size;
    }

    // Limpia todos los elementos de la cola
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Verifica si un elemento está en la cola
    bool contains(T val) {
        Node<T>* temp = front;
        while (temp != nullptr) {
            if (temp->data == val) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Imprime todos los elementos de la cola
    void print() {
        if (isEmpty()) {
            cout << "La cola está vacía." << endl;
            return;
        }

        Node<T>* temp = front;
        cout << "Cola: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor para liberar memoria
    ~Queue() {
        clear();
    }
};

int main() {
    // Creamos una cola con capacidad de 3 elementos
    Queue<int> q(3);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.print(); // Imprime la cola

    cout << "Elemento en el frente: " << q.peek() << endl;
    cout << "Último elemento: " << q.back() << endl;

    cout << "¿Está la cola llena? " << (q.isFull() ? "Sí" : "No") << endl;

    q.enqueue(40); // Intento de agregar un cuarto elemento, no se debe permitir

    q.dequeue();
    q.print(); // Imprime la cola después del dequeue

    cout << "¿Está la cola llena? " << (q.isFull() ? "Sí" : "No") << endl;

    return 0;
}
