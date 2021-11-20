#ifndef AVLTREEDICTIONARY_H
#define AVLTREEDICTIONARY_H

#include "Dictionary.h"
#include "KVPair.h"
#include "AVLTree.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
Clase que representa un diccionario que utiliza la estructura de un AVLTree para
guardar sus elementos, entre sus funciones est�: insertar un elemento al diccionario,
eliminarlo, obtener el valor asociado a una llave, modificar el valor asociado
a una llave, ver si un elemento se encuentra en la estructura, obtener todas las
llaves en el diccionario, obtener todos los valoren en el diccionario, obtener
la cantidad de elementos en la estructura e imprimir sus elementos.
Autor: Manuel Avil�s
**/

template <typename K, typename V>
class AVLTreeDictionary : public Dictionary<K,V>
{
private:
    AVLTree<KVPair<K,V>> elements;

public:

    AVLTreeDictionary(){}

    ~AVLTreeDictionary(){}

    void insert(K key, V value){
        KVPair<K,V> p(key,value);
        elements.insert(p);
    }

    V remove(K key){
        KVPair<K,V> p(key);
        p = elements.remove(p);
        return p.value;
    }

    V getValue(K key){
        KVPair<K,V> p(key);
        p = elements.find(p);
        return p.value;
    }

    void setValue(K key, V value){
        KVPair<K,V> p(key,value);
        elements.remove(p);
        elements.insert(p);
    }

    bool contains(K key){
        KVPair<K,V> p(key);
        return elements.contains(p);
    }

    List<K>* getKeys() {
        List<K> *keys = new DLinkedList<K>();
        List<KVPair<K, V>> *pairs = elements.getElements();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            keys->append(p.key);
        }
        delete pairs;
        return keys;
    }

    List<V>* getValues(){
        List<V> *values = new DLinkedList<V>();
        List<KVPair<K,V>> *pairs = elements.getElements();
        for (pairs -> goToStart(); !pairs -> atEnd(); pairs -> next()){
            KVPair<K,V> p = pairs -> getElement();
            values -> append(p.value);
        }
        delete pairs;
        return values;
    }

    int getSize(){
        return elements.getSize();
    }

    void clear(){
        elements.clear();
    }
    void print() {
        cout << "[ ";
        auto *pairs = elements.getElements();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            auto p = pairs->getElement();
            cout << p.key << ":" << p.value << " ";
        }
        cout << "]" << endl;
    }

};

#endif // AVLTREEDICTIONARY_H
