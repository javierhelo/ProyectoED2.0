#ifndef LIST_H
#define LIST_H

template <typename E>
class List{
private:
    void operator =(const List&){} //Quitar operador de asignación
    List(const List&) {} //no se puede usar el constructor de copia
public:
    List(){}
    //el destructor hay que ponerlo como virtual para que el método
    //se pueda cambiar en las subclases
    virtual ~List(){}
    virtual void insert(E element) = 0; // dejamos implementacion para subclase (para eso es el 0)
    virtual void append(E element) = 0;
    virtual E remove() = 0;
    virtual void clear() = 0;
    virtual E getElement() = 0;
    virtual void goToStart() = 0; //CAMELCASE para métodos
    virtual void goToEnd() = 0;
    virtual void goToPos(int pos) = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual bool atStart() = 0;
    virtual bool atEnd() = 0;
    virtual int getPos() = 0;
    virtual int getSize() = 0;
    virtual void print() = 0;
    // Nuevas funciones:
    virtual int indexOf(E element) = 0;
    virtual bool contains(E element) = 0;
    virtual void extend(List<E> *L) = 0;
    virtual bool equals(List<E> *L) = 0;

};

#endif // LIST_H
