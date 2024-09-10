#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
class Stack {
private:
    Node<T>* top;
    int count;   

public:
    Stack() : top(nullptr), count(0) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    T getTop() const {
        if (isEmpty()) {
            std::cout << "Empty stack";
            return T(); 
        }
        return top->data;
    }

    //inserta un elemento en la pila
    void push(T value) {
        Node<T>* newNode = new Node<T>();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        count++;
    }

    //remueve el elemento superior de la pila
    void pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty. Cannot pop.\n";
            return;
        }
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        count--;
    }

    //devuelve el tamaño de la pila
    int size() const {
        return count;
    }
};

//ejemplos de implementación
int main() {
    Stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "Top: " << s.getTop() << std::endl;
    std::cout << "Size is: " << s.size() << std::endl;

    s.pop();
    std::cout << "Top luego de pop: " << s.getTop() << std::endl;
    std::cout << "Size luego de pop: " << s.size() << std::endl;

    s.pop();
    s.pop();
    s.pop(); // Intentar hacer pop en una pila vacía

    // Ejemplo con una pila de cadenas
    Stack<std::string> s2; // Pila de strings
    s2.push("Hola");
    s2.push("Mundo");
    std::cout << "Top: " << s2.getTop() << std::endl;

    return 0;
}
