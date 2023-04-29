//
// Created by milagros on 4/28/23.
//

#ifndef RECORDLECTURE_AVLFILE_H
#define RECORDLECTURE_AVLFILE_H

#include <fstream>
#include <ostream>
#include <vector>
#include <cstring>
#include "libs.h"
#include "record.h"
using namespace std;

class AVLFile {
private:
    struct NodeBT {
        Record data;
        long left;
        long right;
        long height;
        long pos ;
        NodeBT() {
            left = right = -1;
        }
        NodeBT(Record &record) {
            this->data = record;
            left = right = -1;
        }
    };

private:
    long root;
    std::string filename;

public:
    AVLFile(){};
    AVLFile(string filename){
        this->filename = filename;
    }

    void set_filename (string filename){ this->filename = filename;}

    Record find(int animeid) {
        std::ifstream file(this->filename, std::ios::binary);
        Record result = find(file, this->root, animeid); // El root puede cambiar o solo es -1 cuando no tiene valores el archivo?
        file.close();
        return result;
    }

    void insert(Record& record) {
        std::fstream file(this->filename, std::ios::in|std::ios::out|std::ios::binary | std::ios::app);
        insert(file, this->root, record);
        file.close();
    }

    void remove(Record& record) {
        std::fstream file(this->filename, std::ios::in|std::ios::out|std::ios::binary | std::ios::app);
        remove(file, this->root, record.anime_id);
        file.close();
    }


    vector<Record> search (Record key){
        std::ifstream file(this->filename, std::ios::binary);
        vector<Record> result = search(file, this->root, key.anime_id);
        file.close();
        return result;
    }

    vector<Record> rangeSearch (Record& key1,Record& key2 ){
        vector<Record> results;
        std::fstream file(this->filename, std::ios::in|std::ios::out|std::ios::binary | std::ios::app);

        rangeSearch(file, this->root, key1.anime_id, key2.anime_id, results);

        file.close();
        return results;
    }

private:
    // FUNCTIONS TO USE
    vector<Record> search(std::ifstream &file ,long record_pos, int animeid);

    void rangeSearch(std::fstream &file ,long& record_pos, int begin_key, int end_key , std::vector<Record> &results);

    //void insert(std::fstream &file, long& record_pos, const long& parent_pos, Record& record, long& pos);
    //void insert(std::fstream &file, long& record_pos , Record& record);
    void insert(std::fstream &file , long &node_pos, Record &value);

    //long remove(std::fstream &file, long record_pos, char value[5]);

    //int update_height(long record_pos, std::fstream &file);
    void update_height(std::fstream& file, long node_pos);

    long height (std::fstream& file , long record_pos );
    //void update_balance_factor(long record_pos, std::fstream &file);

    long calculate_balance_factor(std::fstream& file , NodeBT node );

    void balance( std::fstream &file , long &node_pos);

    void left_rotation( std::fstream &file ,long &node_pos);

    void right_rotation( std::fstream &file ,long &node_pos);

    long maxValue(long node_pos, std::fstream &file);

    void remove( std::fstream &file , long &node_pos, int value);

    Record find(std::ifstream &file, long record_pos, int value);
};

// ------------------ IMPLEMENTATIONS ------------------

Record AVLFile::find(std::ifstream &file, long record_pos, int value){
    if (record_pos == -1)
        throw "Archivo Vacio";
    else {
        NodeBT temp;
        file.seekg(record_pos * sizeof(NodeBT)); // Nos ubicamos en la posicion
        file.read((char*)&temp, sizeof(NodeBT));

        if (value < temp.data.anime_id)
            return find(file, temp.left, value);
        else if (value > temp.data.anime_id)
            return find(file, temp.right, value);
        else
            return temp.data;
    }
}

void AVLFile::insert(std::fstream &file , long &node_pos, Record& value) {
    if (node_pos == -1) { // Para cuando no existe
        NodeBT new_node;
        new_node.data = value;
        new_node.left = -1;
        new_node.right = -1;
        new_node.height = 0;
        node_pos = file.tellp() / sizeof(NodeBT);
        //tellp : devuelve la posicion actual para escritura
        file.write((char*)&new_node, sizeof(NodeBT));

    } else {
        NodeBT node;
        file.seekg(node_pos * sizeof(NodeBT));
        file.read((char*)&node, sizeof(NodeBT));

        if (value.anime_id < node.data.anime_id) {
            insert(file , node.left, value);
        } else if (value.anime_id > node.data.anime_id) {
            insert(file , node.right, value);
        }
        update_height( file , node_pos);
        balance(file , node_pos);
    }
}

void AVLFile::remove( std::fstream &file , long &node_pos, int value) {
    if (node_pos == -1) {
        throw "Registro no encontrado";
    }
    NodeBT node;
    file.seekg(node_pos * sizeof(NodeBT));
    file.read((char*)&node, sizeof(NodeBT));

    if (value < node.data.anime_id) {
        remove(file ,node.left, value);
    }
    else if (value > node.data.anime_id) {
        remove(file ,node.right, value);
    }
    else { // se encontró el nodo a eliminar
        if (node.left == -1 && node.right == -1) { // caso 1: el nodo no tiene hijos
            file.seekp(node_pos * sizeof(NodeBT));
            NodeBT delete_node;// Record data_vacia;
            delete_node.data = Record ();
            delete_node.left = -1;
            delete_node.right = -1;
            delete_node.height = 0;

            // Escribimos el nodo borrado
            file.write((char*)&delete_node, sizeof(NodeBT));
            node_pos = -1; // Ya no esta en uso (Se considera como espacio libre)
            return; // Aqui termina la ejecicion ya que solo tiene un hijo
        }
        else if (node.left == -1 || node.right == -1) { // caso 2: el nodo tiene un solo hijo
            long child_pos = node.left == -1 ? node.right : node.left; // Igual al de el ejemplo pero optimizado

            file.seekp(node_pos * sizeof(NodeBT));
            file.write((char*)&child_pos, sizeof(long));

            node_pos = child_pos;
        }
        else { // caso 3: el nodo tiene dos hijos
            long max_pos = maxValue(node.left, file);
            NodeBT max_node;
            file.seekg(max_pos * sizeof(NodeBT));
            file.read((char*)&max_node, sizeof(NodeBT));

            node.data = max_node.data;
            remove(file , node.left, max_node.data.anime_id);
        }
    }
    update_height( file , node_pos);
    balance( file , node_pos);
}

long AVLFile::maxValue(long node_pos, std::fstream &file){
    if (node_pos == -1)
        throw "Registro no encontrado";

    NodeBT node;
    file.seekg(node_pos * sizeof(NodeBT));
    file.read((char*)&node, sizeof(NodeBT));

    while (node.right != -1) {
        node_pos = node.right;
        file.seekg(node_pos * sizeof(NodeBT));
        file.read((char*)&node, sizeof(NodeBT));
    }
    return node_pos; // Para este caso necesitamos la posicion ya que se usa para leer la data
}

void AVLFile::rangeSearch(std::fstream &file ,long& record_pos, int begin_key, int end_key , std::vector<Record> &results){
    if (record_pos == -1)
        throw "El archivo se encuentra vacío";

    NodeBT temp;
    file.seekg(record_pos * sizeof(NodeBT)); // Nos ubicamos en el root
    // IMplementar como cin operator
    file.read((char*)&temp, sizeof(NodeBT)); // Leemos el root

    // SI estamos dentro del rango  agregamos
    if (temp.data.anime_id, begin_key >= 0 && temp.data.anime_id, end_key <= 0) {
        results.push_back(temp.data);
    }

    // buscamos por izquierda
    if (temp.data.anime_id, begin_key > 0) {
        rangeSearch(file, temp.left, begin_key, end_key, results);
    }

    // buscamos por derecha
    if (temp.data.anime_id, end_key < 0) {
        rangeSearch(file, temp.right, begin_key, end_key, results);
    }
    // strcmp:  0: si ambas cadenas son iguales.
    // Un valor negativo: si la primera cadena es menor que la segunda.
    // Un valor positivo: si la primera cadena es mayor que la segunda.

}

void AVLFile::update_height(std::fstream& file, long record_pos) {
    if (record_pos == -1)
        throw "Archivo Vacio";

    // Leemos los datos desde el archivo
    NodeBT node;
    file.seekg(record_pos * sizeof(NodeBT));
    // Intentar por la tecnica del empaquetado
    file.read((char*)&node, sizeof(NodeBT));

    // Calculamos la altura entre el izq y der luego calculamos el maximo de ellos
    node.height = max (height(file , node.left) , height (file , node.right) ) + 1;

    // Escribimos la nueva altura del nodo en su posición correspondiente en el archivo
    file.seekp(record_pos * sizeof(NodeBT) + offsetof(NodeBT, height));//offsetof : guarda el desplazamiento, en este caso guarda el desplazamiento de height
    file.write((char*)&node.height, sizeof(node.height));
}

long AVLFile:: height (std::fstream& file , long record_pos ) {
    long height = 0;
    if (record_pos == -1)
        throw "Archivo Vacio";
    else {
        NodeBT node;
        file.seekg(node.left * sizeof(NodeBT));
        file.read((char*)&node, sizeof(NodeBT));
        height = node.height;
    }
    return height;
}

long AVLFile::calculate_balance_factor(std::fstream& file , NodeBT node ){
    long balance_factor = height(file , node.left) - height(file , node.right);
    return balance_factor;
}

void AVLFile::balance( std::fstream &file , long &node_pos) {
    NodeBT node;
    file.seekg(node_pos * sizeof(NodeBT));

    file.read((char*)&node, sizeof(NodeBT));// Empaquetado para el read
    // Obtenemos el factor de balanceo
    long factor_balanceo = calculate_balance_factor( file , node);

    if (factor_balanceo > 2) { // el nodo está desequilibrado hacia la izquierda
        NodeBT left_node;
        file.seekg(node.left * sizeof(NodeBT));
        file.read((char*)&left_node, sizeof(NodeBT)); // Empaquetado para el read

        if (height(file , left_node.left) >= height(file , left_node.right)) { // rotación simple a la derecha
            right_rotation(file , node_pos);
        }
        else { // rotación doble: izquierda-derecha
            left_rotation(file , left_node.left);
            right_rotation(file , node_pos);
        }
    } else if (factor_balanceo < -2) { // el nodo está desequilibrado hacia la derecha
        NodeBT right_node;
        file.seekg(node.right * sizeof(NodeBT));
        file.read((char*)&right_node, sizeof(NodeBT));
        if (height(file , right_node.right) >= height( file , right_node.left)) { // rotación simple a la izquierda
            left_rotation( file ,node_pos);
        }
        else { // rotación doble: derecha-izquierda
            right_rotation( file ,right_node.right);
            left_rotation( file ,node_pos);
        }
    }
    update_height(file , node_pos); // Actualizamos las alturas

    // Verificacion de balanceo
    if (node_pos != this -> root) {
        NodeBT parent;
        file.seekg(node_pos * sizeof(NodeBT));
        file.read((char*)&parent, sizeof(NodeBT));
        balance( file , (node_pos == parent.left) ? parent.left : parent.right);
    }
    //valid_balance_recursive(file , node_pos);

}

void AVLFile::left_rotation( std::fstream &file ,long &node_pos) {
    NodeBT node, right_node;
    // Nos ubicamos en la posicion del nodo
    file.seekg(node_pos * sizeof(NodeBT));
    file.read((char*)&node, sizeof(NodeBT)); // leemos el nodo (Empaquetar)

    // Nos ubicamos en la posicion del hijo derecho
    file.seekg(node.right * sizeof(NodeBT));
    file.read((char*)&right_node, sizeof(NodeBT));// leemos al hijo (Empaquetar)

    node.right = right_node.left;
    right_node.left = node_pos;

    node.height =  std::max(height(file , node.left), height(file , node.right)) + 1 ;
    right_node.height =  std::max(height(file , right_node.left), height(file , right_node.right)) + 1 ;

    file.seekp(node_pos * sizeof(NodeBT)); // Establece la posicion de escritura para el nodo
    file.write((char*)&node, sizeof(NodeBT));

    file.seekp(right_node.pos  * sizeof(NodeBT)); // Establece la posicion de escritura para el hijo dereco
    file.write((char*)&right_node, sizeof(NodeBT));
    node_pos = right_node.pos ;
}

void AVLFile::right_rotation( std::fstream &file ,long &node_pos) {
    NodeBT node, left_node;

    file.seekg(node_pos * sizeof(NodeBT));
    file.read((char*)&node, sizeof(NodeBT));

    file.seekg(node.left * sizeof(NodeBT));
    file.read((char*)&left_node, sizeof(NodeBT));

    node.left = left_node.right;
    left_node.right = node_pos;

    node.height =  std::max(height(file , node.left), height(file , node.right)) + 1 ;
    left_node.height =  std::max(height(file , left_node.left), height( file , left_node.right)) + 1;

    file.seekp(node_pos * sizeof(NodeBT));
    file.write((char*)&node, sizeof(NodeBT));

    file.seekp(left_node.pos * sizeof(NodeBT));
    file.write((char*)&left_node, sizeof(NodeBT));

    node_pos = left_node.pos;
}

#endif //RECORDLECTURE_AVLFILE_H
