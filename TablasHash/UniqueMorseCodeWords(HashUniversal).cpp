#include <iostream>
#include <string>
using namespace std;

// Implementación de una lista enlazada simple (ForwardList) para manejo de colisiones (chaining)
class ForwardList {
private:
    struct Node {
        string data;
        Node* next;
        Node(string data) : data(data), next(nullptr) {}
    };

    Node* head;

    // Hacemos a Solution amiga para que pueda acceder a Node
    friend class Solution;

public:
    // Constructor
    ForwardList() : head(nullptr) {}

    // Destructor
    ~ForwardList() {
        clear();
    }

    // Insertar al inicio de la lista
    void insert(string value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Buscar un valor en la lista
    bool search(string value) const {
        Node* current = head;
        while (current) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    // Vaciar la lista
    void clear() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    // Obtener el puntero al primer nodo (para rehashing)
    Node* getHead() const {
        return head;
    }
};

// Clase de la Tabla Hash (llamada Solution)
class Solution {
private:
    int p; // Número primo mayor que las claves posibles
    int a, b; // Coeficientes de la función hash
    int m; // Tamaño de la tabla

    double fillFactor;
    double maxFactor;

    ForwardList* table; // Array de listas enlazadas
    int numElements; // Número de elementos en la tabla

    // Función hash universal
    int hash(const string& key) const {
        int hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % p; 
        }
        return ((a * hashValue + b) % p) % m;
    }

    // Función para redimensionar la tabla (rehashing)
    void resize() {
        int old_m = m;
        m = 2 * m;  // Duplicar el tamaño de la tabla
        ForwardList* newTable = new ForwardList[m]; // Nueva tabla

        // Reinsertar los elementos en la nueva tabla
        for (int i = 0; i < old_m; ++i) {
            ForwardList& oldList = table[i]; 
            ForwardList::Node* current = oldList.getHead();
            while (current) {
                string data = current->data;
                int newIndex = hash(data);
                newTable[newIndex].insert(data); 
                current = current->next;
            }
        }

        // Liberar la tabla vieja
        delete[] table;
        table = newTable;
    }

public:
    // Constructor de la tabla hash
    Solution(int initial_size = 10, double max_factor = 0.75) {
        srand(time(0));
        p = 997; // Número primo
        a = rand() % (p - 1) + 1;
        b = rand() % p;
        m = initial_size;
        maxFactor = max_factor;
        fillFactor = 0;
        numElements = 0;
        table = new ForwardList[m];
    }

    ~Solution() {
        clear();
        delete[] table;
    }

    void insert(const string& key) {
        int index = hash(key);
        table[index].insert(key);
        numElements++;

        fillFactor = (double)numElements / m;

        if (fillFactor > maxFactor) {
            resize();  // Redimensionar cuando se excede el factor de llenado
        }
    }

    bool search(const string& key) const {
        int index = hash(key);
        return table[index].search(key);
    }

    void clear() {
        for (int i = 0; i < m; ++i) {
            table[i].clear();
        }
        numElements = 0;
        fillFactor = 0;
    }

    int size() const {
        return numElements;
    }

    int uniqueMorseRepresentations(vector<string>& words) {
        string morseCode[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", 
                                "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", 
                                "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", 
                                "-.--", "--.."};

        Solution morseTable(10, 0.75); 

        for (const string& word : words) {
            string morseTransformation = "";
            for (char c : word) {
                morseTransformation += morseCode[c - 'a'];
            }
            
            if (!morseTable.search(morseTransformation)) {
                morseTable.insert(morseTransformation);
            }
        }
        return morseTable.size();
    }
};