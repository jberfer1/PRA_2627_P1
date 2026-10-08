#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <iostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    // Constructor
    ListLinked() {
        first = nullptr;
        n = 0;
    }

    // Destructor
    ~ListLinked() override {
        while (first != nullptr) {
            Node<T>* aux = first->next; // 1. aux apunta al siguiente
            delete first;               // 2. Liberar memoria de first
            first = aux;                // 3. Actualizar first
        }                               // 4. Repetir hasta el final
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición fuera de rango");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream &out, ListLinked<T> &list) {
        out << "[";
        Node<T>* current = list.first;
        while (current != nullptr) {
            out << current->data;
            if (current->next != nullptr) {
                out << ", ";
            }
            current = current->next;
        }
        out << "]";
        return out;
    }

    // ---- Métodos heredados de la interfaz List<T> ----

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Posición fuera de rango");
        }
        if (pos == 0) {
            // Insertar al principio
            first = new Node<T>(e, first);
        } else {
            // Insertar en medio o al final
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            prev->next = new Node<T>(e, prev->next);
        }
        n++;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición fuera de rango");
        }
        
        Node<T>* aux = first;
        T removed_data;

        if (pos == 0) {
            // Eliminar el primer elemento
            first = first->next;
            removed_data = aux->data;
            delete aux;
        } else {
            // Eliminar en medio o al final
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            aux = prev->next;
            prev->next = aux->next; // Saltamos el nodo a eliminar
            removed_data = aux->data;
            delete aux;
        }
        n--;
        return removed_data;
    }

    T get(int pos) override {
        return (*this)[pos]; // Reutilizamos el operador []
    }

    int search(T e) override {
        Node<T>* current = first;
        int pos = 0;
        while (current != nullptr) {
            if (current->data == e) {
                return pos;
            }
            current = current->next;
            pos++;
        }
        return -1;
    }

    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }
};

#endif
