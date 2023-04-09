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


/* inline istream & operator >> (istream & stream, Matricula & p){
    stream.read((char*) &p.codigo, sizeof(int)); // string

    
    
    
    stream.read((char*) &p.ciclo, sizeof(p)); // int
    stream.read((char*) &p.mensualidad, sizeof(int)); // int
    
    stream.read((char*) &p.observaciones, sizeof(p)); // string
    return stream;
} */

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
        ifstream archivo("metadata.dat", ios::binary);
        if (!archivo) {
            cout << "Error al abrir el archivo." << endl;
        }

        vector<Indice> indices; // vector de estructuras Indice
        cout<<"Indices: \n";
        while (!archivo.eof()) { // leer mientras no se alcance el final del archivo
            Indice indice;
            archivo.read((char*)&indice.posInitial, sizeof(int)); // leer primer valor
            archivo.read((char*)&indice.tamagno, sizeof(int)); // leer segundo valor

            // Agregar el nuevo índice al final del vector
            indices.emplace_back(indice);

            // Imprimir los valores leídos
            cout << " posInitial = " << indice.posInitial << ", tamagno = " << indice.tamagno << endl;
        }

        archivo.close();
        return indices;
    }

    vector<Matricula> load(){
        vector<Matricula> matriculas;
        vector<Indice> indices_metadata = load_metadata();
        
        std::ifstream registros("registros.dat", std::ios::binary);
        if(!registros){ 
            cout<<"No se pudo abrir el archivo de registros"; 
        }
        cout<<"entrams bucle\n";
         for (const auto& indice : indices_metadata) {
            Matricula matricula;
            
            registros.seekg(indice.posInitial); // Nos ubicamos en la posicion inicial         

            size_t size_codigo;
            size_t size_observaciones;
            // Leer el codigo [string]
            /* registros.read((char*)&size_codigo , sizeof(size_t));
            char * buffer_code = new char[size_codigo] ;
            registros.read(buffer_code, sizeof(size_t));
            matricula.codigo = buffer_code; */

            registros.read((char*)&size_codigo, sizeof(size_t));
            char * buffer_code = new char[size_codigo + 1];
            registros.read(buffer_code, size_codigo);
            buffer_code[size_codigo] = '\0'; // agregar el carácter nulo al final
            matricula.codigo = buffer_code;
            delete[] buffer_code;

            // Leer ciclo
            registros.read((char*)&matricula.ciclo , sizeof(int));

            // Leer Mensualidad
            registros.read((char*)&matricula.mensualidad , sizeof(int));
            
            // Leer el observaciones [string]
            /* registros.read((char*)&size_observaciones , sizeof(size_t));
            char * buffer_obs = new char[size_observaciones] ;
            registros.read(buffer_obs, sizeof(size_t));
            matricula.observaciones = buffer_obs; */
            registros.read((char*)&size_observaciones, sizeof(size_t));
            char * buffer_obs = new char[size_observaciones + 1];
            registros.read(buffer_obs, size_observaciones);
            buffer_obs[size_observaciones] = '\0'; // agregar el carácter nulo al final
            matricula.observaciones = buffer_obs;
            delete[] buffer_obs; // liberar la memoria después de usarla


            cout<<"Matricula\n";
            cout<<matricula; // imprimimos en pantalla
                
            //registros.read((char*)&matricula, sizeof(matricula));
            matriculas.push_back(matricula);
        }
        registros.close();

        return matriculas;
    }

    void add(){
        // Escribir en el registro
        std::ofstream registros("registros.dat", std::ios::binary);
        Matricula matricula;
        matricula.codigo = "004";
        matricula.ciclo=4;
        matricula.mensualidad = 4500;
        matricula.observaciones= "observacion4"; 

        // Escribir el codigo [string]
        size_t codigo_size = matricula.codigo.size();
        registros.write((char*)&codigo_size , sizeof(size_t) );
        registros.write(matricula.codigo.c_str(), matricula.codigo.size());
        
        // Escribir ciclo y mensualidad [int]
        registros.write((char*)&matricula.ciclo, sizeof(int));
        registros.write((char*)&matricula.mensualidad, sizeof(int));
        
        // Escribir observaciones [string]
        size_t observaciones_size = matricula.observaciones.size();
        registros.write((char*)&observaciones_size , sizeof(size_t) );
        registros.write(matricula.observaciones.c_str(), matricula.observaciones.size());


        registros.close(); 
        // Escribir en la metadata
        


    }

    Matricula readRecord(int pos) {
        std::ifstream archivo("registros.dat", std::ios::binary);
        Matricula matricula;
        vector<Indice> indices_metadata = load_metadata();
        for(int i = 0 ; i < indices_metadata.size() ; i++){
            if (i == pos){
                archivo.seekg(indices_metadata[0].tamagno);
                
                size_t size_codigo;
                size_t size_observaciones;
                // Leer el codigo [string]
                archivo.read((char*)&size_codigo, sizeof(size_t));
                char * buffer_code = new char[size_codigo + 1];
                archivo.read(buffer_code, size_codigo);
                buffer_code[size_codigo] = '\0'; // agregar el carácter nulo al final
                matricula.codigo = buffer_code;
                delete[] buffer_code;

                // Leer ciclo
                archivo.read((char*)&matricula.ciclo , sizeof(int));

                // Leer Mensualidad
                archivo.read((char*)&matricula.mensualidad , sizeof(int));
                
                // Leer el observaciones [string]
                
                archivo.read((char*)&size_observaciones, sizeof(size_t));
                char * buffer_obs = new char[size_observaciones + 1];
                archivo.read(buffer_obs, size_observaciones);
                buffer_obs[size_observaciones] = '\0'; // agregar el carácter nulo al final
                matricula.observaciones = buffer_obs;
                delete[] buffer_obs; // liberar la memoria después de usarla


                cout<<"Matricula\n";
                cout<<matricula; // imprimimos en pantalla
            }
        }
        
        archivo.close();
        return matricula;
    }


};
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




void test_p4(){
/* int main(){ */

    cout<<">>>> Item (a): \n";
    cout<<"En el archivo metadata.dat nos facilita saber la posición inicial \n de cada registro del archivo binario 'registros.dat', de esta misma \n  forma tenemos el dato de la longitud en bytes por cada registro. \n Ventajas: \n- Se obtieen un facil acceso a cualquier registro en especifico\n- Puede ser muy util en busqueda por rangos de tamaño\nDesventajas:\n- Es mas conveniente usarlo en busqueda por rangos de tamaño, por otro lado\nno es tan necesario ya que se puede usar las posiciones iniciales\n";

    cout<<">>>> Item (b): \n";
    variableRecordBinary p4B;
    vector<Matricula> vector1 = p4B.load();

    cout<<">>>> Item (c): \n";
    variableRecordBinary p4C;
    p4C.add();

    cout<<">>>> Item (d): \n";
    variableRecordBinary p4D;
    Matricula matricula = p4D.readRecord(2);
}
