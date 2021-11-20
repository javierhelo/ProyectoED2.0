#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>
#include <stdexcept>
#include "TrieNode.h"
#include "KVPair.h"

using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

/**
Clase que representa un árbol Trie, entre sus funciones esta: insertar una palabras, determinar si una palabra
se encuentra en el árbol, determinar si se encuentra un prefijo en el árbol, obtener la cantidad de palabras con
un prefijo, eliminar una palabra, limpiar el árbol, obtener la lista de palabras que contienen un prefijo, obtener
las palabras con n número de letras, obtener todas las palabras que contienen un prefijo y la cantidad de veces que aparecen en
el texto, imprimir las palabras en el árbol, obtener el tamaño de la estructura, añadir una línea a la lista de una palabra,
obtener la lista con las líneas de una palabra y obtener el número de líneas en el que aparece una palabra.
Autores: Mauricio Avilés, Juleisy Porras, Javier Helo, David Morales y Paula Bolaños
**/

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

    void numLettersAux(TrieNode *current, int n, List<KVPair<string,int>> *words, string word, int wordSize){
        if (current->isFinal && wordSize == n){
            KVPair<string,int> pair(word, current->lineas->getSize());
            words->append(pair);
            return;
        }
        List<char> *children = current->getChildren();
        for (children->goToStart(); !children->atEnd(); children->next()){
            char c = children->getElement();
            string newWord = word;
            newWord.append(1, c);
            numLettersAux(current->getChild(c), n, words, newWord, wordSize + 1);
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
    void insert(string word, int line){
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
        current->lineas->append(line);
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

    //Función que devuelve una lista que contiene las palabras con una determinada cantidad de letras junto a la cantidad de veces
    //que estas aparecen en el texto
    List<KVPair<string, int>>* numLetters(int n){
        if (n <= 0)
            throw runtime_error("El número debe ser entero positivo. ");
        List<KVPair<string,int>> *words = new DLinkedList<KVPair<string,int>>();
        TrieNode* current = root;
        numLettersAux(current, n, words, "", 0);
        return words;
    }

    //Función que solicita al usuario un prefijo para buscar en el árbol. Se muestran todas las palabras que
    //empiezan con dicho prefijo y la cantidad de veces que aparece cada una en el archivo original.
    List<KVPair<string, int>>* prefixWordCount(string prefix){
        List<KVPair<string, int>> *words = new DLinkedList<KVPair<string, int>>();
        List<string> *matches = getMatches(prefix);
        for (matches->goToStart(); !matches->atEnd(); matches->next()){
            string wordActual = matches->getElement();
            int vecesPalabra = prefixCount(wordActual);
            KVPair<string, int> pair(wordActual, vecesPalabra);
            words->append(pair);
        }
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
    void addLine(int line, string word){
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++)
            current = current->getChild(word[i]);
        current->lineas->append(line);
    }
    List<int>* getLines(string word){
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++)
            current = current->getChild(word[i]);
        return current->lineas;
    }
    int getNumLines(string word){
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++)
            current = current->getChild(word[i]);
        return current->lineas->getSize();
    }
};

#endif // TRIE_H
