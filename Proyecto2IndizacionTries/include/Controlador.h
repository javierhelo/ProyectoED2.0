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
                std::transform(linea.begin(), linea.end(), linea.begin(),
                [](unsigned char c){ return std::tolower(c); });    //pone todo en minusculas
                for (int i = 0, len = linea.size(); i < len; i++){      // este for quita de la linea los signos de puntuaci�n
                    if (ispunct(linea[i]) || std::isdigit(linea[i])){
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
        for (int i = 0; i < lineasArchivo->getSize(); i++){         //se imprimen los contenidos de la lista enumerando las l�neas.
            lineasArchivo->goToPos(i);
            string lineaActual = lineasArchivo->getElement();
            cout << to_string(i + 1) << ". " << lineaActual << endl;
        }
    }

    void verArbol(){
        cout << "El �rbol: " << endl;
        elArbol->print();
        List<int> *lineas = elArbol->getLines("es");
        cout << "Lineas en las que aparece la palabra es: ";
        lineas->print();
        cout << endl;
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

    void verTop(int n){
        MaxHeap<string, int> *top = new MaxHeap<string, int>();
        List<string> *palabras;
        palabras = elArbol->getMatches("");
        for (int i = 0; i < palabras->getSize(); i++){
            palabras->goToPos(i);
                int lines = elArbol->getNumLines(palabras->getElement());
            if(!ignorar->contains(palabras->getElement()) || palabras->getElement() == "\n"){
                top->insert(palabras->getElement(), lines);
            }
        }
        top->printArray(n);
        delete top;
    }
};

#endif // CONTROLADOR_H
