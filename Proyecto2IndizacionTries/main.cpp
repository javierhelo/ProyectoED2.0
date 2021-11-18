#include <iostream>
#include "Controlador.h"

using namespace std;

int main(){

    Controlador *elControlador = new Controlador();
    setlocale(LC_ALL, "spanish");

    cout << "Hola, este es el proyecto de indizaci�n de textos con Tries." << endl;
    cout << "Ingrese el nombre del archivo de texto a analizar: ";

    string nombreArchivo;               //String ingresado por usuario
    getline(cin, nombreArchivo);
    nombreArchivo += ".txt";            //Se le agrega la extensi�n para poder abrirlo
    bool seProceso = elControlador->procesarArchivo(nombreArchivo);       //llama a la funci�n que lee el archivo y agrega las palabaras en el trie
    if (seProceso == false)
        return 0;
    }
    elControlador->verListaLineas();
    elControlador->verArbol();

    return 0;
}
