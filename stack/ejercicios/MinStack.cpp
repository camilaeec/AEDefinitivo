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

    void push(T value) {
        Node<T>* newNode = new Node<T>();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        count++;
    }

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

    int size() const {
        return count;
    }
};

class MinStack {
private:
    Stack<int> stack;
    Stack<int> minStack;

public:
    MinStack() {}

    void push(int val) {
        mainStack.push(val);

        //push min value to minStack
        if (minStack.isEmpty() or val <= minStack.getTop()) {
            minStack.push(val);
        } else {
            minStack.push(minStack.getTop());
        }
    }
    
    void pop() {
        if (!stack.isEmpty()) {
            stack.pop();
            minStack.pop();
        }
    }

    int top() {
        return stack.getTop();
    }
    
    int getMin() {
        return minStack.getTop();
    }
};
