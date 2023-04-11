#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;
struct Alumno2
{
    char codigo[5]{};
    char nombre[11]{};
    char apellidos[20]{};
    char carrera[15]{};
    int ciclo{};
    float mensualidad{};
    int nextdel = -2;
    void print()
    {
        for (char i : codigo)
            cout << i;
        for (char i : nombre)
            cout << i;
        for (char apellido : apellidos)
            cout << apellido;
        for (char i : carrera)
            cout << i;
        cout << ciclo << " ";
        cout << mensualidad << " ";
        cout << nextdel;
    }
};
class FixedRecord_binary {
private:
    string file_name;
public:
    explicit FixedRecord_binary(string name) {
        this->file_name = name;
        int header = -1;
        fstream file(file_name, ios::binary | ios::in | ios::out);
        file.seekg(0, ios::end);
        if (file.tellg() == 0) {
            file.write((char *) &header, sizeof(int));
            file.close();
        }
    }

    int get_header() {
        ifstream file(file_name, ios::binary);
        int h;
        file.read((char *) &h, sizeof(int));
        file.close();
        return h;
    }

    void set_header(int n) {
        fstream file(file_name, ios::binary | ios::out | ios::in);
        file.seekp(0, ios_base::beg);
        file.write((char *) &n, sizeof(int));
        file.close();
    }

    vector<Alumno2> load() {
        ifstream file(file_name, ios::binary);
        if (!file.is_open())
            cerr << "No se pudo abrir el archivo\n";
        vector<Alumno2> alumnos;
        Alumno2 alumno;
        file.seekg(sizeof(int)); //mover despues del header
        while (!file.eof()) {
            alumno = Alumno2();
            file.read((char *) &alumno, sizeof(Alumno2));
            if (alumno.nextdel == -2) //Verificar si es un archivo eliminado o no
                alumnos.push_back(alumno);
        }
        alumnos.pop_back();
        file.close();
        return alumnos; //Solo retorna los registros que no son eliminados
    }

    vector<Alumno2> loadAll() {
        ifstream file(file_name, ios::binary);
        if (!file.is_open())
            cerr << "No se pudo abrir el archivo\n";
        vector<Alumno2> alumnos;
        Alumno2 alumno;
        file.seekg(sizeof(int)); //header
        while (!file.eof()) {
            alumno = Alumno2();
            file.read((char *) &alumno, sizeof(Alumno2));
            //if (alumno.nexdel == -2)
            alumnos.push_back(alumno);
        }
        alumnos.pop_back();
        file.close();
        return alumnos;
    }

    static void readFromConsole(char buffer[], int size) {
        string temp;
        getline(cin, temp);
        for (int i = 0; i < size; i++)
            buffer[i] = (i < temp.size()) ? temp[i] : ' ';
        cin.clear();
    }

    void add(Alumno2 &record) {
        fstream file(file_name, ios::binary | ios::in | ios::out);
        if (!file.is_open())
            cerr << "No se pudo abrir el archivo\n";
        cout << "Codigo: ";
        readFromConsole(record.codigo, 5);
        cout << "Nombre: ";
        readFromConsole(record.nombre, 11);
        cout << "Apellidos: ";
        readFromConsole(record.apellidos, 20);
        cout << "Carrera: ";
        readFromConsole(record.carrera, 15);
        cout << "Ciclo: ";
        cin >> record.ciclo;
        cout << "Mensualidad: ";
        cin >> record.mensualidad;
        int header = this->get_header();
        if (header == -1) { //Si el header es -1 (como se inicializó) quiere decir que no hay eliminados
            file.seekp(0, ios::end); //por ello el próximo registro se agrega al final del archivo
            file.write((char *) &record, sizeof(record));
            file.close();
        } else {
            //Add considerando eliminación con Free List
            Alumno2 lastRecordDeleted = this->readRecord(this->get_header());
            int lastRecordDeleted_nextdel = lastRecordDeleted.nextdel;
            file.seekp(sizeof(int), ios_base::beg); //header

            file.seekp(this->get_header() * (sizeof(Alumno2)), ios_base::cur);
            file.write((char *) &record, sizeof(record));

            this->set_header(lastRecordDeleted_nextdel); //Actualizar el header con el nextdel del último eliminado
            file.close();
        }
    }

    Alumno2 readRecord(int pos) {
        ifstream file(file_name, ios::binary);
        if (!file.is_open())
            cerr << "No se pudo abrir el archivo\n";
        Alumno2 alumno;
        file.seekg(pos * (sizeof(Alumno2)) + sizeof(int), ios_base::beg);
        file.read((char *) &alumno, sizeof(Alumno2));
        file.close();
        return alumno;
    }

    bool eliminar(int pos) {
        //Free List
        int header = this->get_header();
        this->set_header(pos);
        fstream file(file_name, ios::binary | ios::out | ios::in);
        file.seekp(0, ios_base::beg);
        file.seekp(sizeof(int));//header
        file.seekp(pos * sizeof(Alumno2), ios_base::cur);
        file.seekp(sizeof(Alumno2) - sizeof(int), ios_base::cur); // Mover antes del nextdel del regitro para poder actualizarlo
        file.write((char *) &header, sizeof(int)); // Actualizar el nextdel del registro eliminado con el valor del header
        file.close();

        return true;
    }
};

//===================TESTS==========================
void test_pregunta2(){
    //2.a)El constructor reciba el nombre del archivo.
    FixedRecord_binary p2("datos1_2.dat");

    //2.c) Implemente la función void add(Alumno record) para agregar un nuevo registro al archivo.
    cout<< "TEST PREGUNTA 1.c: función void add(Alumno record)"<<endl;
    Alumno2 a2;
    cin.ignore();
    p2.add(a2);

    //2.b)Implemente la función vector<Alumno> load() para leer todos los registros del archivo
    cout<< "TEST PREGUNTA 2.b: función vector<Alumno> load()"<<endl;
    vector<Alumno2> v2;
    v2 = p2.load();
    for(auto a:v2) {
        a.print();
        cout << endl;
    }

    //2.d) Implemente la función Alumno readRecord(int pos) para obtener el registro de la posición “pos”
    cout<< "TEST PREGUNTA 2.d: función Alumno readRecord(int pos)"<<endl;
    Alumno2 a3;
    cout<<"Elija el registro que quieres obtener (comienza de 0): ";
    int pos; cin>>pos;
    a3 = p2.readRecord(pos);
    if(a3.nextdel==-2)
        a3.print();
    else{
        cout<<"Registro vacio";
    }
    cout<<endl;

    //2.e) Implemente la función bool delete(int pos) para eliminar un registro al archivo utilizando la estrategia de FreeList.
    cout<< "TEST PREGUNTA 2.e: función bool delete(int pos)"<<endl;
    int poss;
    cout<<"Registro a eliminar: ";
    cin>>poss;
    bool record_deleted=p2.eliminar(poss);
    if(record_deleted) cout<<"El registro "<<poss<<" ha sido eliminado con exito\n";
    else cout<<"No fue posible eliminar el registro\n";
    cout<<"Para verificar su eliminación se mostrará la lista de registros incluido el eliminado, "
          "de manera que se visualice cómo su nextdel fue actualizado con el valor del header\n";
    v2 = p2.loadAll();
    for(auto a:v2) {
        a.print();
        cout << endl;
    }
}

