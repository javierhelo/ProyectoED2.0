#include <iostream>
#include "Controlador.h"

using namespace std;

int main(){

    Controlador *elControlador = new Controlador();
    setlocale(LC_ALL, "spanish");

    cout << "Hola, este es el proyecto de indizaci�n de textos con Tries." << endl;
    cout << "Ingrese el nombre del archivo de texto a analizar: ";
    elControlador->agregarIgnorar("Hola");
    elControlador->agregarIgnorar("Adios");
    string nombreArchivo;               //String ingresado por usuario
    getline(cin, nombreArchivo);
    nombreArchivo += ".txt";            //Se le agrega la extensi�n para poder abrirlo
    bool seProceso = elControlador->procesarArchivo(nombreArchivo);       //llama a la funci�n que lee el archivo y agrega las palabaras en el trie
    if (seProceso == false)
        return 0;
    else
        cout << "Se proceso el archivo con �xito" << endl;

    //elControlador->verListaLineas();
    //elControlador->verArbol();
    //elControlador->buscarPalabra("que");
<<<<<<< Updated upstream
    elControlador->verTop(25);
    elControlador->borrarIgnorar("Hola");

=======
    //elControlador->verTop(3);
    //elControlador->borrarIgnorar("Hola");
    elControlador->buscarPorCantidadLetras(4);
>>>>>>> Stashed changes
    return 0;
}
