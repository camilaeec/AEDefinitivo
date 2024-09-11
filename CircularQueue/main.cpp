#include <iostream>

using namespace std;

template <typename T>
class CircularQueue {
private:
    int front;      // Índice del frente de la cola
    int rear;       // Índice del final de la cola
    int capacity;   // Capacidad máxima de la cola
    T* arr;         // Arreglo que almacena los elementos

public:
    CircularQueue(int cap) : front(0), rear(0), capacity(cap) {
        arr = new T[cap];
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() const {
        return front == rear;
    }

    bool isFull() const {
        return (rear + 1) % capacity == front;
    }

    void enqueue(T val) {
        if (isFull()) {
            cout << "La cola esta llena, no se puede agregar el elemento." << endl;
            return;
        }

        arr[rear] = val;
        rear = (rear + 1) % capacity;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "La cola esta vacia, no se puede hacer dequeue." << endl;
            return;
        }

        front = (front + 1) % capacity;
    }

    T peek() const {
        if (isEmpty()) {
            cout << "La cola esta vacia." << endl;
            return T(); // Retorna un valor por defecto de tipo T
        }
        return arr[front];
    }

    T back() const {
        if (isEmpty()) {
            cout << "La cola esta vacia." << endl;
            return T(); // Retorna un valor por defecto de tipo T
        }
        return arr[(rear - 1 + capacity) % capacity];
    }

    void print() const {
        if (isEmpty()) {
            cout << "La cola esta vacia." << endl;
            return;
        }

        cout << "Cola Circular: ";
        for (int i = front; i != rear; i = (i + 1) % capacity) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    CircularQueue<int> cq(5);

    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.enqueue(40);
    cq.enqueue(50);

    cq.print();

    cout << "Elemento en el frente: " << cq.peek() << endl;
    cout << "Ultimo elemento: " << cq.back() << endl;

    cq.dequeue();
    cq.dequeue();

    cq.print();

    cq.enqueue(60);
    cq.enqueue(70);

    cq.print();

    cout << "¿Esta la cola llena? " << (cq.isFull() ? "Si" : "No") << endl;

    return 0;
}
