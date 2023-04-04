#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <climits>
#include <vector>
#include "p1.cpp"
#include "p2.cpp"

using namespace std;

struct Alumno2{
  char codigo [5];
  char nombre [11];
  char apellidos [20];
  char carrera [15];
  int ciclo;
  float mensualidad;
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

/*
inline istream & operator >> (istream & stream, Alumno2 & p){
  stream.read((char*) &p.codigo, sizeof(p.codigo)-1);
  stream.read((char*) &p.nombre, sizeof(p.nombre)-1);
  stream.read((char*) &p.apellidos, sizeof(p.apellidos)-1);
  stream.read((char*) &p.carrera, sizeof(p.carrera)-1);
  stream.read((char*) &p.ciclo, sizeof(p.ciclo)-1);
  stream.read((char*) &p.mensualidad, sizeof(p.mensualidad)-1);
  return stream;
}
*/

class FixedRecord_binary{
  ifstream inFile;
  ofstream outFile;

  public:
    /*vector<Alumno2> load1(){
      inFile.open("datos1.dat", ios::in | ios::binary);
      if (inFile.fail()) cout << "No se pudo abrir el archivo";
      vector<Alumno2> Alumnos;
      Alumno2 alumno;
      inFile >> alumno;
      cout << "CODIGO: "<<alumno.codigo<<endl;
      cout << "NOMBRE: "<<alumno.nombre<<endl;
      cout << "APELLIDOS: "<<alumno.apellidos<<endl;
      cout << "CARRERA:" <<alumno.carrera<<endl;
            //cout << alumno.ciclo<<" ";
            //cout << alumno.mensualidad<<" ";
            cout << endl;
      inFile.close();
      return Alumnos;
    }*/

    vector<Alumno2> load(){
      inFile.open("datos1.dat", ios::binary);
      if (inFile.fail()){
        cout<<"No se pudo abrir el archivo";
      }
      Alumno2 alumno;
      vector<Alumno2> vector;
      string line;
      do{
        inFile>>alumno;
        cout<<alumno;
        if (inFile.eof()) break; 
        vector.push_back(alumno);
      }while(getline(inFile, line));
      
      inFile.close();
      return vector;
    }

    void add(Alumno2 record){
      outFile.open("datos1.dat", ios::app);
      outFile << record;
	    outFile.close();
    }

    Alumno2 readRecord(int pos){
      inFile.open("datos1.dat", ios::app);
      if (inFile.fail()) cout << "No se pudo abrir el archivo";
      Alumno2 alumno;
      inFile.seekg((pos-1)*64, ios_base::beg);
      inFile >> alumno;
      inFile.close();
      cout<<alumno;
      return alumno;
    }
};


int main()
{
 /* vector<Alumno> v;
  Alumno a;
  FixedRecord p1;
  v = p1.load();
  a = p1.readRecord(1);
  cout << a;
*/

  /*vector<Alumno3> v3;
  Alumno3 a3;
  VariableRecord p3;
  //v3 = p3.load();
 a3 = p3.readRecord(4);
 cout << a3;

*/
  
  Alumno2 alumno2;
  FixedRecord_binary p2;
  //p2.add(alumno2);
  //p2.readRecord(7);
  vector<Alumno2> vector = p2.load();
  //cout<<sizeof(alumno2.ciclo);

  
  /*Alumno alumno1;
  Alumno3 alumno3;
  FixedRecord p1;
  VariableRecord p3;
  //vector<Alumno3> vector = p3.load();
  //vector<Alumno> vector = p1.load();
  
  //alumno1 = p1.readRecord(7);
  //cout << alumno1;
  //alumno3 = p3.readRecord(2);
  //cout << alumno_n;
  */
	return 0;
}




/*
void readFromConsole(char buffer[], int size){
	string temp;
	cin >> temp;
  //Milagros (este es temp, ocupa 8 espacios)
	for(int i=0; i<size; i++)		  
    //llenar con espacios en blanco si el tamaño del string recibido en menor que el tamaño asignado para ese campo (size)
		buffer[i] = (i < temp.size())? temp[i] : ' ';
  //se llena el último espacio con \0 porque es un char
	buffer[size-1] = '\0';    
	cin.clear();
}

void testWrite(string filename){
	ofstream outFile;
	//escribir
	outFile.open(filename, ios::app);
	if(outFile.is_open()){		
		//leer desde consola datos para person1
		Alumno person1;	
		cout<<"Nombre:"; readFromConsole(person1.Nombre, 12);
		cout<<"Apellidos:"; readFromConsole(person1.Apellidos, 12);
		outFile << person1;
		outFile.close();
		
	}
	else 
		cerr<<"No se pudo abrir el archivo\n";	
}

void testRead(string filename)
{
	ifstream inFile;
	//leer
	inFile.open(filename);
	Alumno person2;	
	if(inFile.is_open()){
		while(!inFile.eof()){
			inFile >> person2;
      cout << person2.Code << person2.Nombre << person2.Apellidos << person2.Carrera;
			cout << endl;
		}	
		inFile.close();
	}
	else 
		cerr<<"No se pudo abrir el archivos\n";
}
*/


