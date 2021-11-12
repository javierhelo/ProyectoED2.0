#ifndef BSTREE_H
#define BSTREE_H

#include "BSTNode.h"
#include "DLinkedList.h"
#include <stdexcept>

using std::runtime_error;

template <typename E>
class BSTree{
private:
    BSTNode<E> *root;
    int size;

public:
    BSTree(){
        root = nullptr;
        size = 0;
    }
    ~BSTree(){
        clear();
    }
    void insert(E element){
        root = insertAux(root, element);
        size++;
    }
    E find(E element){
        return findAux(root, element);
    }
//    bool contains(E element){
//        try{
//            find(element);
//            return true;
//        }
//        catch(runtime_error e&){
//            return false
//        }
//    }
    bool contains(E element){
        return containsAux(root, element);
    }
    E remove(E element){
        E result;
        root = removeAux(root, element, &result); //parámetro de salida
        size--;
        return result;
    }
    void clear(){
        clearAux(root);
        root = nullptr;
        size = 0;
    }
    List<E>* getElements(){
        List<E> *elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }

    int getSize(){
        return size;
    }

private:
    BSTNode<E>* insertAux(BSTNode<E> *current, E element){
        if (current == nullptr)
            return new BSTNode<E>(element);
        //Si no acepta repetidos
        if (element == current->element)
            throw runtime_error("Duplicated element.");
        if (element < current->element){
            current->left = insertAux(current->left, element);
            return current;
        }else {
            current->right = insertAux(current->right, element);
            return current;
        }
    }
    E findAux(BSTNode<E> *current, E element){
        if (current == nullptr)
            throw runtime_error("Element not found.");
        if (current->element == element)
            return current->element;
        if (element < current->element)
            return findAux(current->left, element);
        else{
            return findAux(current->right, element);
        }
    }
    bool containsAux(BSTNode<E> *current, E element){
        if (current == nullptr)
            return false;
        if (element == current->element)
            return true;
        if (element < current->element)
            return containsAux(current->left, element);
        else
            return containsAux(current->right, element);
    }
    BSTNode<E>* removeAux(BSTNode<E> *current, E element, E* result){
        if (current == nullptr)
            throw runtime_error("Element not found.");
        if (element < current->element){
            current->left = removeAux(current->left, element, result);
            return current;
        }
        if (element > current->element){
            current->right = removeAux(current->right, element, result);
            return current;
        }else {     // element == current->element
            *result = current->element;     //guardamos dirección
            if (current->isLeaf()){
                delete current;
                return nullptr;
            }
            if (current->childrenCount() == 1){
                BSTNode<E>* child = current->getUniqueChild();
                delete current;
                return child;
            }else {
                // el nodo tiene dos hijos
                BSTNode<E> *successor = getSuccessor(current->right);
                swap(current, successor);
                current->right = removeAux(current->right, element, result);
                return current;
            }
        }
    }
    BSTNode<E>* getSuccessor(BSTNode<E> *current){
//        while (current->left != nullptr)
//            current = current->left;
//        return current;
        if (current->left == nullptr)
            return current;
        else
            return getSuccessor(current->left);
    }
    void swap(BSTNode<E> *node1, BSTNode<E> *node2){
        E element = node1->element;
        node1->element = node2->element;
        node2->element = element;
    }

    void clearAux(BSTNode<E> *current){
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    void getElementsAux(BSTNode<E> *current, List<E> *elements){
        if (current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

};

#endif // BSTREE_H
