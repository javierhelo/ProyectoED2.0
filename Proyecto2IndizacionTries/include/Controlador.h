#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

#include <algorithm>
#include "DLinkedList.h"
#include "Trie.h"
#include "MaxHeap.h"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::stringstream;
using namespace std;

/**
Esta clase, como lo dice su nombre, se encarga de controlar lo que pasa
en el programa principal, cada vez que se selecciona una acción en el menú
del main, se llama a una funcion de esta clase, sus funciones son: procesar
el archivo solicitado, además de procesar el archivo de palabras a ordenar
ver la lista de líneas guardadas, ver el cotenido del árbol, buscar una
palabra en el texto, agregar una palabra al archivo de ignorar palabras,
borrar una palabra del archivo de palabras a ignorar, ver el top de las
palabras más usadas en el archivo, buscar las palabras por su cantidad
de letras y la cantidad de palabras que contienen un prefijo.
Autores: Juleisy Porras, David Morales, Javier Helo, Paula Bolaños
**/

class Controlador{
public:
    Trie *elArbol;
    List<string> *lineasArchivo;
    List<string> *ignorar;

    Controlador(){
        elArbol = new Trie();
        lineasArchivo = new DLinkedList<string>();
        ignorar = new DLinkedList<string>();
    }

    ~Controlador(){
        elArbol->clear();
        lineasArchivo->clear();
        ignorar->clear();
    }

    bool procesarArchivo(string nombreArchivo){
        string linea;
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()){
            while (archivo.good()){
                getline(archivo, linea);
                lineasArchivo->append(linea);                      //se agregan linea por linea a la lista
                for (int i = 0, len = linea.size(); i < len; i++){      // este for quita de la linea los signos de puntuación y pone todo en minusculas
                    if (ispunct(linea[i]) || std::isdigit(linea[i])){
                        linea.erase(i--, 1);
                        len = linea.size();
                    }else{
                        linea[i] = std::tolower(linea[i]);
                    }
                }
                int size = linea.size();
                int espacioPos = 0;
                for (int i = 0; i < size; i++){
                    string palabra = "";
                    espacioPos = 0;
                    bool encontrado = false;
                    int j = 0;
                    while (encontrado == false){
                        if (linea[j] == ' ')
                            encontrado = true;
                        j++;
                    }
                    espacioPos = j;
                    palabra = linea.substr(0, espacioPos);
                    linea.erase(0, espacioPos);
                    palabra.erase(std::remove(palabra.begin(),palabra.end(), ' '), palabra.end());
                    if (palabra != "" && palabra != " "){
                        if (!elArbol->containsWord(palabra)){
                            elArbol->insert(palabra, lineasArchivo->getSize()-1);
                        }else{
                            elArbol->addLine(lineasArchivo->getSize()-1, palabra);
                        }
                    }
                }
            }
            procesarIgnorar();
            archivo.close();
            return true;
        }else {
            cout << "No se pudo abrir el archivo.";                 //caso de error y termina el programa
            return false;
        }
    }

     void procesarIgnorar(){
        string linea;
        ifstream archivo("ignorar.txt");
        if (archivo.is_open()){
            while (archivo.good()){
                getline(archivo, linea);
                ignorar->append(linea);
            }
        }else {
            cout << "No se pudo abrir el archivo ignorar.";                 //caso de error y termina el programa
        }
    }

    void verListaLineas(){
        for (int i = 0; i < lineasArchivo->getSize(); i++){         //se imprimen los contenidos de la lista enumerando las líneas.
            lineasArchivo->goToPos(i);
            string lineaActual = lineasArchivo->getElement();
            cout << to_string(i + 1) << ". " << lineaActual << endl;
        }
    }

    void verArbol(){
        cout << "El árbol: " << endl;
        elArbol->print();
    }

    void buscarPalabra(string palabra){
        if (elArbol->containsWord(palabra)){
            List<int>* lineas = elArbol->getLines(palabra);
            for (int i = 0; i < lineas->getSize(); i++){
                lineas->goToPos(i);
                lineasArchivo->goToPos(lineas->getElement());
                cout << lineas->getElement() << ". " << lineasArchivo->getElement() <<endl;
            }
        }else{
            cout << "La palabra no se encuentra en el texto" << endl;
        }
    }
    void agregarIgnorar(string palabra){
        ofstream archivo("ignorar.txt", ios::app);//Abre el txt en modo append, asi no borra lo que ya hay escrito
        if(archivo.is_open() && archivo.good()){
            archivo << '\n' << palabra;
            ignorar->append(palabra);
        }
        archivo.close();
    }
    void borrarIgnorar(string palabra){
        bool existe = ignorar->contains(palabra);
        if(existe){
            ofstream archivo2("ignorar.txt",ios::out | ios::trunc );//abre el archivo pero esta vez lo deja en blanco
            if(archivo2.is_open()){
               for(int i = 0; i < ignorar->getSize();i++){//este for remueve la palabra de la lista de palabras
                    ignorar->goToPos(i);
                    string elemento = ignorar->getElement();
                    if(elemento == palabra){
                       ignorar->remove();
                    }
                }
                for(int i = 0; i < ignorar->getSize();i++){//este for vuelve a agregar las palabras que quedaron en la lista al txt
                    ignorar->goToPos(i);
                    string elemento = ignorar->getElement();
                    archivo2 << '\n' << elemento ;
                }
                archivo2.close();
            }
        }else{
            cout << "La palabra no existe en el archivo ignorar.txt" << endl;
        }

    }
    void verTop(int n){
        MaxHeap<string, int> *top = new MaxHeap<string, int>();
        List<string> *palabras;
        palabras = elArbol->getMatches("");
        for (int i = 0; i < palabras->getSize(); i++){
            palabras->goToPos(i);
            int lines = elArbol->getNumLines(palabras->getElement());
            if(!ignorar->contains(palabras->getElement())){
                top->insert(palabras->getElement(), lines);
            }
        }
        if (n > top->getSize()){
            throw runtime_error ("n is bigger than the size of the top.");
        }
        for (int i = 0; i < n; i++){
            cout << i+1 << ". " << top->removeFirst() << endl;
        }
        delete top;
    }

    void buscarPorCantidadLetras(int n){
        elArbol->numLetters(n)->print();
    }
    void cuentaPalabrasPrefijo(string prefijo){
        elArbol->prefixWordCount(prefijo)->print();
    }

};

#endif // CONTROLADOR_H
