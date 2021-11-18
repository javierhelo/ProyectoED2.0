#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "DLinkedList.h"
#include "Trie.h"
#include "MaxHeap.h"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;
using namespace std;

class Controlador{
public:
    Trie *elArbol;
    List<string> *lineasArchivo;
    List<string> *palabrasIgnorar = new DLinkedList<string>();
    Controlador(){
        elArbol = new Trie();
        lineasArchivo = new DLinkedList<string>();
    }

    bool procesarArchivo(string nombreArchivo){
        string linea;
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()){
            while (archivo.good()){
                getline(archivo, linea);
                lineasArchivo->append(linea);                      //se agregan linea por linea a la lista
                for (int i = 0, len = linea.size(); i < len; i++){      // este for quita de la linea los signos de puntuación
                    if (ispunct(linea[i])){
                        linea.erase(i--, 1);
                        len = linea.size();
                    }
                }
                string espacio = " ";
                vector<string> palabras{};
                size_t pos = 0;
                while ((pos = linea.find(espacio)) != string::npos) {       //se guardan las palabras en un vector
                    palabras.push_back(linea.substr(0, pos));
                    linea.erase(0, pos + espacio.length());
                }
                for (unsigned int i = 0; i < palabras.size(); i++){          //se insertan las palabras en el trie
                    if (!elArbol->containsWord(palabras[i])){
                        elArbol->insert(palabras[i], lineasArchivo->getSize()-1);
                    }else{
                        elArbol->addLine(lineasArchivo->getSize()-1, palabras[i]);
                    }
                }
            }
            archivo.close();
            return true;
        }else {
            cout << "No se pudo abrir el archivo.";                 //caso de error y termina el programa
            return false;
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
        List<int> *lineas = elArbol->getLines("es");
        cout << "Lineas en las que aparece la palabra es: ";
        lineas->print();
    }
    void agregarIgnorar(string palabra){
        ofstream archivo("ignorar.txt", ios::app);//Abre el txt en modo append, asi no borra lo que ya hay escrito
        if(archivo.is_open() && archivo.good()){
            archivo << '\n' << palabra;
            palabrasIgnorar->append(palabra);
        }
        archivo.close();
    }
    void borrarIgnorar(string palabra){
        string word;
        List<string> *lista= new DLinkedList<string>();
        ifstream archivo("ignorar.txt");//Abre el archivo para lectura
        if(archivo.is_open()){
           while(archivo.good()){//crea una lista con todas las palabras que hay en el txt
            getline(archivo,word);
            lista->append(word);
           }
           archivo.close();
        }
        ofstream archivo2("ignorar.txt",ios::out | ios::trunc );//abre de nuevo el archivo pero esta vez lo deja en blanco
        if(archivo2.is_open()){
           for(int i = 0; i < lista->getSize();i++){//este for remueve la palabra de la lista de palabras
                lista->goToPos(i);
                string elemento = lista->getElement();
                if(elemento == palabra)
                   lista->remove();
            }
            for(int i = 0; i < lista->getSize();i++){//este for vuelve a agregar las palabras que quedaron en la lista al txt
                lista->goToPos(i);
                string elemento = lista->getElement();
                archivo2 << '\n' << elemento ;
            }
            archivo.close();
        }
    }
};

#endif // CONTROLADOR_H
