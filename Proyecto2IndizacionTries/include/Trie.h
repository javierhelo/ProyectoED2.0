#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>
#include <stdexcept>
#include "TrieNode.h"

using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

class Trie{
private:
    TrieNode *root;

    void clearAux(TrieNode *current){
        List<TrieNode*> *pointers = current->getChildrenPointers();
        for (pointers->goToStart(); !pointers->atEnd(); pointers->next()){
            clearAux(pointers->getElement());
        }
    }

    void getMatchesAux (TrieNode *current, string prefix, List<string> *words){
        if (current->isFinal)
            words->append(prefix);
        List<char> *children = current->getChildren();
        for (children->goToStart(); !children->atEnd(); children->next()){
            char c = children->getElement();
            string newPrefix = prefix;
            newPrefix.append(1, c);
            getMatchesAux(current->getChild(c), newPrefix, words);
        }
        delete children;
    }

public:
    Trie(){
        root = new TrieNode(); //invocamos al constructor de TrieNode
    }
    ~Trie(){
        clear();
        delete root;
    }
    void insert(string word){
        if (containsWord(word))
            throw runtime_error("Word already in trie.");
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++){
            current->prefixCount++;
            if (!current->contains(word[i]))
                current->add(word[i]);
            current = current->getChild(word[i]);
        }
        current->prefixCount++;
        current->isFinal = true;
    }
    bool containsWord(string word){
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++){
            if (!current->contains(word[i]))
                return false;
            current = current->getChild(word[i]);
        }
        return current->isFinal;
    }
    bool containsPrefix(string prefix){
        TrieNode *current = root;
        for (unsigned int i = 0; i < prefix.size(); i++){
            if (!current->contains(prefix[i]))
                return false;
            current = current->getChild(prefix[i]);
        }
        return true;
    }
    int prefixCount(string prefix){
        TrieNode *current = root;
        for (unsigned int i = 0; i < prefix.size(); i++){
            if (!current->contains(prefix[i]))
                return 0;
            current = current->getChild(prefix[i]);
        }
        return current->prefixCount;
    }
    void remove(string word){
        if (!containsWord(word))
            throw runtime_error("Word not found.");
        TrieNode *current = root;
        for(unsigned int i = 0; i < word.size(); i++){
            current->prefixCount--;
            TrieNode *child = current->getChild(word[i]);
            if (current->prefixCount == 0)
                delete current;
            else if (child->prefixCount == 1)
                current->remove(word[i]);
            current = child;
        }
        current->prefixCount--;
        if (current->prefixCount == 0)
            delete current;
        else current->isFinal = false;
    }
    void clear(){
        clearAux(root);
        root = new TrieNode();
    }
    List<string>* getMatches(string prefix){
        List<string> *words = new DLinkedList<string>();
        TrieNode* current = root;
        for (unsigned int i = 0; i < prefix.size(); i++){
            if (!current->contains(prefix[i]))
                return words;
            current = current->getChild(prefix[i]);
        }
        getMatchesAux(current, prefix, words);
        return words;
    }
    void print(){
        List<string> *words = getMatches("");
        cout << "[ ";
        for (words->goToStart(); !words->atEnd(); words->next()){
            cout << words->getElement() << " ";
        }
        cout << "]" << endl;
        delete words;
    }
    int getSize(){
        return root->prefixCount;
    }
};

#endif // TRIE_H
