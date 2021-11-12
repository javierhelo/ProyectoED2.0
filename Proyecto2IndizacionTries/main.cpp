#include <iostream>
#include <locale.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "spanish");

    cout << "Hola, este es el proyecto de indización de textos con Tries." << endl;

    return 0;
}
