// Leer el archivo binario correcto
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Indice {
    int posInitial;
    int tamagno;
};

int main() {
    ifstream archivo("metadata4.dat", ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<Indice> indices; // vector de estructuras Indice

    while (!archivo.eof()) { // leer mientras no se alcance el final del archivo
        Indice indice;
        archivo.read((char*)&indice.posInitial, sizeof(int)); // leer primer valor
        archivo.read((char*)&indice.tamagno, sizeof(int)); // leer segundo valor

        // Agregar el nuevo índice al final del vector
        indices.emplace_back(indice);

        // Imprimir los valores leídos
        cout << "Indice: posInitial = " << indice.posInitial << ", tamagno = " << indice.tamagno << endl;
    }

    archivo.close();
    return 0;
}
