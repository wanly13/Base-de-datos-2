#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <cstring>
#include "setavlfile.h"

using namespace std;

void write_demo(){
    ofstream archivo("datos.dat", ios::binary);

   /*  string linea1 = "33874,Naruto 1,Special,1,6.96,117,-1,-1,2,0\n";
    string linea2 = "33875,Naruto 2,Special,1,6.95,104,456,304,1,152\n";
    string linea3 = "33876,Naruto 3,Special,1,7.0,108,-1,-1,0,304\n";
    string linea4 = "33872,Naruto 4,Special,1,7.0,108,608,0,1,456\n";
    string linea5 = "33871,Naruto 5,Special,1,7.0,108,-1,-1,0,608\n";
    char* datos = "33874,Naruto 1,Special,1,6.96,117,-1,-1,2,0\n"
                  "33875,Naruto 2,Special,1,6.95,104,456,304,1,152\n"
                  "33876,Naruto 3,Special,1,7.0,108,-1,-1,0,304\n"
                  "33872,Naruto 4,Special,1,7.0,108,608,0,1,456\n"
                  "33871,Naruto 5,Special,1,7.0,108,-1,-1,0,608\n"; */
    //archivo.write(datos, sizeof(char) * std::strlen(datos));

  /*   archivo.write(linea1.c_str(), linea1.size());
    archivo.write(linea2.c_str(), linea2.size());
    archivo.write(linea3.c_str(), linea3.size());
    archivo.write(linea4.c_str(), linea4.size());
    archivo.write(linea5.c_str(), linea5.size()); */
    
    archivo.close();

}
int main(){
    AVLFile avl_file;
    read_write_dataset("animedata2.csv", "animedata_avl.dat", avl_file);

    //write_demo();
    read_binary_avl();
}
