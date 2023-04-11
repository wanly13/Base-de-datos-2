//
// Created by milagros on 4/09/23.
//
// Escribir el archivo binario
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;

    void print()
    {
        cout << codigo << " ";
        cout << ciclo << " ";
        cout << mensualidad << " ";
        cout << observaciones;
    }
};

class variableRecordBinary {
private:
    string metadata_name;
    string registros_name;

public:
    explicit variableRecordBinary(string metadataName, string registrosName) {
        this->metadata_name = metadataName;
        this->registros_name = registrosName;
    }

    void readMetadata(){
        fstream metadata(metadata_name, ios::binary | ios::in | ios::out);
        if (!metadata.is_open())
            cerr << "No se pudo abrir el archivo\n";
        metadata.seekg(0, ios::beg);
        while (!metadata.eof()) {
            int posicion;
            metadata.read((char *) &posicion, sizeof(int));
            cout << "Posicion n: "<<posicion<<endl;
        }
        metadata.close();
    }

    vector<Matricula> load(){
        ifstream file(registros_name, ios::binary |ios::in);
        if (!file.is_open())
            cerr << "No se pudo abrir el archivo\n";
        vector<Matricula> matriculados;
        Matricula matriculado;
        file.seekg(0, ios::beg);
        while (!file.eof()) {
            int size_codigo = 0;
            int size_observaciones = 0;

            file.read((char *) &size_codigo, sizeof(int));
            char *buffer_code = new char [size_codigo+1];
            file.read(buffer_code, size_codigo);
            buffer_code[size_codigo] = '\0'; // agregar el carácter nulo al final
            matriculado.codigo = buffer_code;
            delete[] buffer_code;

            file.read((char *) &matriculado.ciclo, sizeof(int));
            file.read((char *) &matriculado.mensualidad, sizeof(float));

            file.read((char *) &size_observaciones, sizeof(int)); //tamaño de observaciones
            char *buffer_observaciones = new char [size_observaciones+1];
            file.read(buffer_observaciones, size_observaciones);
            buffer_observaciones[size_observaciones] = '\0'; // agregar el carácter nulo al final
            matriculado.observaciones = buffer_observaciones;
            delete[] buffer_observaciones;
            matriculados.push_back(matriculado);
        }
        matriculados.pop_back();
        file.close();
        return matriculados;

    }


    void add(Matricula &record) {
        fstream file(registros_name, ios::binary | ios::in | ios::out);
        if (!file.is_open())
            cerr << "No se pudo abrir el archivo\n";

        string temp2;
        string temp3;
        cout << "Codigo: ";
        getline(cin, temp2);
        record.codigo = temp2;
        file.seekg(0, ios::end);
        int newPos = file.tellg();
        //cout<<"Posicion del nuevo registro: "<<newPos<<endl;
        file.seekp(0, ios::end);

        // Escribir en registro.dat
        int codigo_size = record.codigo.size();
        file.write((char*)&codigo_size , sizeof(int));
        file.write(record.codigo.c_str(), codigo_size);

        cout << "Ciclo: ";
        cin >> record.ciclo;

        // Escribir ciclo y mensualidad [int]
        file.write((char *) &record.ciclo, sizeof(int));

        cout << "Mensualidad: ";
        cin >> record.mensualidad;
        file.write((char *) &record.mensualidad, sizeof(float));
        cin.ignore();

        cout << "Observaciones: ";
        getline(cin, temp3);
        record.observaciones = temp3;
        int observaciones_size = record.observaciones.size();
        file.write((char*)&observaciones_size , sizeof(int));
        file.write(record.observaciones.c_str(), observaciones_size);

        //int tamagno =  sizeof(int) + codigo_size + sizeof(int) + sizeof(float) + sizeof(int) + observaciones_size;
        file.close();
        write_in_metadata(newPos);
    }

    void write_in_metadata(int pos){
        fstream metadata(metadata_name, ios::binary | ios::in | ios::out);
        if (!metadata.is_open())
            cerr << "No se pudo abrir el archivo\n";
        int newPos = pos;
        metadata.seekp(0, ios::end);
        metadata.write((char*)&newPos, sizeof(int)); //Solo escribe posiciones
        metadata.close();
    }

    Matricula readRecord(int pos){
        ifstream file(registros_name, ios::binary);
        if (!file.is_open())
            cerr << "No se pudo abrir el archivo\n";
        Matricula matriculado;

        ifstream metadata(metadata_name, ios::binary);
        metadata.seekg(0, ios::beg);
        metadata.seekg(pos*sizeof(int), ios::cur);
        int pos_registro;
        metadata.read((char *) &pos_registro, sizeof(int));
        //cout<<"Posición del registro a leer: "<<pos_registro<<endl;

        file.seekg(pos_registro, ios::beg); //ir a la posicion del registro

        int size_codigo = 0;
        int size_observaciones = 0;

        file.read((char *) &size_codigo, sizeof(int));
        char *buffer_code = new char [size_codigo+1];
        file.read(buffer_code, size_codigo);
        buffer_code[size_codigo] = '\0'; // agregar el carácter nulo al final
        matriculado.codigo = buffer_code;
        delete[] buffer_code;

        file.read((char *) &matriculado.ciclo, sizeof(int));
        file.read((char *) &matriculado.mensualidad, sizeof(float));

        file.read((char *) &size_observaciones, sizeof(int)); //tamaño de observaciones
        char *buffer_observaciones = new char [size_observaciones+1];
        file.read(buffer_observaciones, size_observaciones);
        buffer_observaciones[size_observaciones] = '\0'; // agregar el carácter nulo al final
        matriculado.observaciones = buffer_observaciones;
        delete[] buffer_observaciones;

        file.close();
        metadata.close();
        return matriculado;
    }

};


void test_pregunta4(){
    //4.a)El constructor reciba el nombre del archivo.
    variableRecordBinary p4("metadata.dat", "registros.dat");

    /*4.c) Implemente la función void add(Alumno record) para agregar un nuevo registro al archivo.
    cout<< "TEST PREGUNTA 4.c: función void add(Alumno record)"<<endl;
    Matricula m4;
    //cin.ignore();
    p4.add(m4);*/

    //4.b)Implemente la función vector<Alumno> load() para leer todos los registros del archivo
    cout<< "TEST PREGUNTA 4.b: función vector<Alumno> load()"<<endl;
     vector<Matricula> v4;
     v4 = p4.load();
     for(auto a:v4) {
         a.print();
         cout << endl;
     }

    //4.d) Implemente la función Alumno readRecord(int pos) para obtener el registro de la posición “pos”
    cout<< "TEST PREGUNTA 4.d: función Alumno readRecord(int pos)"<<endl;
    Matricula a3;
    cout<<"Elija el registro que quieres obtener (comienza de 0): ";
    int pos; cin>>pos;
    a3 = p4.readRecord(pos);
    a3.print();
    cout<<endl;

}
