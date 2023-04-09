#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <climits>
#include <vector>
#include "p1.cpp"
//#include "p2.cpp"
#include "p3.cpp"
#include "p4.cpp" 

using namespace std;

struct Alumno2
{
  char codigo[5];
  char nombre[11];
  char apellidos[20];
  char carrera[15];
  int ciclo;
  float mensualidad;
};

inline ostream &operator<<(ostream &stream, Alumno2 &p)
{
  stream.write((char *)&p, sizeof(p));
  stream << endl;
  return stream;
}

inline istream &operator>>(istream &stream, Alumno2 &p)
{
  stream.read((char *)&p, sizeof(p));
  return stream;
}

class FixedRecord_binary
{
  ifstream inFile;
  ofstream outFile;

 public:
  vector<Alumno2> load()
  {
    inFile.open("datos1.dat", ios::binary);
    if (inFile.fail())
    {
      cout << "No se pudo abrir el archivo";
    }
    Alumno2 alumno;
    vector<Alumno2> vector;
    string line;
    do
    {
      inFile >> alumno;
      cout << alumno;
      if (inFile.eof())
        break;
      vector.push_back(alumno);
    } while (getline(inFile, line));

    inFile.close();
    return vector;
  }

  void add(Alumno2 record)
  {
    outFile.open("datos1.dat", ios::app);
    outFile << record;
    outFile.close();
  }

  Alumno2 readRecord(int pos)
  {
    inFile.open("datos1.dat", ios::app);
    if (inFile.fail())
      cout << "No se pudo abrir el archivo";
    Alumno2 alumno;
    inFile.seekg((pos - 1) * 64, ios_base::beg);
    inFile >> alumno;
    inFile.close();
    cout << alumno;
    return alumno;
  }
};

int main(){
// Aun faltas mejoras por implementar con la nueva explicacion que hizo en clase
  // Pruebas p1
  /* cout<<"Pregunta 1:\n";
  vector<Alumno> v;
  Alumno a;
  FixedRecord p1;
  v = p1.load();
  a = p1.readRecord(1);
  cout << a; */

  // Pruebas p2
  /* cout<<"Pregunta 2: \n"; */
  /* Alumno2 alumno2;
  FixedRecord_binary p2("datos1.dat");
   vector<Alumno2> vector = p2.load(); */
  //p2.add(alumno2);
  /* p2.readRecord(5); */

  // Pruebas p3
  /* cout<<"Pregunta 3: \n";
  test_3(); */
 
 // Pruebas p4
  cout<<"Pregunta 4: \n";
  test_p6();

  
  return 0;
}

