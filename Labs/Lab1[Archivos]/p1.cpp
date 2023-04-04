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
  stream << endl;
	//stream << "\n";
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

  public:
    vector<Alumno> load(){
      inFile.open("datos1.txt");
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
      outFile.open("datos1.txt", ios::app);
      outFile << record;
	    outFile.close();
    }

    Alumno readRecord(int pos){
      inFile.open("datos1.txt");
      if (inFile.fail()) cout << "No se pudo abrir el archivo";
      Alumno alumno;
      inFile.seekg((pos-1)*53, ios_base::beg);
      inFile >> alumno;
      inFile.close();
      return alumno;
    };

};