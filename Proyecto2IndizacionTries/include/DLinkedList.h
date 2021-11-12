#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "List.h"
#include "DNode.h"
#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E> *head;
    DNode<E> *current;
    DNode<E> *tail;
    int size;

public:
    DLinkedList(){
        current = head = new DNode<E>(nullptr, nullptr);
        head->next = tail = new DNode<E>(nullptr, head);
        size = 0;
    }
    ~DLinkedList(){
        clear();
        delete head;
        delete tail;
    }
    void insert(E element){
        current-> next = current->next->previous =
            new DNode<E> (element, current->next, current);
        size++;
    }
    void append(E element){
        tail->previous = tail->previous->next =
        new DNode<E> (element, tail, tail->previous);
        size++;
    }
    E remove(){
        if (size == 0)
            throw runtime_error("List is empty");
        if (current->next == tail)
            throw runtime_error("There is no current element");
        E result = current->next->element;
        current->next = current->next->next;
        delete current->next->previous;
        current->next->previous = current;
        size--;
        return result;
    }
    void clear(){
        while (head->next != tail){
            current = head->next;
            head->next = current->next;
            delete current;
        }
        current = tail->previous = head;
        size = 0;
    }
    E getElement(){
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == nullptr)
            throw runtime_error("No current element.");
        return current->next->element;
    }
    void goToStart(){
        current = head;
    }
    void goToEnd(){
        current = tail->previous;
    }
    void goToPos(int pos){
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of range.");
        current = head;
        for (int i = 0; i < pos; i++)
            current = current->next;
    }
    void next(){
        if (current != tail->previous)
            current = current->next;
    }
    void previous(){
        if (current != head)
            current = current->previous;
    }
    bool atStart(){
        return current == head;
    }
    bool atEnd(){
        return current == tail->previous;
    }
    int getPos(){
        int pos;
        for (DNode<E> *temp = head; temp != current; temp = temp->next)
            pos++;
        return pos;
    }
    int getSize(){
        return size;
    }
    int indexOf(E element){
        DNode<E> *temp = current;
        for (goToStart(); !atEnd(); next()){
            if (getElement() == element){
                return getPos();
            }
        }
        current = temp;
        return -1;
    }
    bool contains(E element){
        DNode<E> *temp = current;
        for (goToStart(); !atEnd(); next()){
            if (getElement() == element){
                current = temp;
                return true;
            }
        }
        current = temp;
        return false;
    }
    void extend(List<E> *L){
        int posL = L->getPos();
        for (L->goToStart(); !L->atEnd(); L->next()){
            append(L->getElement());
        }
        L->goToPos(posL);
    }
    bool equals(List<E> *L){
        if (size != L->getSize())
            return false;
        DNode<E> *temp = current;
        int posL = L->getPos();
        goToStart();
        for (L->goToStart(); !L->atEnd(); L->next()){
            if (current->next->element != L->getElement()){
                current = temp;
                L->goToPos(posL);
                return false;
            }
            current = current->next;
        }
        current = temp;
        L->goToPos(posL);
        return true;
    }

    void print(){
        DNode<E> *oldCurrent = current;
        cout << "[ ";
        for (goToStart(); !atEnd(); next())
            cout << getElement() << " ";
        cout << "]";
        current = oldCurrent;
    }
};

#endif // DLINKEDLIST_H
