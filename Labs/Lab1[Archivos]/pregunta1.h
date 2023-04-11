//
// Created by milagros on 4/09/23.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

struct Alumno//Record
{
    char Code [5];
    char Nombre [11];
    char Apellidos [20];
    char Carrera [15];
};

//Sobrecarga cout
inline ostream & operator << (ostream & stream, Alumno & p)
{
    stream << p.Code << " ";
    stream << p.Nombre << " ";
    stream << p.Apellidos << " ";
    stream << p.Carrera << " ";
    //stream << endl;
    stream << "\n";
    stream << flush;
    return stream;
}

//Sobrecarga cin
inline istream & operator >> (istream & stream, Alumno & p)
{
    stream.get(p.Code, 5);
    stream.get(p.Nombre, 11);
    stream.get(p.Apellidos, 20);
    stream.get(p.Carrera, 15);
    //stream.get();
    return stream;
}

class FixedRecord{
    ifstream inFile;
    ofstream outFile;
    string file_name;

public:

    FixedRecord(string file_name){
        this->file_name = file_name;
    }

    void readFromConsole(char buffer[], int size){
        string temp;
        getline (cin,temp);
        for(int i=0; i<size; i++)
            //llenar con espacios en blanco si el tamaño del string recibido en menor que el tamaño asignado para ese campo (size)
            buffer[i] = (i < temp.size())? temp[i] : ' ';
        //se llena el último espacio con \0 porque es un char
        buffer[size-1] = '\0';
        cin.clear();
    }

    vector<Alumno> load(){
        inFile.open(file_name);
        if (inFile.fail()) cout << "No se pudo abrir el archivo";
        vector<Alumno> Alumnos;
        Alumno alumno;
        string line;

        do{
            inFile >> alumno;
            if (inFile.eof()) break;
            cout << alumno;
            Alumnos.push_back(alumno);

        }while(getline(inFile, line));

        inFile.close();
        return Alumnos;
    }

    void add(Alumno record){
        outFile.open(file_name, ios::app);
        cout<<"Codigo: ";
        readFromConsole(record.Code,5);
        cout<<"Nombre: ";
        readFromConsole(record.Nombre,11);
        cout<<"Apellidos: ";
        readFromConsole(record.Apellidos,20);
        cout<<"Carrera: ";
        readFromConsole(record.Carrera,15);
        outFile << record;
        outFile.close();
    }

    Alumno readRecord(int pos){
        inFile.open(file_name);
        if (inFile.fail()) cout << "No se pudo abrir el archivo";
        Alumno alumno{};
        inFile.seekg((pos)*(sizeof(Alumno)+2), ios_base::beg);
        inFile >> alumno;
        inFile.close();
        return alumno;
    };

};

//===================TESTS==========================
void test_pregunta1(){
    //1.a)El constructor reciba el nombre del archivo.
    FixedRecord p1("datos1.txt");

    //1.b)Implemente la función vector<Alumno> load() para leer todos los registros del archivo
    cout<< "TEST PREGUNTA 1.b: función vector<Alumno> load()"<<endl;
    vector<Alumno> v1;
    v1 = p1.load();
    cout<<endl;

    //1.c) Implemente la función void add(Alumno record) para agregar un nuevo registro al archivo.
    cout<< "TEST PREGUNTA 1.c: función void add(Alumno record)"<<endl;
    Alumno a1{};
    p1.add(a1);
    cout<<endl;

    //1.d) Implemente la función Alumno readRecord(int pos) para obtener el registro de la posición “pos”
    cout<< "TEST PREGUNTA 1.d: función Alumno readRecord(int pos)"<<endl;
    Alumno a2{};
    cout<<"Elija el registro que quieres obtener (comienza de 0): ";
    int pos; cin>>pos;
    a2 = p1.readRecord(pos);
    cout << a2<<endl;
};
