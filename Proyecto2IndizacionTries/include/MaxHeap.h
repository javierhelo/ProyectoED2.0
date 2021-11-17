#ifndef MAXHEAP_H
#define MAXHEAP_H
#define DEFAULT_MAX_SIZE 1024
#include "KVPair.h"
#include "List.h"
#include "ArrayList.h"
#include <stdexcept>

using std::runtime_error;
using namespace std;

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
        if (rightChild(pos) <= size || elements[leftChild(pos)].value > elements[rightChild(pos)].value)
            return leftChild(pos);
        return rightChild(pos);
    }

public:
    MaxHeap(int max = DEFAULT_MAX_SIZE){
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
    void printArray(){
        for (int i = 0; i < size; i++)
            cout << elements[i] << " ";
        cout << endl;
    }
    List<KVPair<K,V>>* removeTop(int n){
        if (n > size)
            throw runtime_error("n is higher than size of the heap");
        if (n < 0)
            throw runtime_error("n is 0 or a negative number");
        List<KVPair<K,V>> *A = new ArrayList<KVPair<K,V>>;
        for (int i = 0; i < n; i++){
            A->append(elements[0]);
            removeFirst();
        }
        return A;
    }
};
#endif // MAXHEAP_H
