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
    p.Mensualidad = stof(campo);
  
	  return stream;
}

//Sobrecarga cout
inline ostream & operator << (ostream & stream, Alumno3 & p)
{	
	stream << p.Nombre << "|";
	stream << p.Apellidos << "|";
  stream << p.Carrera << "|";
  stream << p.Mensualidad;
  stream << endl;
	//stream << "\n";
	stream << flush;
	return stream;
}

class VariableRecord{
  ifstream inFile;
  ofstream outFile;

  public:
    vector<Alumno3> load() {
      inFile.open("datos2.txt");
      if (inFile.fail()) cout << "No se pudo abrir el archivo";
      vector<Alumno3> Alumnos;
      Alumno3 alumno;

      while(!inFile.eof()){
        inFile >> alumno;
        Alumnos.push_back(alumno);
        cout << alumno<<endl;
      }
      
      inFile.close();
      return Alumnos;
    }

    void add(Alumno3 record){
      outFile.open("datos2.txt", ios::app);
      outFile << record;
	    outFile.close();
    }

    Alumno3 readRecord(int pos) {
      inFile.open("datos2.txt");
      if (inFile.fail()) cout << "No se pudo abrir el archivo";
      Alumno3 alumno;
      string line;
      for(int i = 1 ; i<pos; i++){
        getline(inFile, line);
      }
      inFile >> alumno;
      inFile.close();
      return alumno;
    }
};


void test_3(){
     vector<Alumno3> v3;
  Alumno3 a3;
  VariableRecord p3;
  // v3 = p3.load();
  a3 = p3.readRecord(4);
  cout << a3;
}