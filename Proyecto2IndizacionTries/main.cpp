#include <iostream>
#include <string>
#include "Controlador.h"
#include "Windows.h"

using namespace std;

int main(){

    Controlador *elControlador = new Controlador();
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    cout << "Prueba 2" << endl;
    cout << "Hola, este es el proyecto de indización de textos con Tries." << endl;
    cout << "Ingrese el nombre del archivo de texto a analizar: ";
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

    //-------MENU PRINCIPAL----------------------------------------------------
    bool sigueCorriendo = true;

    while (sigueCorriendo){
        int decision;
        cout << "Menú" << endl;
        cout << "1.Consulta por prefijo" << endl;
        cout << "2. Buscar palabra" << endl;
        cout << "3. Buscar por cantidad de letras" << endl;
        cout << "4. Palabras más utilizadas" << endl;
        cout << "5. Salir" << endl;
        cout << "Digite la opción que desee utilizar: ";
        cin >> decision;
        while (cin.fail() || decision < 1 || decision > 5){
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> decision;
        }
        if (decision == 1){
            string prefijo;
            cout << "Ingrese el prefijo a buscar en el árbol: ";
            cin.clear();
            cin.ignore(1000, '\n');
            getline(cin, prefijo);
            elControlador->cuentaPalabrasPrefijo(prefijo);
        }else if(decision == 2){
            string palabra;
            cout << "Ingrese la palabra a buscar en el árbol: ";
            cin.clear();
            cin.ignore(1000, '\n');
            getline(cin, palabra);
            elControlador->buscarPalabra(palabra);
        }else if (decision == 3){
            int cantidadLetras;
            cout << "Indique la cantidad de letras: ";
            cin >> cantidadLetras;
            while(cin.fail() || cantidadLetras < 1){
                cout << "Ingrese una cantidad de letras válida: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            elControlador->buscarPorCantidadLetras(cantidadLetras);
        }else if (decision == 4){
            int n;
            cout << "1. Agregar palabra a ignorar" << endl;
            cout << "2. Borrar palabra a ignorar" << endl;
            cout << "3. Ver top" << endl;
            cout << "4. Regresar" << endl;
            cout << "Ingrese cual opción desea: ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> n;
            while (cin.fail() || n < 1 || n > 4){
                cout << "Ingrese una opción válida (1-4): ";
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> n;
            }
            if (n == 1){
                string palabraIgnorar;
                cout << "Escriba la palabra nueva a ignorar: ";
                cin.clear();
                cin.ignore(1000, '\n');
                getline(cin, palabraIgnorar);
                elControlador->agregarIgnorar(palabraIgnorar);
            }else if (n == 2){
                string palabraBorrar;
                cout << "Escriba la palabra a borrar: ";
                cin.clear();
                cin.ignore(1000, '\n');
                getline(cin, palabraBorrar);
                elControlador->borrarIgnorar(palabraBorrar);
            }else if (n == 3){
                int numero;
                cout << "Ingrese la cantidad de elementos que se incluirán en el top: ";
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> numero;
                while (cin.fail() || numero < 1){
                    cout << "Ingrese un número entero positivo para la cantidad de elementos del top: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> numero;
                }
                elControlador->verTop(numero);
            }
        }else{
            sigueCorriendo = false;
        }
        cout << " " << endl;
    }
    return 0;
}
