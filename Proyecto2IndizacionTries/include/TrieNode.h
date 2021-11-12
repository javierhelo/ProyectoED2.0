#ifndef TRIENODE_H
#define TRIENODE_H

#include "BSTDictionary.h"

class TrieNode{
private:
    BSTDictionary<char, TrieNode*> children;

public:
    bool isFinal;
    int prefixCount; //insigned = solo enteros positivos

    TrieNode() : children(){
        isFinal = false;
        prefixCount = 0;
    }
    ~TrieNode(){}   //memoria estática, c++ borra children
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
