struct Node {
    char data;
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

    char getTop() const {
        if (isEmpty()) {
            std::cout << "Stack is empty. No top element.\n";
            return -1;
        }
        return top->data;
    }

    void push(char value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        count++;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
        count--;
    }
};

class Solution {
public:
    bool isValid(string s) {
        Stack str;
        for(int i = 0; i < s.length(); i++) { 
            char c = s[i];

            if(c == '(' || c == '[' || c == '{') {
                str.push(c);
            } 
            else {
                if (str.isEmpty()) return false; 
                
                if((c == ')' and str.getTop() == '(') or
                   (c == ']' and str.getTop() == '[') or
                   (c == '}' and str.getTop() == '{')) {
                    str.pop();
                } else {
                    return false;
                }
            }        
        }

        if(str.isEmpty()) return 1;

        return false;
    }
};
