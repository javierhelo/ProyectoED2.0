#ifndef BSTNODE_H
#define BSTNODE_H

/**
Clase que representa un nodo de un árbol BST, es una clase simple
al igual que sus funciones que son: decir si un nodo es hoja,
la cantidad de hijos que tiene el nodo y retorna su hijo único.
Autor: Mauricio Avilés
**/

template <typename E>
class BSTNode {
public:
    E element;
    BSTNode<E> *left;
    BSTNode<E> *right;

    BSTNode(E element, BSTNode<E> *left = nullptr, BSTNode<E> * right = nullptr){
        this->element = element;
        this->left = left;
        this->right = right;
    }
    bool isLeaf(){
        return left == nullptr && right == nullptr;
    }
    int childrenCount(){
        return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
    }
    BSTNode<E>* getUniqueChild(){
        return left == nullptr? right : left;
    }
};

#endif // BSTNODE_H
