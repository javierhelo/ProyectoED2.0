#ifndef MAXHEAP_H
#define MAXHEAP_H
#include "KVPair.h"
#include "List.h"
#include "ArrayList.h"
#include <stdexcept>

using std::runtime_error;
using namespace std;

/**
Clase que representa un maxHeap, entre sus funciones esta:
insertar un valor, obtener el valor que est� de primero,
eliminar un elemento, eliminar el primer elemento,
obtener el tama�o de la estructura, determinar si la estructura
est� vac�a e imprimir la estructura.
Autores: Mauricio Avil�s y Paula Bola�os
**/

template <typename K, typename V>
class MaxHeap{
private:
    KVPair<K,V> *elements;
    int max;
    int size;

    int leftChild(int pos){
        return 2 * pos + 1;
    }
    int rightChild(int pos){
        return 2 * pos + 2;
    }
    int parent(int pos){
        return (pos - 1) / 2;
    }
    bool isLeaf(int pos){
        return leftChild(pos) >= size;
    }
    void swap(int pos1, int pos2){
        KVPair<K,V> temp = elements[pos1];
        elements[pos1] = elements[pos2];
        elements[pos2] = temp;
    }
    void siftUp(int pos){
        while (pos != 0 && elements[pos].value > elements[parent(pos)].value){
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }
    void siftDown(int pos){
        while (!isLeaf(pos) && elements[greaterChild(pos)].value > elements[pos].value){
            int child = greaterChild(pos);
            swap(pos, child);
            pos = child;
        }
    }
    int greaterChild(int pos){
        if (rightChild(pos) >= size || elements[leftChild(pos)].value > elements[rightChild(pos)].value)
            return leftChild(pos);
        return rightChild(pos);
    }

public:
    MaxHeap(int max = 100000){
        if (max < 1)
            throw runtime_error("Max size must be positive");
        elements = new KVPair<K,V>[max];
        this->max = max;
        size = 0;
    }
    ~MaxHeap(){
        delete [] elements;
    }
    void insert(K key, V value) {
        KVPair<K, V> p(key, value);
        if (size == max)
            throw runtime_error("Heap is full");
        elements[size] = p;
        siftUp(size);
        size++;
    }
    KVPair<K,V> first(){
        if (size==0)
            throw runtime_error("Heap is empty");
        return elements[0];
    }
    KVPair<K,V> remove(int pos){
        if (size==0)
            throw runtime_error("Heap is empty");
        if (pos < 0 || pos >= size)
            throw runtime_error("Index out of range");
        size--;
        swap(pos, size);
        if (size > 0)
            siftDown(pos);
        return elements[size];
    }
    KVPair<K,V> removeFirst(){
        return remove(0);
    }
    int getSize(){
        return size;
    }
    bool isEmpty(){
        return size==0;
    }
    void printArray(int n){
        for (int i = 0; i < n; i++)
            cout << i+1 << ". " << elements[i] << endl;
    }
};
#endif // MAXHEAP_H
