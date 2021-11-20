#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "List.h"
#include <stdexcept>

#define DEFAULT_MAX_SIZE 1024

using namespace std;
using std::runtime_error;

/**
Esta es una clase abstracta que respresenta un ArrayList, en esta clase se puede guardar
cualquier tipo de datos, tiene funcionalidades para agregar elementos, hacer el array más grande,
eliminar elementos, obtener la posicion de un elemento, el tamaño del array, ir a diferentes posiciones
dentro del array y obtener el elemento en el que esta la posicion.
Autor: Mauricio Aviles
**/

template <typename E>
class ArrayList : public List<E>{
private:
    E *elements;
    int max;
    int pos;
    int size;

    void checkCurrentElement(){
        if(size==0)
            throw runtime_error("La lista esta vacia");
        if(pos==size)
            throw runtime_error("No hay elemento actual");
    }

    void expand(){
        E *temp;
        max = max*2;
        temp = new E[max];
        for(int i=0; i!=size; i++)
            temp[i] = elements[i];
        delete [] elements;
        elements = temp;
    }

public:
    ArrayList(int max = DEFAULT_MAX_SIZE){
        elements = new E[max];
        this->max = max;
        size = pos = 0;
    }
    ~ArrayList(){
        delete [] elements;
    }
    void insert(E element){
        if(size==max)
            expand();
        for(int i=size; i>pos; i--)
            elements[i] = elements[i-1];
        elements[pos] = element;
        size++;
    }
    void append(E element){
        if(size==max)
            expand();
        elements[size] = element;
        size++;
    }
    E remove(){
        checkCurrentElement();
        E result = elements[pos];
        for(int i=pos+1; i<size; i++)
            elements[i-1] = elements[i];
        size--;
        return result;
    }
    void clear(){
        size = pos = 0;
        delete [] elements;
        elements = new E[max];
    }
    E getElement(){
        checkCurrentElement();
        return elements[pos];
    }
    void goToStart(){
        pos=0;
    }
    void goToEnd(){
        pos = size;
    }
    void goToPos(int pos){
        if(pos<0 || pos>size)
            throw runtime_error("Posicion fuera de rango");
        this->pos = pos;
    }
    void next(){
        if(pos<size)
            pos++;
    }
    void previous(){
        if(pos>0)
            pos--;
    }
    bool atStart(){
        return pos == 0;
    }
    bool atEnd(){
        return pos == size;
    }
    int getPos(){
        return pos;
    }
    int getSize(){
        return size;
    }
    void print(){
        int oldPos = pos;
        cout << "[ ";
        for(goToStart(); !atEnd(); next())
            cout << getElement() << " ";
        cout << "]" << endl;
        pos = oldPos;
    }
    int indexOf(E element){
        for(int i=0; i!=size; i++){
            if(elements[i] == element)
                return i;
        }
        return -1;
    }
    bool contains(E element){
        for(int i=0; i!=size; i++){
            if(elements[i] == element)
                return true;
        }
        return false;
    }
    void extend(List<E> *L){
        if(L==nullptr)
            throw runtime_error("Null pointer");
        int oldPos = L->getPos();
        for (L->goToStart(); !L->atEnd(); L->next())
            append(L->getElement());
        L->goToPos(oldPos);
    }
    bool equals(List<E> *L){
        if(L==nullptr)
            throw runtime_error("Null pointer");
        int oldPosL = L->getPos();
        int oldPos = getPos();
        goToStart();
        for (L->goToStart(); !L->atEnd(); L->next()){
            if (getElement()==L->getElement()){
                next();
                L->next();
            }
            if (getElement()!=L->getElement())
                return false;
        }
        L->goToPos(oldPosL);
        goToPos(oldPos);
        return true;
    }

};

#endif // ARRAYLIST_H
