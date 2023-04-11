//
// Created by milagros on 4/09/23.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

struct Alumno3
{
    string Nombre;
    string Apellidos;
    string Carrera;
    float Mensualidad;

};

inline istream & operator >> (istream & stream, Alumno3 & p)
{
    string campo;
    getline(stream, campo,'|');
    p.Nombre = campo;
    getline(stream, campo,'|');
    p.Apellidos = campo;
    getline(stream, campo,'|');
    p.Carrera = campo;
    getline(stream, campo);
    p.Mensualidad = atof(campo.c_str());

    return stream;
}

//Sobrecarga cout
inline ostream & operator << (ostream & stream, Alumno3 & p)
{
    stream << p.Nombre << "|";
    stream << p.Apellidos << "|";
    stream << p.Carrera << "|";
    stream << p.Mensualidad;
    //stream << endl;
    stream << "\n";
    stream << flush;
    return stream;
}

class VariableRecord{
    ifstream inFile;
    ofstream outFile;
    string file_name;

public:
    VariableRecord(string file_name){
        this->file_name = file_name;
    }
    vector<Alumno3> load() {
        inFile.open(file_name);
        if (inFile.fail()) cout << "No se pudo abrir el archivo";
        vector<Alumno3> Alumnos;
        Alumno3 alumno;

        while(!inFile.eof()){
            inFile >> alumno;
            if(alumno.Nombre.size() == 0) break;
            Alumnos.push_back(alumno);
            cout << alumno << endl;
        }

        inFile.close();
        return Alumnos;
    }

    void add(Alumno3 record){
        outFile.open(file_name, ios::app);
        cout<<"Nombre: ";
        getline(cin,record.Nombre);
        cout<<"Apellidos: ";
        getline(cin,record.Apellidos);
        cout<<"Carrera: ";
        getline(cin,record.Carrera);
        cout<<"Mensualidad: ";
        cin >> record.Mensualidad;
        outFile << record;
        outFile.close();
    }

    Alumno3 readRecord(int pos) {
        inFile.open(file_name);
        if (inFile.fail()) cout << "No se pudo abrir el archivo";
        Alumno3 alumno;
        string line;
        for(int i = 0 ; i<pos; i++){
            getline(inFile, line);
        }
        inFile >> alumno;
        inFile.close();
        return alumno;
    }
};


//===================TESTS==========================

void test_pregunta3(){
    //3.a)El constructor reciba el nombre del archivo.
    VariableRecord p3("datos2.txt");

    //3.b)Implemente la función vector<Alumno> load() para leer todos los registros del archivo
    cout<< "TEST PREGUNTA 3.b: función vector<Alumno> load()"<<endl;
    vector<Alumno3> v3;
    v3 = p3.load();
    cout<<endl;

    //3.c) Implemente la función void add(Alumno record) para agregar un nuevo registro al archivo.
    cout<< "TEST PREGUNTA 3.c: función void add(Alumno record)"<<endl;
    Alumno3 a3 = Alumno3();
    p3.add(a3);
    cout<<endl;

    //3.d) Implemente la función Alumno readRecord(int pos) para obtener el registro de la posición “pos”
    cout<< "TEST PREGUNTA 3.d: función Alumno readRecord(int pos)"<<endl;
    Alumno3 a4{};
    cout<<"Elija el registro que quieres obtener (comienza de 0): ";
    int pos; cin>>pos;
    a4 = p3.readRecord(pos);
    cout << a4<<endl;
};

