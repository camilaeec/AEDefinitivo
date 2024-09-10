#include <iostream>

struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* top;
    int count;

public:
    Stack() : top(nullptr), count(0) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    int getTop() const {
        if (isEmpty()) {
            std::cout << "Stack is empty. No top element.\n";
            return -1;
        }
        return top->data;
    }

    //inserts an element into the stack
    void push(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        count++;
    }

    //removes the top element from the stack
    void pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty. Cannot pop.\n";
            return;
        }
        Node *temp = top;
        top = top->next;
        delete temp;
        count--;
    }

    //is full
    int size() const {
        return count;
    }
};

//ejemplos de implementacion
int main() {
    Stack s;

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
    s.pop();

    return 0;
}
