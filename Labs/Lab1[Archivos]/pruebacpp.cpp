#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//Definición de la estructura Matricula
struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;
};

//Función para escribir un registro en el archivo binario
void escribirRegistro(fstream& archivo, Matricula& matricula){
    //Escribir el campo "codigo"
    int tamanoCodigo = matricula.codigo.length();
    archivo.write(reinterpret_cast<const char*>(&tamanoCodigo), sizeof(tamanoCodigo));
    archivo.write(matricula.codigo.c_str(), tamanoCodigo);

    //Escribir el campo "ciclo"
    archivo.write(reinterpret_cast<const char*>(&matricula.ciclo), sizeof(matricula.ciclo));

    //Escribir el campo "mensualidad"
    archivo.write(reinterpret_cast<const char*>(&matricula.mensualidad), sizeof(matricula.mensualidad));

    //Escribir el campo "observaciones"
    int tamanoObservaciones = matricula.observaciones.length();
    archivo.write(reinterpret_cast<const char*>(&tamanoObservaciones), sizeof(tamanoObservaciones));
    archivo.write(matricula.observaciones.c_str(), tamanoObservaciones);
}

//Función para leer un registro del archivo binario
void leerRegistro(fstream& archivo, Matricula& matricula){
    //Leer el campo "codigo"
    int tamanoCodigo;
    archivo.read(reinterpret_cast<char*>(&tamanoCodigo), sizeof(tamanoCodigo));
    char* codigo = new char[tamanoCodigo + 1];
    archivo.read(codigo, tamanoCodigo);
    codigo[tamanoCodigo] = '\0';
    matricula.codigo = codigo;
    delete[] codigo;

    //Leer el campo "ciclo"
    archivo.read(reinterpret_cast<char*>(&matricula.ciclo), sizeof(matricula.ciclo));

    //Leer el campo "mensualidad"
    archivo.read(reinterpret_cast<char*>(&matricula.mensualidad), sizeof(matricula.mensualidad));

    //Leer el campo "observaciones"
    int tamanoObservaciones;
    archivo.read(reinterpret_cast<char*>(&tamanoObservaciones), sizeof(tamanoObservaciones));
    char* observaciones = new char[tamanoObservaciones + 1];
    archivo.read(observaciones, tamanoObservaciones);
    observaciones[tamanoObservaciones] = '\0';
    matricula.observaciones = observaciones;
    delete[] observaciones;
}
Matricula readRecord(int pos) {
    // Abrir el archivo binario para lectura
    fstream archivo("registros5.dat", ios::binary | ios::in);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    // Mover el cursor a la posición del registro
    int tamanoCodigo, tamanoObservaciones;
    while (pos > 0) {
        archivo.read(reinterpret_cast<char*>(&tamanoCodigo), sizeof(tamanoCodigo));
        archivo.ignore(tamanoCodigo);
        archivo.ignore(sizeof(int) + sizeof(float));
        archivo.read(reinterpret_cast<char*>(&tamanoObservaciones), sizeof(tamanoObservaciones));
        archivo.ignore(tamanoObservaciones);
        --pos;
    }

    // Leer el registro y almacenarlo en una estructura Matricula
    Matricula matricula = {};
    leerRegistro(archivo, matricula);

    // Cerrar el archivo
    archivo.close();

    return matricula;
}
int main() {
    fstream archivo("registros5.dat", ios::in | ios::out | ios::binary);

    // Si el archivo no existe, lo creamos y escribimos algunos registros
    if (!archivo) {
        archivo.open("registros5.dat", ios::out | ios::binary);
        Matricula matricula1 = {"MAT001", 1, 1000.0, "Ninguna"};
        escribirRegistro(archivo, matricula1);
        Matricula matricula2 = {"MAT002", 2, 1200.5, "Con descuento del 10%"};
        escribirRegistro(archivo, matricula2);
        archivo.close();
        archivo.open("registros5.dat", ios::in | ios::out | ios::binary);
    }

    // Leemos los registros del archivo y los imprimimos en pantalla
    int pos = 0;
    Matricula matricula;
    archivo.seekg(pos, ios::beg);
    while (archivo.read(reinterpret_cast<char*>(&matricula), sizeof(matricula))) {
        cout << "Matricula en la posicion " << pos << ":" << endl;
        cout << "Codigo: " << matricula.codigo << endl;
        cout << "Ciclo: " << matricula.ciclo << endl;
        cout << "Mensualidad: " << matricula.mensualidad << endl;
        cout << "Observaciones: " << matricula.observaciones << endl << endl;
        pos = archivo.tellg();
        archivo.seekg(pos, ios::beg);
    }

    // Agregamos un nuevo registro al final del archivo
    Matricula matricula3 = {"MAT003", 3, 1500.0, "Con beca completa"};
    archivo.seekp(0, ios::end);
    escribirRegistro(archivo, matricula3);

    // Leemos de nuevo los registros del archivo y los imprimimos en pantalla
    pos = 0;
    archivo.seekg(pos, ios::beg);
    while (archivo.read(reinterpret_cast<char*>(&matricula), sizeof(matricula))) {
        cout << "Matricula en la posicion " << pos << ":" << endl;
        cout << "Codigo: " << matricula.codigo << endl;
        cout << "Ciclo: " << matricula.ciclo << endl;
        cout << "Mensualidad: " << matricula.mensualidad << endl;
        cout << "Observaciones: " << matricula.observaciones << endl << endl;
        pos = archivo.tellg();
        archivo.seekg(pos, ios::beg);
    }

    archivo.close();

    return 0;
}
