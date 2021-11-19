#include <iostream>
#include "Controlador.h"
#include "Windows.h"

using namespace std;

int main(){

    Controlador *elControlador = new Controlador();
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    cout << "Hola, este es el proyecto de indizaci�n de textos con Tries." << endl;
    cout << "Ingrese el nombre del archivo de texto a analizar: ";
    string nombreArchivo;               //String ingresado por usuario
    getline(cin, nombreArchivo);
    string extensionTxt = ".txt";          //Extension para archivos .txt
    string extensionPdf = ".pdf";            //Se le agrega la extensi�n para poder abrirlo
    bool seProceso = elControlador->procesarArchivo(nombreArchivo + extensionTxt);       //llama a la funci�n que lee el archivo .txt y agrega las palabaras en el trie
    if (!seProceso)
        seProceso = elControlador->procesarArchivo(nombreArchivo + extensionPdf);
    if (!seProceso)
        return 0;
    else
        cout << "Se proceso el archivo con �xito" << endl;

    //-------MENU PRINCIPAL----------------------------------------------------
    bool sigueCorriendo = true;
    cout << "Men�" << endl;
    cout << "1. Consulta por prefijo" << endl;
    cout << "2. Buscar palabra" << endl;
    cout << "3. Buscar por cantidad de letras" << endl;
    cout << "4. Palabras m�s utilizadas" << endl;
    cout << "5. Salir" << endl;
    cout << "Elija la opci�n que desee: ";

    while(sigueCorriendo){
        int laDecision;
        cin >> laDecision;
        while (cin.fail() || laDecision < 1 || laDecision > 4){
            cout << "Elija una opci�n v�lida (1-4): ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        switch(laDecision){
        case 1:
            {
            cout << "Ingrese el prefijo a buscar en el �rbol: ";
            string prefijo;
            getline(cin, prefijo);
            elControlador->cuentaPalabrasPrefijo(prefijo);
            }
            break;
        case 2:
            {
            cout << "Ingrese la palabra a buscar en el �rbol: ";
            string palabra;
            getline(cin, palabra);
            elControlador->buscarPalabra(palabra);
            }
            break;

        case 3:
            {
            cout << "Indique la cantidad de letras: ";
            int cantidadLetras;
            cin >> cantidadLetras;
            while(cin.fail() || cantidadLetras < 1){
                cout << "La cantidad de letras debe ser un entero positivo: ";
                cin >> cantidadLetras;
            }
            elControlador->buscarPorCantidadLetras(cantidadLetras);
            }
            break;

        case 4:
            {
            cout << "1. Agregar palabra a ignorar" << endl;
            cout << "2. Borrar palabra a ignorar" << endl;
            cout << "3. Ver top" << endl;
            cout << "4. Regresar al men� principal" << endl;
            cout << "Ingrese el n�mero de opci�n que desee: ";
            int n;
            cin >> n;
            while (cin.fail() || n < 1 || n > 4){
                cout << "Ingrese un n�mero v�lido (1-4): ";
                cin >> n;
            }
            switch(n){
            case 1:
                {
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
                }
                break;
            case 2:
                {
                cout << "Ingrese la palabra a borrar: ";
                string palabraBorrar;
                getline(cin, palabraBorrar);
                for (int i = 0, len = palabraBorrar.size(); i < len; i++){     //Quitar espacios de la palabraIgnorar
                    if (palabraBorrar[i] == " "){
                        palabraBorrar.erase(i--, 1);
                        len = palabraBorrar.size();
                    }
                }
                elControlador->borrarIgnorar(palabraBorrar);
                }
                break;
            case 3:
                {
                cout << "Ingrese la cantidad de elementos que se incluir�n en el top:";
                cin >> n;
                elControlador->verTop(n);
                }
            }
            }
            break;
        case 5:
            sigueCorriendo = false;
            break;
        }
    }
    return 0;
}
