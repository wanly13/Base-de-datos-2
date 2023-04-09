// Escribir el archivo binario
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Indice {
    int posInitial;
    int tamagno;
};

struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;
};

void write_index(vector<Indice> Indices){
    cout<<"write_index\n";
    ofstream archivo("metadata.dat", ios::binary); // Si existe lo reemplaza, sino lo crea
    
    cout<<Indices.size()<< endl;
    for(int i = 0 ; i < Indices.size() ; i++){
        
        archivo.write((char*)&Indices[i].posInitial, sizeof(int));
        archivo.write((char*)&Indices[i].tamagno, sizeof(int));
        
    }

    archivo.close();

}
void write_values(vector<Matricula> Matriculas){
    vector<Indice> Indices;
    ofstream archivo("registros.dat", ios::binary);
    
    int temp = 0; // 20
    int pos = 0; // 39
    cout<<"Carga"<<endl;
    for(int i =0 ; i < Matriculas.size() ; i++){
        pos = pos + temp; // 39        
        
        Indice index ;
        index.posInitial = pos;//39
        index.tamagno =  Matriculas[i].codigo.size() + sizeof(int) + sizeof(int) + sizeof(int); //20; //20
        temp = index.tamagno ; // 20        
        cout<<"pos: "<<index.posInitial << endl;
        cout<<"temp: " << index.tamagno << endl;
        Indices.push_back(index);

        // Escribir el codigo [string]
        size_t codigo_size = Matriculas[i].codigo.size();
        archivo.write((char*)&codigo_size , sizeof(size_t) );
        archivo.write(Matriculas[i].codigo.c_str(), Matriculas[i].codigo.size());
        
        // Escribir ciclo y mensualidad [int]
        archivo.write((char*)&Matriculas[i].ciclo, sizeof(int));
        archivo.write((char*)&Matriculas[i].mensualidad, sizeof(int));
        
        // Escribir observaciones [string]
        size_t observaciones_size = Matriculas[i].observaciones.size();
        archivo.write((char*)&observaciones_size , sizeof(size_t) );
        archivo.write(Matriculas[i].observaciones.c_str(), Matriculas[i].observaciones.size());

    }
    cout<<"salida\n";
    write_index(Indices);
    archivo.close();
}



vector<Matricula> cargarMatriculas(){
    vector<Matricula> Matriculas;
    Matricula temp ;
    temp.codigo = "001";
    temp.ciclo= 1;
    temp.mensualidad= 1500;
    temp.observaciones = "observacion1";
    Matriculas.push_back(temp);

    temp.codigo = "002";
    temp.ciclo= 2;
    temp.mensualidad= 2500;
    temp.observaciones = "observacion2";
    Matriculas.push_back(temp);

    temp.codigo = "003";
    temp.ciclo= 3;
    temp.mensualidad= 3500;
    temp.observaciones = "observacion3";
    Matriculas.push_back(temp);
    return Matriculas;
}

int main() {
    vector<Matricula> Matriculas =  cargarMatriculas();
    
    write_values( Matriculas );

    
    
}
