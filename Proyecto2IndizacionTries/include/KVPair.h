#ifndef KVPAIR_H
#define KVPAIR_H

#include <iostream>

using std::ostream;

template <typename K, typename V>
class KVPair {
public:
    K key;
    V value;

    KVPair(){}
    KVPair(K key){
        this->key = key;
    }
    KVPair(K key, V value){
        this->key = key;
        this->value = value;
    }
    void operator=(const KVPair& other){
        this->key = other.key;
        this->value = other.value;
    }
    bool operator==(const KVPair& other){
        return this->key == other.key;
    }
    bool operator!=(const KVPair& other){
        return this->key != other.key;
    }
    bool operator<(const KVPair& other){
        return this->key < other.key;
    }
    bool operator<=(const KVPair& other){
        return this->key <= other.key;
    }
    bool operator>(const KVPair& other){
        return this->key > other.key;
    }
    bool operator>=(const KVPair& other){
        return this->key >= other.key;
    }

};
// Esta función "solitaria" sirve para sobrescribir el funcionamiento
// del operador << con el KVPair.
// Aparentemente no se puede sobrescribir desde dentro de la clase
// y hay que hacerlo en una función aparte.
template<typename K, typename V>
ostream& operator<<(ostream& os, const KVPair<K, V>& p) {
    os << p.key << ":" << p.value;
    return os;
}

#endif // KVPAIR_H
