/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
 
// Implementación manual de una cola
class Queue {
private:
    struct Node {
        NestedInteger value;
        Node* next;
    };
    
    Node* frontNode;
    Node* rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}
    
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    void enqueue(NestedInteger value) {
        Node* newNode = new Node();
        newNode->value = value;
        newNode->next = nullptr;
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }
    
    NestedInteger front() const {
        if (frontNode != nullptr) {
            return frontNode->value;
        }
        // Retorna un valor por defecto si la cola está vacía, se puede mejorar con excepciones.
        return NestedInteger(); 
    }
    
    void dequeue() {
        if (frontNode != nullptr) {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
            if (frontNode == nullptr) {
                rearNode = nullptr;
            }
        }
    }
    
    bool isEmpty() const {
        return frontNode == nullptr;
    }
};

class NestedIterator {
private:
    Queue q;
    
    // Función auxiliar para "desenrollar" la lista anidada y añadir los elementos a la cola.
    void flatten(const vector<NestedInteger>& nestedList) {
        for (int i = 0; i < nestedList.size(); ++i) {
            if (nestedList[i].isInteger()) {
                q.enqueue(nestedList[i]);
            } else {
                flatten(nestedList[i].getList()); // Llamada recursiva para listas anidadas
            }
        }
    }

public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        // Inicializa la cola con la lista anidada aplanada
        flatten(nestedList);
    }
    
    int next() {
        int result = q.front().getInteger();
        q.dequeue();
        return result;
    }
    
    bool hasNext() {
        return !q.isEmpty();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
