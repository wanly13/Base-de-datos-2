#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

/* 
    Si se necesita conocer el tamaño exacto de cada registro para realizar
     ciertas operaciones, como por ejemplo realizar búsquedas por rangos de
      tamaño, entonces sí es conveniente guardar el tamaño del registro en 
      la metadata. En caso contrario, no es necesario guardar el tamaño del 
      registro, ya que se puede calcular a partir de las posiciones iniciales 
      de cada registro en el archivo.
 */
/* 
 Este archivo de índice puede contener información como el número de registro, la posición de inicio del registro en el archivo binario y la longitud del registro en bytes. Esta información puede ser útil para acceder rápidamente a un registro específico dentro del archivo binario sin tener que recorrer todo el archivo */

struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;

    
};

struct Indice {
    int nroRegistro;
    int posInitial;
    int tamagno;
};

inline ostream & operator << (ostream & stream, Matricula & p){	
   // cout<<"Imprimos valores: \n";
	stream << p.codigo ;
	stream << p.ciclo ;
    stream << p.mensualidad ;
    stream << p.observaciones;
    stream << endl;
    stream << flush;
    return stream;
}
inline istream & operator >> (istream & stream, Matricula & p){
  stream.read((char*) &p, sizeof(p));
  return stream;
}

/* class VariableRecord_binary {
    
    ifstream inFile; ofstream outFile;

    public:
        vector<Matricula> load(){
            vector<Matricula> matriculas;
            std::ifstream indices("metadata4.dat" , ios::in | ios::binary); 
            if(!indices){ 
                cout<<"No se pudo abrir el archivo de indices"; 
            }

            vector<Indice> indices_v; Indice currentIndex;
            // Leemos la primera fila y lo asignamos en currentIndex y agregamos al vector
            while (indices.read((char*)&currentIndex, sizeof(currentIndex))) {                
                indices_v.push_back(currentIndex);
            }
            indices.close();

            // Usamos los indices obtenidos
            std::ifstream registros("registros4.dat", std::ios::binary);
            if(!registros){ 
                cout<<"No se pudo abrir el archivo de registros"; 
            }
            
            // Imprimimos los datos
            for (const auto& indice : indices_v) {
                cout<<"bu";
                Matricula matricula;
              //  cout<<"as"<<matricula;
                registros.seekg(indice.posicion);
                registros.read((char*)&matricula, sizeof(matricula));
                
                //cout<<matricula; // imprimimos en pantalla
                matriculas.push_back(matricula);
            }
            registros.close();

            return matriculas;
        }

       

        
        void add(Matricula record){

        }

        Matricula readRecord(int pos){
            Matricula preuba;
            return preuba;
        }
};
 */

class variableRecordBinary{
  ifstream inFile;
  ofstream outFile;

  public:
    vector<Indice> load_metadata(){
        inFile.open("metadata4.dat", ios::binary);
        if (inFile.fail()){ cout<<"No se pudo abrir el archivo"; }
        
        Indice index; vector<Indice> indices_metadata;
        string line;
        do{
            inFile.read((char*) &index, sizeof(index));            
            

            if (inFile.eof()) break; 
            cout<<'index.nroRegistro'<< index.nroRegistro <<endl;
            cout<<'index.posInitial'<< index.posInitial <<endl;
            cout<<'index.tamagno'<< index.tamagno <<endl;
            indices_metadata.push_back(index);
        } while(getline(inFile, line));
         inFile.close();
        return indices_metadata;
    }
    vector<Matricula> load(){
        vector<Matricula> matriculas;
        vector<Indice> indices_metadata = load_metadata();
        
        std::ifstream registros("registros4.dat", std::ios::binary);
        if(!registros){ 
            cout<<"No se pudo abrir el archivo de registros"; 
        }

         for (const auto& indice : indices_metadata) {
            Matricula matricula;
            cout<<matricula;
            registros.seekg(indice.posInitial);          
            registros >> matricula.codigo;
            registros >> matricula.ciclo;
            registros >> matricula.mensualidad;
            registros >> matricula.observaciones;
          
            cout<<matricula; // imprimimos en pantalla
                
            //registros.read((char*)&matricula, sizeof(matricula));
            matriculas.push_back(matricula);
        }
        registros.close();

        return matriculas;
    }

    void add(){
        std::ofstream registros("registros4.dat", std::ios::binary);
        Matricula matricula;
        matricula.codigo = 'A001';
        matricula.ciclo=3;
        matricula.mensualidad = 1502.01;
        matricula.observaciones= 'Prueba agregar';
        registros.write((char*)&matricula, sizeof(Matricula));
    }

    Matricula readRecord(int pos) {
        std::ifstream archivo("datos.dat", std::ios::binary);
        Matricula matricula;
        archivo.seekg(pos * sizeof(Matricula));
        archivo.read((char*)&matricula, sizeof(Matricula));
        archivo.close();
        return matricula;
    }
};



/* vector<Matricula> load(){
    vector<Matricula> matriculas;
    std::ifstream indices("metadata4.dat" , ios::in | ios::binary); 
    if(!indices){ 
        cout<<"No se pudo abrir el archivo de indices"; 
    }
    
    vector<Indice> indices_v; Indice currentIndex;
    
    // Leemos la primera fila y lo asignamos en currentIndex y agregamos al vector
    
    
    while (!indices.eof()) {
        Indice indice;
        indices.read((char*)&indice, sizeof(indice));        
    }
    
    indices.close();

    // Usamos los indices obtenidos
    std::ifstream registros("registros4.dat", std::ios::binary);
    if(!registros){ 
        cout<<"No se pudo abrir el archivo de registros"; 
    }
    
    // Imprimimos los datos
    for (const auto& indice : indices_v) {
        cout<<"bu";
        Matricula matricula;
        cout<<matricula;
        registros.seekg(indice.posicion);
        registros.read((char*)&matricula, sizeof(matricula));
        
        //cout<<matricula; // imprimimos en pantalla
        matriculas.push_back(matricula);
    }
    registros.close();

    return matriculas;
} */
/* Item 1

    En el archivo metadata4.dat nos facilita saber la posición inicial de cada registro
    del archivo binario 'datos1.dat', de esta misma forma tenemos el dato de la longitud
    en bytes por cada registro. 

    Ventajas:
        - Se obtieen un facil acceso a cualquier registro en especifico
        - Puede ser muy util en busqueda por rangos de tamaño

    Desventajas:
        - Es mas conveniente usarlo en busqueda por rangos de tamaño, por otro lado
        no es tan necesario ya que se puede usar las posiciones iniciales
 */


/* void test_p4(){
    cout<<"test_p4";
    Matricula matricula;
    VariableRecord_binary p4;
    cout<<"test_p4";
    vector<Matricula> test_1 = p4.load(); 
    
} */

/* void test_p5(){
   
    std::vector<Matricula> matriculas = load();
    cout<<"length" <<matriculas.size();
    // Imprimir información de cada matrícula
    for (const auto& matricula : matriculas) {
        std::cout << "Código: " << matricula.codigo << std::endl;
        std::cout << "Ciclo: " << matricula.ciclo << std::endl;
        std::cout << "Mensualidad: " << matricula.mensualidad << std::endl;
        std::cout << "Observaciones: " << matricula.observaciones << std::endl;
        std::cout << std::endl;
    }
} */

void test_p6(){
    cout<<"Item (a): ";
    cout<<"En el archivo metadata4.dat nos facilita saber la posición inicial \n de cada registro del archivo binario 'datos1.dat', de esta misma \n  forma tenemos el dato de la longitud en bytes por cada registro. \n Ventajas: \n- Se obtieen un facil acceso a cualquier registro en especifico\n- Puede ser muy util en busqueda por rangos de tamaño\nDesventajas:\n- Es mas conveniente usarlo en busqueda por rangos de tamaño, por otro lado\nno es tan necesario ya que se puede usar las posiciones iniciales\n";

    cout<<"Item (b): ";
    variableRecordBinary p4B;
    vector<Matricula> vector1 = p4B.load();

    cout<<"Item (c): ";
    variableRecordBinary p4C;
    p4C.add();

    cout<<"Item (d): ";
    variableRecordBinary p4D;
    Matricula matricula = p4D.readRecord(2);
    cout<<matricula;

}
int main(){
   
    test_p6();
}
