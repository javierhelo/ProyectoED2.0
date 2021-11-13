#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
#include "include/DLinkedList.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "spanish");

    cout << "Hola, este es el proyecto de indización de textos con Tries." << endl;
    cout << "Ingrese el nombre del archivo de texto a analizar: ";



    string nombreArchivo;               //String ingresado por usuario
    getline(cin, nombreArchivo);
    nombreArchivo += ".txt";            //Se le agrega la extensión para poder abrirlo

    List<string> *lineasArchivo = new DLinkedList<string>(); //lista donde cada elemento es una linea
    string linea;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()){
        while (archivo.good()){
            getline(archivo, linea);
            lineasArchivo->append(linea);                      //se agregan linea por linea a la lista
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

    return 0;
}
