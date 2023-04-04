#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <climits>
#include <vector>

using namespace std;

struct Alumno2{
  char codigo [5];
  char nombre [11];
  char apellidos [20];
  char carrera [15];
  int ciclo;
  float mensualidad;
  int nextdel;

};

inline ostream & operator << (ostream & stream, Alumno2 & p){
  stream.write((char*) &p, sizeof(p));
  stream << endl;
  return stream;
}

inline istream & operator >> (istream & stream, Alumno2 & p){
  stream.read((char*) &p, sizeof(p));
  return stream;
}

/*inline ostream & operator << (ostream & stream, Alumno2 & p){
  stream.write((char*) &p.codigo, sizeof(p.codigo));
  stream.write((char*) &p.nombre, sizeof(p.nombre));
  stream.write((char*) &p.apellidos, sizeof(p.apellidos));
  stream.write((char*) &p.carrera, sizeof(p.carrera));
  stream.write((char*) &p.ciclo, sizeof(p.ciclo));
  stream.write((char*) &p.mensualidad, sizeof(p.mensualidad));
  stream.write((char*) &p.nextdel, sizeof(p.nextdel));
  stream << endl;
  return stream;
}

inline istream & operator >> (istream & stream, Alumno2 & p){
  stream.read((char*) &p.codigo, sizeof(p.codigo));
  stream.read((char*) &p.nombre, sizeof(p.nombre));
  stream.read((char*) &p.apellidos, sizeof(p.apellidos));
  stream.read((char*) &p.carrera, sizeof(p.carrera));
  stream.read((char*) &p.ciclo, sizeof(p.ciclo));
  stream.read((char*) &p.mensualidad, sizeof(p.mensualidad));
  stream.read((char*) &p.nextdel, sizeof(p.nextdel));
  return stream;
}*/

class FixedRecord_binary{
  ifstream inFile;
  string file_name;
  ofstream outFile;
  string firstline;
  int header;

  public:
    FixedRecord_binary(string file_name){
      this->file_name = file_name;
    }
    void define_header(){
      inFile.open("datos1.dat", ios::binary);
      getline(inFile,firstline);
      header = stoi(firstline);
      //cout<<header;
      inFile.close();
    }
    vector<Alumno2> load(){
      inFile.open("datos1.dat", ios::binary);
      if (inFile.fail()){
        cout<<"No se pudo abrir el archivo";
      }
      Alumno2 alumno;
      vector<Alumno2> Alumnos;
      
      string line;
      do{
        inFile>>alumno;
        cout<<alumno<<endl;
        if (inFile.eof()) break; 
        Alumnos.push_back(alumno);
      }while(getline(inFile, line));
      
      inFile.close();
      return Alumnos;
    }

    void add(Alumno2 record){
      outFile.open("datos1.dat", ios::binary |ios::app);
      outFile << record;
	    outFile.close();
    }

    Alumno2 readRecord(int pos){
      inFile.open("datos1.dat", ios::binary |ios::app);
      if (inFile.fail()) cout << "No se pudo abrir el archivo";
      Alumno2 alumno;
      inFile.seekg((pos)*sizeof(alumno), ios_base::beg);
      
      inFile >> alumno;
      inFile.close();
      cout<<alumno;
      return alumno;
    }

//Falta
    void delete_record(int pos){
      outFile.open("datos1.dat", ios::binary |ios::app|ios::out);
      if (outFile.fail()) cout << "No se pudo abrir el archivo";
      Alumno2 alumno;
      inFile.seekg(((pos)*sizeof(alumno)), ios_base::beg);
      inFile >> alumno;
      outFile.seekp(sizeof(alumno)-sizeof(alumno.nextdel), ios_base::cur);
      outFile.write((char*) &header, sizeof(alumno.nextdel));
      outFile.close();
      //alumno.nextdel = header;
      //header = pos;*/
    }
};
