#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <cstring>
#include "avlFIle.h"
using namespace std;


int main(){
    AVL hola("prueba.dat");
    AVL::RecordAVL prueba1("aaaaaaa" , "bbbbbbbbbbbbbbb" , 'f' , 100 , 6 , "nikeb");
    hola.insert(prueba1);

    AVL::RecordAVL prueba2("ccccccc" , "bbbbbbbbbbbbbbb" , 'f' , 100 , 6 , "nikeb");
    hola.insert(prueba2);
    
    AVL::RecordAVL prueba3("ddddddd" , "bbbbbbbbbbbbbbb" , 'f' , 100 , 6 , "nikeb");
    hola.insert(prueba3);

    AVL::RecordAVL prueba4("eeeeeee" , "bbbbbbbbbbbbbbb" , 'f' , 100 , 6 , "nikeb");
    hola.insert(prueba4);

    AVL::RecordAVL prueba5("fffffff" , "bbbbbbbbbbbbbbb" , 'f' , 100 , 6 , "nikeb");
    hola.insert(prueba5);

    AVL::RecordAVL prueba6("ggggggg" , "bbbbbbbbbbbbbbb" , 'f' , 100 , 6 , "nikeb");
    hola.insert(prueba6);

    AVL::NodeBT registro;
    fstream file("prueba.dat" ,  ios::in | ios::binary);

     if (!file) {
        cout << "Error al abrir el archivo" << endl;
    }
    while (file.read((char*) &registro, sizeof(registro))) {        
        cout << registro.data.cod << " | " << registro.data.prenda << " | " << registro.data.genero << " | " << registro.data.precio << " | " << registro.data.stock << " | " << registro.data.marca << " | " <<registro.left << " | " << registro.right << " | " << registro.height << endl;
    }

    
}