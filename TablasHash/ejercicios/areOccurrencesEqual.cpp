#include <iostream>

class HashTableOpenAddressing {
private:
    char* keys;
    int* values;
    int* status; // 0=empty, 1=occupied, 2=deleted
    int capacity;
    int size;

    int hash(char key, int cap) {
        return key % cap; 
    }

    int probe(int hashValue, int step, int cap) {
        return (hashValue + step) % cap;
    }

    void resize() {
        int newCapacity = capacity * 2;
        char* newKeys = new char[newCapacity];
        int* newValues = new int[newCapacity];
        int* newStatus = new int[newCapacity];

        for (int i = 0; i < newCapacity; i++) {
            newStatus[i] = 0;
        }

        for (int i = 0; i < capacity; i++) {
            if (status[i] == 1) {
                int hashValue = hash(keys[i], newCapacity);
                int step = 0;
                while (newStatus[hashValue] == 1) {
                    hashValue = probe(hashValue, ++step, newCapacity);
                }
                newKeys[hashValue] = keys[i];
                newValues[hashValue] = values[i];
                newStatus[hashValue] = 1;
            }
        }

        //borrar la antigua y reemplazar por la nueva
        delete[] keys;
        delete[] values;
        delete[] status;

        keys = newKeys;
        values = newValues;
        status = newStatus;
        capacity = newCapacity;
    }

public:
    HashTableOpenAddressing(int cap) : capacity(cap), size(0) {
        keys = new char[capacity];
        values = new int[capacity];
        status = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            status[i] = 0;
        }
    }

    ~HashTableOpenAddressing() {
        delete[] keys;
        delete[] values;
        delete[] status;
    }

    void insert(char key, int value) {
        if (size >= capacity * 0.7) { //resize al 70%
            resize();
        }

        int hashValue = hash(key, capacity);
        int step = 0;

        while (status[hashValue] == 1) {
            if (keys[hashValue] == key) {
                values[hashValue] = value;  //actualizar si existe
                return;
            }
            hashValue = probe(hashValue, ++step, capacity);
        }

        keys[hashValue] = key;
        values[hashValue] = value;
        status[hashValue] = 1;
        size++;
    }

    int* search(char key) {
        int hashValue = hash(key, capacity);
        int step = 0;
        while (status[hashValue] != 0) {
            if (status[hashValue] == 1 && keys[hashValue] == key) {
                return &values[hashValue];
            }
            hashValue = probe(hashValue, ++step, capacity);
        }
        return nullptr;
    }
};

class Solution {
public:
    bool areOccurrencesEqual(std::string s) {
        HashTableOpenAddressing hashTable(26); //sin n con sombrero
        
        for (char c : s) {
            int* count = hashTable.search(c);
            if (count != nullptr) {
                (*count)++;
            } else {
                hashTable.insert(c, 1);
            }
        }

        //verificar si todas las ocurrencias son iguales
        int* firstCount = nullptr;
        for (char c : s) {
            int* count = hashTable.search(c);
            if (firstCount == nullptr) {
                firstCount = count;
            } else if (*count != *firstCount) {
                return false;
            }
        }

        return true;
    }
};
