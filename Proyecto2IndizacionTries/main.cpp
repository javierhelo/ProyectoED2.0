#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "include/DLinkedList.h"
#include "include/Trie.h"
#include "include/MaxHeap.h"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;
using namespace std;

int main(){
    setlocale(LC_ALL, "spanish");

    cout << "Hola, este es el proyecto de indización de textos con Tries." << endl;
    cout << "Ingrese el nombre del archivo de texto a analizar: ";



    string nombreArchivo;               //String ingresado por usuario
    getline(cin, nombreArchivo);
    nombreArchivo += ".txt";            //Se le agrega la extensión para poder abrirlo

    Trie *elArbol = new Trie();
    List<string> *lineasArchivo = new DLinkedList<string>(); //lista donde cada elemento es una linea
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
    }else {
        cout << "No se pudo abrir el archivo.";                 //caso de error y termina el programa
        return 0;
    }

    //Prueba de lo que quedó en la lista
    for (int i = 0; i < lineasArchivo->getSize(); i++){         //se imprimen los contenidos de la lista enumerando las líneas.
        lineasArchivo->goToPos(i);
        string lineaActual = lineasArchivo->getElement();
        cout << to_string(i + 1) << ". " << lineaActual << endl;
    }
    cout << "El árbol: " << endl;
    elArbol->print();
    List<int> *lineas = elArbol->getLines("es");
    cout << "Lineas en las que aparece la palabra es: ";
    lineas->print();

    return 0;
}
