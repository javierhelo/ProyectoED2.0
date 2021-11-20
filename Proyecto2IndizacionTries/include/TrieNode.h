#ifndef TRIENODE_H
#define TRIENODE_H

#include "AVLTreeDictionary.h"
#include "DLinkedList.h"

/**
Clase que representa un nodo de un �rbol trie, sus funciones
son: a�adir una letra, eliminar una letra, obtener el hijo
de un nodo, obtener todos los hijos de un nodo.
Autores: Muricio Avil�s y Paula Bola�os
**/

class TrieNode{
private:
    AVLTreeDictionary<char, TrieNode*> children;

public:
    bool isFinal;
    int prefixCount; //insigned = solo enteros positivos
    DLinkedList<int> *lineas;

    TrieNode() : children(){
        isFinal = false;
        prefixCount = 0;
        lineas = new DLinkedList<int>();
    }
    ~TrieNode(){}   //memoria est�tica, c++ borra children
    bool contains(char c){
        return children.contains(c);
    }
    void add(char c){
        TrieNode *newNode = new TrieNode();
        children.insert(c, newNode);
    }
    void remove(char c){
        //Puede ser que este delete haya que quitarlo
        children.remove(c);
    }
    TrieNode* getChild(char c){
        return children.getValue(c);
    }
    List<char>* getChildren(){
        return children.getKeys();
    }
    List<TrieNode*>* getChildrenPointers(){
        return children.getValues();
    }

};

#endif // TRIENODE_H
