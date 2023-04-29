#include <fstream>
#include <string>
#include <iostream>
#include <sstream> 
#include "Record.h"

int main() {
    std::ifstream archivo("datos.csv");
    std::string linea;
    while (std::getline(archivo, linea)) {
        // Dividir la línea en campos separados por comas
        std::string nombre, apellido;
        int edad;   
        std::istringstream ss(linea);
        std::getline(ss, nombre, ',');
        std::getline(ss, apellido, ',');
        ss >> edad;
        
        /* // Hacer algo con los datos leídos
        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Apellido: " << apellido << std::endl;
        std::cout << "Edad: " << edad << std::endl; */
        Persona persona;
        std::strncpy(persona.nombre , nombre.c_str() , 100);
        persona.nombre[100] = '\0';
        std::strncpy(persona.apellido , apellido.c_str() , 100);
        persona.apellido[100] = '\0';

        
                

    }
    return 0;
}
