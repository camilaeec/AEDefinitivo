#include <iostream>

using namespace std;

// Implementación de una lista enlazada simple (forward list) para manejo de colisiones (chaining)
template<typename T>
class ForwardList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node* head;

public:
    // Constructor
    ForwardList() : head(nullptr) {}

    // Destructor
    ~ForwardList() {
        clear();
    }

    // Insertar al inicio de la lista
    void insert(T value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Buscar un valor en la lista
    bool search(T value) const {
        Node* current = head;
        while (current) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    // Eliminar un valor de la lista
    void remove(T value) {
        Node* current = head;
        Node* prev = nullptr;
        while (current) {
            if (current->data == value) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
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

    // Imprimir la lista (para depuración)
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

// Clase template de Tabla Hash
template<typename T>
class HashTable {
private:
    // Parámetros de la función hash universal
    int p; // Número primo mayor que las claves posibles
    int a, b; // Coeficientes de la función hash
    int m; // Tamaño de la tabla

    // Factor de llenado y factor máximo
    double fillFactor;
    double maxFactor;

    // Tabla de hash con manejo de colisiones usando ForwardList
    ForwardList<T>* table; // Array de listas enlazadas
    int numElements; // Número de elementos en la tabla

    // Función hash universal
    int hash(const T& key) const {
        return ((a * key + b) % p) % m;
    }

    // Función para redimensionar la tabla (rehashing)
    void resize() {
        // Duplicar el tamaño de la tabla
        int new_m = 2 * m;
        ForwardList<T>* newTable = new ForwardList<T>[new_m];

        // Generar nuevos coeficientes para la función hash universal
        a = rand() % (p - 1) + 1; // a ∈ [1, p-1]
        b = rand() % p;           // b ∈ [0, p-1]
        m = new_m;

        // Reinsertar todos los elementos en la nueva tabla
        for (int i = 0; i < m / 2; ++i) {
            // Recorrer la lista en cada bucket y reinsertar los elementos
            table[i].clear(); // Los elementos serán reinserados en la nueva tabla
        }

        // Liberar la memoria de la tabla vieja
        delete[] table;
        table = newTable;
    }

public:
    // Constructor de la tabla hash
    HashTable(int initial_size, double max_factor) {
        srand(time(0)); // Inicializa semilla aleatoria para los coeficientes
        p = 997; // Número primo mayor para la función hash
        a = rand() % (p - 1) + 1; // a ∈ [1, p-1]
        b = rand() % p;           // b ∈ [0, p-1]
        m = initial_size;
        maxFactor = max_factor;
        fillFactor = 0;
        numElements = 0;
        table = new ForwardList<T>[m];
    }

    // Destructor para liberar memoria
    ~HashTable() {
        clear();
        delete[] table;
    }

    // Insertar un elemento en la tabla hash
    void insert(const T& key) {
        int index = hash(key);
        table[index].insert(key);
        numElements++;

        // Actualizar el factor de llenado
        fillFactor = (double)numElements / m;

        // Redimensionar la tabla si el factor de llenado excede el máximo
        if (fillFactor > maxFactor) {
            resize();
        }
    }

    // Buscar un elemento en la tabla hash
    bool search(const T& key) const {
        int index = hash(key);
        return table[index].search(key);
    }

    // Eliminar un elemento de la tabla hash
    void remove(const T& key) {
        int index = hash(key);
        table[index].remove(key);
        numElements--;
    }

    // Vaciar la tabla hash
    void clear() {
        for (int i = 0; i < m; ++i) {
            table[i].clear();
        }
        numElements = 0;
        fillFactor = 0;
    }

    // Imprimir el contenido de la tabla hash (para depuración)
    void print() const {
        for (int i = 0; i < m; ++i) {
            cout << "Bucket " << i << ": ";
            table[i].print();
        }
    }

    // Obtener el número de elementos en la tabla
    int size() const {
        return numElements;
    }

    // Obtener el factor de llenado actual
    double getFillFactor() const {
        return fillFactor;
    }
};

// Función main para probar la tabla hash
int main() {
    // Crear una tabla hash con tamaño inicial de 10 y un factor máximo de 0.75
    HashTable<int> ht(10, 0.75);

    // Insertar elementos en la tabla hash
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(25);
    ht.insert(35);
    ht.insert(45);

    // Imprimir el contenido de la tabla
    ht.print();

    // Buscar elementos en la tabla hash
    cout << "Buscar 30: " << (ht.search(30) ? "Encontrado" : "No Encontrado") << endl;

    // Eliminar un elemento
    ht.remove(30);
    ht.print();

    // Vaciar la tabla
    ht.clear();
    ht.print();

    return 0;
}
