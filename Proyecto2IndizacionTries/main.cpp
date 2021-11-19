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

    //-------MENU PRINCIPAL----------------------------------------------------
    bool sigueCorriendo = true;
    cout << "1. Consulta por prefijo" << endl;
    cout << "2. Buscar palabra" << endl;
    cout << "3. Buscar por cantidad de letras" << endl;
    cout << "4. Palabras más utilizadas" << endl;
    cout << "5. Salir" << endl;
    cout << "Elija la opción que desee: ";

    while(sigueCorriendo){
        int laDecision;
        cin >> laDecision;
        while (cin.fail() || laDecision < 1 || laDecision > 4){
            cout << "Elija una opción válida (1-4): ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        switch(laDecision){
        case 1:
            {
            cout << "Ingrese el prefijo a buscar en el árbol: ";
            string prefijo;
            getline(cin, prefijo);
            elControlador->cuentaPalabrasPrefijo(prefijo);
            break;
            }

        case 2:
            {
            cout << "Ingrese la palabra a buscar en el árbol: ";
            string palabra;
            getline(cin, palabra);
            elControlador->buscarPalabra(palabra);
            break;
            }

        case 3:
            cout << "Indique la cantidad de letras: ";
            int cantidadLetras;
            cin >> cantidadLetras;
            while(cin.fail() || cantidadLetras < 1){
                cout << "La cantidad de letras debe ser un entero positivo: ";
                cin >> cantidadLetras;
            }
            elControlador->buscarPorCantidadLetras(cantidadLetras);
            break;
        case 4:
            cout << "1. Agregar palabra a ignorar" << endl;
            cout << "2. Borrar palabra a ignorar" << endl;
            cout << "3. Ver top" << endl;
            cout << "4. Regresar" << endl;
            cout << "Ingrese el número de opción que desee: ";
            int n;
            cin >> n;
            while (cin.fail() || n < 1 || n > 4){
                cout << "Ingrese un número válido (1-4): ";
                cin >> n;
            }
            switch(n){
            case 1:
                cout << "Ingrese la palabra a ignorar: ";
                string palabraIgnorar;
                getline(cin, palabraIgnorar);
                for (int i = 0, len = palabraIgnorar.size(); i < len; i++){     //Quitar espacios de la palabraIgnorar
                    if (palabraIgnorar[i] == " "){
                        palabraIgnorar.erase(i--, 1);
                        len = palabraIgnorar.size();
                    }
                }
                elControlador->agregarIgnorar(palabraIgnorar);
                break;
            case 2:
                cout << "Ingrese la palabra a borrar: ";
                string palabraBorrar;
                getline(cin, palabraBorrar);
                for (int i = 0, len = palabraBorrar.size(); i < len; i++){     //Quitar espacios de la palabraIgnorar
                    if (palabraBorrar[i] == " "){
                        palabraBorrar.erase(i--, 1);
                        len = palabraBorrar.size();
                    }
                }

            }
        case 5:
            sigueCorriendo = false;
            break;
        }
    }

    return 0;
}
/*
for (int i = 0, len = linea.size(); i < len; i++){
            if (linea[i] == " "){
                        linea.erase(i--, 1);
                        len = linea.size();
                }
*/
