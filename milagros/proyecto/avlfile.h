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
public:
    struct NodeBT {
        Record data;
        long left;
        long right;
        long height;
        long pos ;
        NodeBT() {
            left = right = -1;
            height = 0;
        }
        NodeBT(Record &record) {
            this->data = record;
            left = right = -1;
            height = 0;
        }
        void print_node(){
            cout<<"Insertar -> ";
            cout << data.anime_id << " | " << data.name << " | ";
            cout<< "L("<<left << ") | R(" << right << ") | H(" << height << ") | P("<<pos<<") | "<<endl;
        }
       /*  void killSelf(){
            if(left != -1) left->killSelf();
            if(right != -1) right->killSelf();
            delete this;
        }  */
    };

private:
    long root;
    std::string filename;

public:
    AVLFile() : root(-1) {};
    AVLFile(string filename){
        this->filename = filename;
        this-> root = -1;
    }
    string getFileName() {
        return this->filename;
    }
    void getDates(){
        cout<<root<<endl;
    }
    void set_filename (string filename){ this->filename = filename;}

    Record find(int animeid) {
        std::ifstream file(this->filename, std::ios::binary);
        cout<<"root que pasa: "<<this->root<<endl;
        Record result = find(file, this->root, animeid); // El root puede cambiar o solo es -1 cuando no tiene valores el archivo?
        result.get_data();
        file.close();
        return result;
    }

    void insert(Record& record) {
        std::fstream file(this->filename, std::ios::in|std::ios::out|std::ios::binary );
        //insert(file, this->root, record , true);
        insert(file, this->root, record );
        file.close();
    }

    void remove(int anime_id) {
        std::fstream file(this->filename, std::ios::in|std::ios::out|std::ios::binary );
        remove(file, this -> root, anime_id);
        file.close();
    }


   /*  Record search (Record key){
        std::ifstream file(this->filename, std::ios::binary);
        Record result = search(file, this->root, key.anime_id);
        file.close();
        return result;
    } */

    vector<Record> rangeSearch(int begin_key, int end_key) {
        vector<Record> results;
        fstream file(filename, ios::in | ios::binary);
        if (file) {
            rangeSearch(file, root, begin_key, end_key, results);
            file.close();
        } else {
            cout << "Error al abrir el archivo " << filename << endl;
        }
        return results;
    }

private:
    // FUNCTIONS TO USE
    //vector<Record> search(std::ifstream &file ,long record_pos, int animeid);

    void rangeSearch(fstream &file, long node, int begin_key, int end_key, vector<Record> &results);

    Record search(std::fstream &file, long& record_pos, int key);
    
    void insert(std::fstream &file, long& record_pos , Record& record);
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

    void remove(std::fstream& file, long& record_pos, int value);

    Record find(std::ifstream &file, long record_pos, int value);

    void valid_balance_recursive(std::fstream &file, long record_pos);
    // otros
    //long height(std::fstream& file, long node);
    void rotateLeft(std::fstream& file, long& node) ;
    void rotateRight(std::fstream& file, long& node);
    void writeNode(std::fstream& file, long pos, const NodeBT& node);
    AVLFile::NodeBT readNode(std::fstream& file, long pos);
    AVLFile::NodeBT find_predecessor(std::fstream& file, long& record_pos, NodeBT& predecessor);
    
    AVLFile::NodeBT find_max(std::fstream& file, long record_pos);
};

// ------------------ IMPLEMENTATIONS ------------------

Record AVLFile::find(std::ifstream &file, long record_pos, int value){
    NodeBT temp;
    file.seekg(record_pos ); // Nos ubicamos en la posición actual
    file.read((char*)&temp, sizeof(NodeBT));

    if (temp.pos == -1) {
        // El archivo está vacío o no se encontró el valor buscado
        return Record(); // Retorna un registro vacío
    }

    if (value < temp.data.anime_id)
        return find(file, temp.left, value);
    else if (value > temp.data.anime_id)
        return find(file, temp.right, value);
    else
        return temp.data;
}

void AVLFile::insert(std::fstream& file, long& node, Record& record) {
    if (node == -1) {
        file.seekp(0, ios::end); // Necesario
        node = file.tellp(); // Obtenemos la posición actual del cursor en el archivo
        if(file.tellp() == 0) {
            node = -1;
        } else node = file.tellp();
       /*  if (this -> root == -1) {
                // Si es el primer nodo, asignar su posición al atributo de la raíz
                this -> root = node;
                //file.seekp(0, ios::beg);
                //file.write((char*)&root, sizeof(long));
        } */
        /* this -> root = node; */
        cout<<"root es: "<<this -> root<<endl;
        cout<< "Ubicacion a insertar: " << node << endl;       
        NodeBT newNode(record);
        newNode.pos = node; // Guardamos la posición del registro en el archivo
        newNode.print_node();
        file.write((char*)&newNode, sizeof(NodeBT)); // Escribimos el nuevo nodo en el archivo
    } else {
        NodeBT currentNode;// Leemos el node actual anterior
        file.seekg(node , ios::beg);
        file.read((char*)&currentNode, sizeof(NodeBT));
        if (record.anime_id == currentNode.data.anime_id) {
            std::cout << "El registro ya existe en el árbol" << std::endl;
            return;
        } else if (record.anime_id < currentNode.data.anime_id) {
            insert(file, currentNode.left, record); 

        } else {
            insert(file, currentNode.right, record); 

        }
        // Actualizamos la altura del nodo actual
        //update_height( file , node);
        currentNode.height = std::max(height(file, currentNode.left), height(file, currentNode.right)) + 1;
        // Rebalanceamos el árbol si es necesario
        balance(file, node);
        // Guardamos los cambios en el archivo
        file.seekp(node , ios::beg);
        file.write((char*)&currentNode, sizeof(NodeBT));
    }
}

long AVLFile::height(std::fstream& file, long node) {

    if (node == -1) {
        return 0; // Si el nodo es nulo, su altura es 0
    } else {
        NodeBT currentNode;
        file.seekg(node , ios::beg);
        file.read((char*)&currentNode, sizeof(NodeBT));
        //cout<<"height: "<<currentNode.height<<endl;
        return currentNode.height; 
    }
}

void AVLFile::remove(std::fstream& file, long& record_pos, int value) {
    /* if (record_pos == -1) record_pos = 0;
    if (record_pos == -1) {
        std::cout << "El registro no se encuentra en el árbol" << std::endl;
        return;
    } */
    NodeBT current_node;
    file.seekg(record_pos, std::ios::beg);
    file.read((char*)&current_node, sizeof(NodeBT));
    if (value < current_node.data.anime_id) {
        remove(file, current_node.left, value);
    } else if (value > current_node.data.anime_id) {
        remove(file, current_node.right, value);
    } else {
        // Caso en el que se encuentra el valor a eliminar
        if (current_node.left == -1 && current_node.right == -1) {
            // Caso 1: El nodo a eliminar es una hoja
            record_pos = -1;
            balance(file, record_pos);
            file.seekp(0, std::ios::beg);
            file.write((char*)&root, sizeof(long));
        } else if (current_node.left == -1 || current_node.right == -1) {
            // Caso 2: El nodo a eliminar tiene un solo hijo
            record_pos = (current_node.left != -1) ? current_node.left : current_node.right;
            balance(file, record_pos);
            file.seekp(0, std::ios::beg);
            file.write((char*)&root, sizeof(long));
        } else {
            // Caso 3: El nodo a eliminar tiene dos hijos
            NodeBT predecessor;
            find_predecessor(file, current_node.left, predecessor);
            current_node.data = predecessor.data;
            remove(file, current_node.left, predecessor.data.anime_id);
            file.seekp(record_pos, std::ios::beg);
            file.write((char*)&current_node, sizeof(NodeBT));
        }
    }
    // Actualizamos la altura del nodo actual
    current_node.height = std::max(height(file, current_node.left), height(file, current_node.right)) + 1;
    // Rebalanceamos el árbol si es necesario
    balance(file, record_pos);
    // Guardamos los cambios en el archivo
    file.seekp(record_pos, std::ios::beg);
    file.write((char*)&current_node, sizeof(NodeBT));
}

AVLFile::NodeBT AVLFile::find_predecessor(std::fstream& file, long& record_pos, NodeBT& predecessor) {
    NodeBT currentNode;
    file.seekg(record_pos); // Nos ubicamos en el nodo actual
    file.read((char*)&currentNode, sizeof(NodeBT));

    // Si hay un subárbol izquierdo, el predecesor es el nodo más grande de ese subárbol
    if (currentNode.left != -1) {
        return find_max(file, currentNode.left);
    }

    // Si no hay un subárbol izquierdo, buscamos el primer ancestro que sea el hijo derecho de su padre
    // El predecesor es el padre de ese nodo
    while (true) {
        long parent_pos = currentNode.pos;
        if (parent_pos == -1) {
            // No hay predecesor
            return NodeBT();
        }
        NodeBT parent;
        file.seekg(parent_pos); // Nos ubicamos en el padre del nodo actual
        file.read((char*)&parent, sizeof(NodeBT));
        if (parent.right == record_pos) {
            // El nodo actual es el hijo derecho del padre
            // El predecesor es el padre
            predecessor = parent;
            return parent;
        }
        // Si no es el hijo derecho, seguimos subiendo en el árbol
        currentNode = parent;
        record_pos = parent_pos;
    }
}

AVLFile::NodeBT AVLFile::find_max(std::fstream& file, long record_pos) {
    NodeBT currentNode;
    file.seekg(record_pos); // Nos ubicamos en el nodo actual
    file.read((char*)&currentNode, sizeof(NodeBT));

    while (currentNode.right != -1) {
        // Seguimos bajando por el subárbol derecho
        file.seekg(currentNode.right);
        file.read((char*)&currentNode, sizeof(NodeBT));
    }

    return currentNode;
}


void AVLFile::rangeSearch(fstream &file, long node, int begin_key, int end_key, vector<Record> &results) {
    if (node == -1) {
        return;
    }
    NodeBT current;
    file.seekg(node);
    file.read((char*)&current, sizeof(NodeBT));
    if (current.data.anime_id >= begin_key && current.data.anime_id <= end_key) {
        results.push_back(current.data);
    }
    if (current.data.anime_id > begin_key) {
        rangeSearch(file, current.left, begin_key, end_key, results);
    }
    if (current.data.anime_id < end_key) {
        rangeSearch(file, current.right, begin_key, end_key, results);
    }
}

Record AVLFile::search(std::fstream &file, long& record_pos, int key) {
    if (record_pos == -1)
        throw "El archivo se encuentra vacío";

    NodeBT temp;
    file.seekg(record_pos);
    file.read((char*)&temp, sizeof(NodeBT));

    if (key == temp.data.anime_id)
        return temp.data;
    else if (key < temp.data.anime_id && temp.left != -1)
        return search(file, temp.left, key);
    else if (key > temp.data.anime_id && temp.right != -1)
        return search(file, temp.right, key);
    else
        throw "El elemento no fue encontrado";
}


void AVLFile::update_height(std::fstream& file, long record_pos) {
  
    // Leemos los datos desde el archivo
    NodeBT node;
    file.seekg(record_pos * sizeof(NodeBT));
    file.read((char*)&node, sizeof(NodeBT));

    node.height = max (height(file , node.left) , height (file , node.right) ) + 1;

    cout<<"guardamos en: "<<record_pos * sizeof(NodeBT) + offsetof(NodeBT, height);
   /*  file.seekp(record_pos * sizeof(NodeBT) + offsetof(NodeBT, height));//offsetof : guarda el desplazamiento, en este caso guarda el desplazamiento de height
    file.write((char*)&node.height, sizeof(node.height)); */
}


long AVLFile::calculate_balance_factor(std::fstream& file , NodeBT node ){
    long balance_factor = height(file , node.left) - height(file , node.right);
    //cout<<"hl - hr: " << height(file , node.left) << " - " <<height(file , node.right) << endl;
    return balance_factor;
}

void AVLFile::balance(std::fstream& file, long& node) {
    
    NodeBT currentNode;
    file.seekg(node);
    file.read((char*)&currentNode, sizeof(NodeBT));

    // Obtenemos las alturas de los subárboles izquierdo y derecho
    long heightLeft = height(file, currentNode.left);
    long heightRight = height(file, currentNode.right);
    cout<<"hl - hr: (" << heightLeft << ") - (" <<heightRight <<")"<< endl;

    // Calculamos el factor de balance del nodo actual
    long balanceFactor = heightRight - heightLeft;
    cout<<"indice: " << balanceFactor<< endl;

    // Si el factor de balance está fuera de los límites (-1, 0, 1), el árbol está desequilibrado
    if (balanceFactor < -1 || balanceFactor > 1) {
        cout<<"...Balanceamos..."<<endl;
        // Si el subárbol derecho es más alto, realizamos una rotación simple o doble hacia la izquierda
        if (balanceFactor > 0) {
            NodeBT rightNode;
            file.seekg(currentNode.right);
            file.read((char*)&rightNode, sizeof(NodeBT));

            long heightRightLeft = height(file, rightNode.left);
            long heightRightRight = height(file, rightNode.right);

            if (heightRightLeft > heightRightRight) {
                rotateRight(file, currentNode.right);
            }

            rotateLeft(file, node);

        // Si el subárbol izquierdo es más alto, realizamos una rotación simple o doble hacia la derecha
        } else {
            NodeBT leftNode;
            file.seekg(currentNode.left);
            file.read((char*)&leftNode, sizeof(NodeBT));

            long heightLeftLeft = height(file, leftNode.left);
            long heightLeftRight = height(file, leftNode.right);

            if (heightLeftRight > heightLeftLeft) {
                rotateLeft(file, currentNode.left);
            }

            rotateRight(file, node);
        }

        // Después de la rotación, actualizamos las alturas del nodo y sus hijos
        currentNode.height = 1 + std::max(height(file, currentNode.left), height(file, currentNode.right));

        NodeBT leftChild, rightChild;
        file.seekg(currentNode.left);
        file.read((char*)&leftChild, sizeof(NodeBT));
        file.seekg(currentNode.right);
        file.read((char*)&rightChild, sizeof(NodeBT));

        leftChild.height = 1 + std::max(height(file, leftChild.left), height(file, leftChild.right));
        rightChild.height = 1 + std::max(height(file, rightChild.left), height(file, rightChild.right));

        file.seekp(currentNode.pos);
        file.write((char*)&currentNode, sizeof(NodeBT));
        file.seekp(leftChild.pos);
        file.write((char*)&leftChild, sizeof(NodeBT));
        file.seekp(rightChild.pos);
        file.write((char*)&rightChild, sizeof(NodeBT));
    }
}
void AVLFile::rotateLeft(std::fstream& file, long& node) {
    NodeBT tmpNode = readNode(file, node);
    NodeBT rightNode = readNode(file, tmpNode.right);
    
    tmpNode.right = rightNode.left;
    rightNode.left = node;

    tmpNode.height = 1 + std::max(height(file, tmpNode.left), height(file, tmpNode.right));
    rightNode.height = 1 + std::max(height(file, rightNode.left), height(file, rightNode.right));
    
    writeNode(file, node, rightNode);
    writeNode(file, tmpNode.pos, tmpNode);
    node = rightNode.pos;
}
void AVLFile::rotateRight(std::fstream& file, long& node) {
    NodeBT tmpNode = readNode(file, node);
    NodeBT leftNode = readNode(file, tmpNode.left);
    
    tmpNode.left = leftNode.right;
    leftNode.right = node;

    tmpNode.height = 1 + std::max(height(file, tmpNode.left), height(file, tmpNode.right));
    leftNode.height = 1 + std::max(height(file, leftNode.left), height(file, leftNode.right));
    
    writeNode(file, node, leftNode);
    writeNode(file, tmpNode.pos, tmpNode);
    node = leftNode.pos;
}
void AVLFile::writeNode(std::fstream& file, long pos, const NodeBT& node) {
    file.seekp(pos * sizeof(NodeBT));
    file.write(reinterpret_cast<const char*>(&node), sizeof(NodeBT));
}

AVLFile::NodeBT AVLFile::readNode(std::fstream& file, long pos) {
    NodeBT node;
    file.seekg(pos * sizeof(NodeBT));
    file.read(reinterpret_cast<char*>(&node), sizeof(NodeBT));
    node.pos = pos;
    return node;
}

void AVLFile::left_rotation( std::fstream &file ,long &node_pos) {
    cout<<"left_rotation: "<<endl;
    NodeBT node, right_node;
    // Nos ubicamos en la posicion del nodo
    //file.seekg(node_pos * sizeof(NodeBT));
    file.seekg(node_pos );
    file.read((char*)&node, sizeof(NodeBT)); // leemos el nodo (Empaquetar)

    // Nos ubicamos en la posicion del hijo derecho
    //file.seekg(node.right * sizeof(NodeBT));
    file.seekg(node.right );
    file.read((char*)&right_node, sizeof(NodeBT));// leemos al hijo (Empaquetar)

    node.right = right_node.left;
    right_node.left = node_pos;

    node.height =  std::max(height(file , node.left), height(file , node.right)) + 1 ;
    right_node.height =  std::max(height(file , right_node.left), height(file , right_node.right)) + 1 ;

    //file.seekp(node_pos * sizeof(NodeBT)); 
    file.seekp(node_pos );  
    file.write((char*)&node, sizeof(NodeBT));

    //file.seekp(right_node.pos  * sizeof(NodeBT)); 
    file.seekp(right_node.pos); 
    file.write((char*)&right_node, sizeof(NodeBT));
    node_pos = right_node.pos ;
}

void AVLFile::right_rotation( std::fstream &file ,long &node_pos) {
    cout<<"right_rotation: "<<endl;
    NodeBT node, left_node;

    //file.seekg(node_pos * sizeof(NodeBT));
    file.seekg(node_pos );
    file.read((char*)&node, sizeof(NodeBT));

    //file.seekg(node.left * sizeof(NodeBT));
    file.seekg(node.left );
    file.read((char*)&left_node, sizeof(NodeBT));

    node.left = left_node.right;
    left_node.right = node_pos;

    node.height =  std::max(height(file , node.left), height(file , node.right)) + 1 ;
    left_node.height =  std::max(height(file , left_node.left), height( file , left_node.right)) + 1;

    //file.seekp(node_pos * sizeof(NodeBT));
    file.seekp(node_pos );
    file.write((char*)&node, sizeof(NodeBT));

    //file.seekp(left_node.pos * sizeof(NodeBT));
    file.seekp(left_node.pos );
    file.write((char*)&left_node, sizeof(NodeBT));

    node_pos = left_node.pos;
}

#endif //RECORDLECTURE_AVLFILE_H
