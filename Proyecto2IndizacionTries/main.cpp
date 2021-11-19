#include <iostream>
#include "Controlador.h"

using namespace std;

int main(){

    Controlador *elControlador = new Controlador();
    setlocale(LC_ALL, "spanish");

    cout << "Hola, este es el proyecto de indización de textos con Tries." << endl;
    cout << "Ingrese el nombre del archivo de texto a analizar: ";
    elControlador->agregarIgnorar("Hola");
    elControlador->agregarIgnorar("Adios");
    string nombreArchivo;               //String ingresado por usuario
    getline(cin, nombreArchivo);
    string extensionTxt = ".txt";          //Extension para archivos .txt
    string extensionPdf = ".pdf";            //Se le agrega la extensión para poder abrirlo
    bool seProceso = elControlador->procesarArchivo(nombreArchivo + extensionTxt);       //llama a la función que lee el archivo .txt y agrega las palabaras en el trie
    if (!seProceso)
        seProceso = elControlador->procesarArchivo(nombreArchivo + extensionPdf);
    if (!seProceso)
        return 0;
    else
        cout << "Se proceso el archivo con éxito" << endl;

    //elControlador->verListaLineas();
    //elControlador->verArbol();
    //elControlador->buscarPalabra("que");

    elControlador->verTop(25);
    elControlador->borrarIgnorar("Hola");

    //elControlador->verTop(3);
    //elControlador->borrarIgnorar("Hola");
//    elControlador->buscarPorCantidadLetras(4);  //Prueba de Juleisy
    elControlador->cuentaPalabrasPrefijo("es");

    return 0;
}
