#ifndef BSTDICTIONARY_H
#define BSTDICTIONARY_H

#include <stdexcept>
#include <iostream>
#include "Dictionary.h"
#include "BSTree.h"
#include "DLinkedList.h"
#include "KVPair.h"

using std::runtime_error;
using std::cout;
using std::endl;            //

template <typename K, typename V>
class BSTDictionary : public Dictionary<K, V>{
private:
    BSTree<KVPair<K, V>> elements; //como esta en estática se construye y destruye solo

public:
    BSTDictionary() : elements(){} //cuando se ejecuta el constructor de dictionary se ejecuta el de elements
    ~BSTDictionary(){}
    void insert(K key, V value) {
        KVPair<K, V> p(key, value);
        elements.insert(p);
    }
    V remove(K key){
        KVPair<K, V> p(key);
        p = elements.remove(p);
        return p.value;
    }
    V getValue(K key){
        KVPair<K, V> p(key);
        p = elements.find(p);
        return p.value;
    }
    void setValue(K key, V value){
        KVPair<K, V> p(key, value);
        elements.remove(p);
        elements.insert(p);
    }
    bool contains(K key){
        KVPair<K, V> p(key);
        return elements.contains(p);
    }
    List<K>* getKeys(){
        List<K> *keys = new DLinkedList<K>(); //Como declaramos que es se usa auto
        List<KVPair<K, V>> *pairs = elements.getElements(); //auto = List<KVPair<K, V>>
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            KVPair<K, V> p = pairs->getElement();
            keys->append(p.key);
        }
        //getelements crea lista en memoria dinamica por lo tanto:
        delete pairs;
        return keys;
    }
    List<V>* getValues(){
        List<V> *values = new DLinkedList<V>();
        List<KVPair<K, V>> *pairs = elements.getElements();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            KVPair<K, V> p = pairs->getElement();
            values->append(p.value);
        }
        delete pairs;
        return values;
    }
    int getSize(){
        return elements.getSize();
    }
    void print(){
        cout << "[ ";
        auto *pairs = elements.getElements();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            auto p = pairs->getElement();
            cout << p.key << ":" << p.value << " ";
        }
        cout << "]" << endl;
    }

};

#endif // BSTDICTIONARY_H
