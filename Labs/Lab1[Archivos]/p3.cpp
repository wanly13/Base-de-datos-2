#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;
};

void escribir_registro(ofstream& archivo, Matricula matricula){
    // Escribir el tamaño de cada campo antes de escribir el campo en sí
    int codigo_tam = matricula.codigo.size();
    archivo.write(reinterpret_cast<const char*>(&codigo_tam), sizeof(int));
    archivo.write(matricula.codigo.c_str(), codigo_tam);

    archivo.write(reinterpret_cast<const char*>(&matricula.ciclo), sizeof(int));
    archivo.write(reinterpret_cast<const char*>(&matricula.mensualidad), sizeof(float));

    int obs_tam = matricula.observaciones.size();
    archivo.write(reinterpret_cast<const char*>(&obs_tam), sizeof(int));
    archivo.write(matricula.observaciones.c_str(), obs_tam);
}

void leer_registro(ifstream& archivo, Matricula& matricula){
    // Leer el tamaño de cada campo antes de leer el campo en sí
    int codigo_tam;
    archivo.read(reinterpret_cast<char*>(&codigo_tam), sizeof(int));
    char* codigo_buf = new char[codigo_tam + 1];
    archivo.read(codigo_buf, codigo_tam);
    codigo_buf[codigo_tam] = '\0';
    matricula.codigo = codigo_buf;

    archivo.read(reinterpret_cast<char*>(&matricula.ciclo), sizeof(int));
    archivo.read(reinterpret_cast<char*>(&matricula.mensualidad), sizeof(float));

    int obs_tam;
    archivo.read(reinterpret_cast<char*>(&obs_tam), sizeof(int));
    char* obs_buf = new char[obs_tam + 1];
    archivo.read(obs_buf, obs_tam);
    obs_buf[obs_tam] = '\0';
    matricula.observaciones = obs_buf;

    delete[] codigo_buf;
    delete[] obs_buf;
}

int main(){
    // Abrir el archivo en modo binario de salida
    ofstream archivo_salida("matriculas.bin", ios::binary);
    if(!archivo_salida){
        cerr << "No se pudo abrir el archivo de salida." << endl;
        return 1;
    }

    // Escribir algunos registros en el archivo
    Matricula matricula1 = {"M001", 2022, 150.50, "Pago completo"};
    Matricula matricula2 = {"M002", 2022, 200.00, "Deuda pendiente"};
    Matricula matricula3 = {"M003", 2022, 300.00, "Descuento aplicado"};
    escribir_registro(archivo_salida, matricula1);
    escribir_registro(archivo_salida, matricula2);
    escribir_registro(archivo_salida, matricula3);

    // Cerrar el archivo de salida
    archivo_salida.close();

    // Abrir el archivo en modo binario de entrada
    ifstream archivo_entrada("matriculas.bin", ios::binary);
    if(!archivo_entrada){
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    // Leer los registros del archivo e imprimirlos en la consola
    Matricula matricula_leida;
    while(!archivo_entrada.eof()){
        leer_registro(archivo_entrada, matricula_leida);
        cout << "
