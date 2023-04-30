#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <cstring>
#include "avl_file.h"
using namespace std;


int main(){
    AVL nuevo_avl("nombre_archivo.dat");
    AVL::Record record;
    record.anime_id = 123;
    strcpy(record.name, "Naruto");
    strcpy(record.type, "TV");
    record.episodes = 220;
    record.rating = 7.91;
    record.members = 1257682;
    nuevo_avl.insert(record);

  
    
  /*   fstream file("prueba.dat" ,  ios::in | ios::binary);

     if (!file) {
        cout << "Error al abrir el archivo" << endl;
    }
    while (file.read((char*) &registro, sizeof(registro))) {        
        cout << registro.data.cod << " | " << registro.data.prenda << " | " << registro.data.genero << " | " << registro.data.precio << " | " << registro.data.stock << " | " << registro.data.marca << " | " <<registro.left << " | " << registro.right << " | " << registro.height << endl;
    }
 */
    
}