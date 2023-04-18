#include <fstream>
#include <ostream>
#include <vector>
#include <cstring>
#include "Record.h"
using namespace std;

template <typename Record>
class AVLFile {
 private:
    struct NodeBT {
        Record data;
        long left; 
        long right;
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
    Record find(char value[5]) {
        std::ifstream file(this->filename, std::ios::binary);
        Record result = find(file, this->root, value); // El root puede cambiar o solo es -1 cuando no tiene valores el archivo?
        file.close();
        return result;
    }

    void insert(Record& record) {
        std::fstream file(this->filename, std::ios::in|std::ios::out|std::ios::binary | std::ios::app);
        NodeBT node(record);
        file.write((char *)&node.data, sizeof(node.data));
        file.write((char *)&node.left, sizeof(node.left));
        file.write((char *)&node.right, sizeof(node.right));
        if (this->root == -1) this->root = 0;
        else {
            long pos = file.tellg() / sizeof(NodeBT) - 1;
            insert(file, this->root, -1, node.data, pos);
        }
        file.close();
    }
    void remove(char value[5]) {
        std::fstream file(this->filename, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open())
            throw "Error al abrir el archivo";
        this->root = remove(file, this->root, value);
        file.close();
    }

    vector<Record> search (Record key){
        std::ifstream file(this->filename, std::ios::binary);
        vector<Record> result = search(file, this->root, value);        
    }

    vector<Record> rangeSearch (Record key1,Record key2 ){
        vector<Record> results;
        ifstream file(this->filename, std::ios::binary);

        rangeSearch(file, this->root, value_min, value_max, results);

        file.close();
        return results;       
    }
 private:
    // FUNCTIONS TO USE
    vector<Record> search(std::ifstream &file ,long record_pos, char value[5]);
    
    void rangeSearch(std::fstream &file ,long& record_pos, char begin_key[5], char end_key[5] , std::vector<Record> &results);
    
    void insert(std::fstream &file, long& record_pos, const long& parent_pos, Record& record, long& pos);
    
    long remove(std::fstream &file, long record_pos, char value[5]);

    int update_height(long record_pos, std::fstream &file);

    void update_balance_factor(long record_pos, std::fstream &file);

    long balance(long record_pos, std::fstream &file);
    
    Record find(std::ifstream &file, long record_pos, char value[5]);
};

// ------------------ IMPLEMENTATIONS ------------------ 

/* template <typename Record>
vector<Record> AVLFile<Record>::search (Record key){
    vector<Record> result;
    return result;
}
 */
template <typename Record>
vector<Record> AVLFile<Record>::search(std::ifstream &file, long record_pos, char value[5]){
    vector<Record> result;
    return result;
}

template <typename Record>
Record AVLFile<Record>::find(std::ifstream &file, long record_pos, char value[5]){
        if (record_pos == -1)
            throw "Archivo Vacio";
        else {
            NodeBT temp;
            file.seekg(record_pos * sizeof(NodeBT)); // Nos ubicamos en la posicion 
            file.read((char*)&temp, sizeof(NodeBT));
            
            if (value < temp.data.cod)
                return find(file, temp.left, value);
            else if (value > temp.data.cod)
                return find(file, temp.right, value);
            else
                return temp.data;
        }
}

template <typename Record>
void insert(std::fstream &file, long& record_pos, const long& parent_pos, Record& record, long& pos){
        if (record_pos == -1) {
            NodeBT temp;
            file.seekg(parent_pos * sizeof(NodeBT));
            file.read((char*)&temp, sizeof(NodeBT));
            file.seekg(parent_pos*sizeof(NodeBT)+sizeof(record)+(record <= temp.data)?0:sizeof(temp.left));
            file.write((char *)&pos, sizeof(pos));

        }
        else {
            NodeBT temp;
            file.seekg(record_pos * sizeof(NodeBT));
            file.read((char*)&temp, sizeof(NodeBT));
            if (record <= temp.data)
                insert(file, temp.left, record_pos, record, pos);
            else
                insert(file, temp.right, record_pos, record, pos);
            
            this->update_height(temp);
            this->balance(temp);
        }
        
}

template <typename Record>
long AVLFile<Record>::remove(std::fstream& file, long record_pos, char value[5]) {
    if (record_pos == -1)
        throw "Registro no encontrado";
    else {
        NodeBT temp;
        file.seekg(record_pos * sizeof(NodeBT));
        file.read((char*)&temp, sizeof(NodeBT));

        if (strcmp(value, temp.data.cod) < 0)
            temp.left = remove(file, temp.left, value);
        else if (strcmp(value, temp.data.cod) > 0)
            temp.right = remove(file, temp.right, value);
        else {
            if (temp.left == -1) {
                long right_child = temp.right;
                file.seekp(record_pos * sizeof(NodeBT));
                file.write((char*)&temp.right, sizeof(long));
                return right_child;
            }
            else if (temp.right == -1) {
                long left_child = temp.left;
                file.seekp(record_pos * sizeof(NodeBT));
                file.write((char*)&temp.left, sizeof(long));
                return left_child;
            }
            else {
                long min_right = find_min(file, temp.right);
                NodeBT min_right_node;
                file.seekg(min_right * sizeof(NodeBT));
                file.read((char*)&min_right_node, sizeof(NodeBT));
                temp.data = min_right_node.data;
                temp.right = remove(file, temp.right, min_right_node.data.cod);
            }
        }
        update_height(temp);
        update_balance_factor(temp);

        file.seekp(record_pos * sizeof(NodeBT));
        file.write((char*)&temp, sizeof(NodeBT));
        return balance(file, temp);
    }
}

template <typename Record>
void AVLFile<Record>::rangeSearch(std::fstream &file ,long& record_pos, char begin_key[5], char end_key[5] , std::vector<Record> &results){
    if (record_pos == -1) {
        throw "El archivo se encuentra vacío";
    }

    NodeBT temp;
    file.seekg(record_pos * sizeof(NodeBT)); // Nos ubicamos en el root
    // IMplementar como cin operator
    file.read((char*)&temp, sizeof(NodeBT)); // Leemos el root

    // SI estamos dentro del rango  agregamos 
    if (strcmp(temp.data.cod, begin_key) >= 0 && strcmp(temp.data.cod, end_key) <= 0) {
        results.push_back(temp.data);
    }

    // buscamos por izquierda
    if (strcmp(temp.data.cod, begin_key) > 0) {
        rangeSearch(file, temp.left, begin_key, end_key, results);
    }

    // buscamos por derecha
    if (strcmp(temp.data.cod, end_key) < 0) {
        rangeSearch(file, temp.right, begin_key, end_key, results);
    }
/*  strcmp:  0: si ambas cadenas son iguales.
    Un valor negativo: si la primera cadena es menor que la segunda.
    Un valor positivo: si la primera cadena es mayor que la segunda.
 */
}

template<typename Record>
int AVLFile<Record>::update_height(long record_pos, std::fstream &file) {
    if (record_pos == -1)
        return -1;
    else {
        NodeBT temp;
        file.seekg(record_pos * sizeof(NodeBT)); // Nos ubicamos en la posición 
        file.read(reinterpret_cast<char*>(&temp), sizeof(NodeBT));
        
        int left_height = update_height(temp.left, file);
        int right_height = update_height(temp.right, file);
        
        temp.height = std::max(left_height, right_height) + 1;
        
        file.seekp(record_pos * sizeof(NodeBT)); // Nos ubicamos en la posición 
        file.write(reinterpret_cast<const char*>(&temp), sizeof(NodeBT));
        
        return temp.height;
    }
}

template<typename Record>
void AVLFile<Record>::update_balance_factor(long record_pos, std::fstream &file) {
    if (record_pos != -1) {
        NodeBT temp;
        file.seekg(record_pos * sizeof(NodeBT)); // Nos ubicamos en la posición 
        file.read(reinterpret_cast<char*>(&temp), sizeof(NodeBT));
        
        int left_height = get_height(temp.left, file);
        int right_height = get_height(temp.right, file);
        
        temp.balance_factor = right_height - left_height;
        
        file.seekp(record_pos * sizeof(NodeBT)); // Nos ubicamos en la posición 
        file.write(reinterpret_cast<const char*>(&temp), sizeof(NodeBT));
        
        update_balance_factor(temp.left, file);
        update_balance_factor(temp.right, file);
    }
}

template<typename Record>
long AVLFile<Record>::balance(long record_pos, std::fstream &file) {
    NodeBT temp;
    file.seekg(record_pos * sizeof(NodeBT)); // Nos ubicamos en la posición 
    file.read(reinterpret_cast<char*>(&temp), sizeof(NodeBT));
    
    if (temp.balance_factor > 1) {
        NodeBT right_child;
        file.seekg(temp.right * sizeof(NodeBT)); // Nos ubicamos en la posición 
        file.read(reinterpret_cast<char*>(&right_child), sizeof(NodeBT));
        
        if (right_child.balance_factor < 0) {
            temp.right = rotate_right(right_child, file);
        }
        record_pos = rotate_left(temp, file);
    } else if (temp.balance_factor < -1) {
        NodeBT left_child;
        file.seekg(temp.left * sizeof(NodeBT)); // Nos ubicamos en la posición 
        file.read(reinterpret_cast<char*>(&left_child), sizeof(NodeBT));
        
        if (left_child.balance_factor > 0) {
            temp.left = rotate_left(left_child, file);
        }
        record_pos = rotate_right(temp, file);
    } else {
        record_pos = temp_pos;
    }
    
    return record_pos;
}
