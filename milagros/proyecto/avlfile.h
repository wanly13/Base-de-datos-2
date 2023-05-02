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
        Record result = find(file, this->root, animeid); // El root puede cambiar o solo es -1 cuando no tiene valores el archivo?
        file.close();
        return result;
    }

    void insert(Record& record) {
        std::fstream file(this->filename, std::ios::in|std::ios::out|std::ios::binary | std::ios::app);
        insert(file, this->root, record , true);
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
    void insert(std::fstream &file , long &node_pos, Record &value , bool sit);

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

    void valid_balance_recursive(std::fstream &file, long record_pos);
    // otros
    //long height(std::fstream& file, long node);
    void rotateLeft(std::fstream& file, long& node) ;
    void rotateRight(std::fstream& file, long& node);
    void writeNode(std::fstream& file, long pos, const NodeBT& node);
    AVLFile::NodeBT readNode(std::fstream& file, long pos);
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

/* void AVLFile:: valid_balance_recursive(std::fstream &file, long record_pos) {
    NodeBT parent;
    file.seekg(record_pos * sizeof(NodeBT));
    file.read((char*)&parent, sizeof(NodeBT));

    if(parent.)
}
 */

/* void AVLFile::insert(std::fstream& file, long& node, Record& record) {
    if (node == -1) {
        file.seekp(0, ios::end); // Necesario
        node = file.tellp(); // Obtenemos la posición actual del cursor en el archivo
        cout<< "Ubicacion a insertar: " << node << endl;       
        NodeBT newNode(record);
        newNode.pos = node; // Guardamos la posición del registro en el archivo
        //newNode.print_node();
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
} */

void AVLFile::insert(std::fstream& file, long& node, Record& record , bool sit) {
    if (node == -1) {
        file.seekp(0, ios::end); // Necesario
        node = file.tellp(); // Obtenemos la posición actual del cursor en el archivo
        cout<< "Ubicacion a insertar: " << node << endl;       
        NodeBT newNode(record);
        newNode.pos = node; // Guardamos la posición del registro en el archivo
        //newNode.print_node();
        cout<<"Donde se escribe el registro: "<<file.tellg()<<endl;

        file.write((char*)&newNode, sizeof(NodeBT)); // Escribimos el nuevo nodo en el archivo

        cout<<"Despues de escribir: "<<file.tellg()<<endl;

        if(node > 0) {
            long padre_pos = node - sizeof(NodeBT);
            NodeBT parent;// Leemos el node actual anterior
            file.seekg(padre_pos , ios::beg);
            file.read((char*)&parent, sizeof(NodeBT));
            (sit) ? parent.left = node : parent.right = node;
            file.seekp(padre_pos, ios::beg);
            file.write((char*)&parent, sizeof(NodeBT));
        }
    } else {
        NodeBT currentNode;// Leemos el node actual anterior
        file.seekg(node , ios::beg);
        file.read((char*)&currentNode, sizeof(NodeBT));
        if (record.anime_id == currentNode.data.anime_id) {
            std::cout << "El registro ya existe en el árbol" << std::endl;
            return;
        } else if (record.anime_id < currentNode.data.anime_id) {
            insert(file, currentNode.left, record , true); 

        } else {
            insert(file, currentNode.right, record , false); 

        }
        // Actualizamos la altura del nodo actual
        //update_height( file , node);
        currentNode.height = std::max(height(file, currentNode.left), height(file, currentNode.right)) + 1;
        // Rebalanceamos el árbol si es necesario
        balance(file, node);
        // Guardamos los cambios en el archivo
       /*  file.seekp(node , ios::beg);
        file.write((char*)&currentNode, sizeof(NodeBT)); */
    }
}


long AVLFile::height(std::fstream& file, long node) {

    if (node == -1) {
        return -1; // Si el nodo es nulo, su altura es 0
    } else {
        NodeBT currentNode;
        file.seekg(node);
        file.read((char*)&currentNode, sizeof(NodeBT));
        cout<<"height: "<<currentNode.height<<endl;
        return currentNode.height; 
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
  
    // Leemos los datos desde el archivo
    NodeBT node;
    file.seekg(record_pos * sizeof(NodeBT));
    file.read((char*)&node, sizeof(NodeBT));

    node.height = max (height(file , node.left) , height (file , node.right) ) + 1;

    cout<<"guardamos en: "<<record_pos * sizeof(NodeBT) + offsetof(NodeBT, height);
   /*  file.seekp(record_pos * sizeof(NodeBT) + offsetof(NodeBT, height));//offsetof : guarda el desplazamiento, en este caso guarda el desplazamiento de height
    file.write((char*)&node.height, sizeof(node.height)); */
}

/* long AVLFile:: height (std::fstream& file , long record_pos ) {
    if (record_pos == -1) {
        return 0; // Si el nodo es nulo, su altura es 0
    } else {
        NodeBT currentNode;
        file.seekg(record_pos);
        cout<<"height: "<<record_pos<<endl;

        file.read((char*)&currentNode, sizeof(NodeBT));
        return currentNode.height; // Si el nodo no es nulo, su altura es el valor del campo "height" del nodo
    }
} */

long AVLFile::calculate_balance_factor(std::fstream& file , NodeBT node ){
    long balance_factor = height(file , node.left) - height(file , node.right);
    //cout<<"hl - hr: " << height(file , node.left) << " - " <<height(file , node.right) << endl;
    return balance_factor;
}

void AVLFile::balance( std::fstream &file , long &node_pos) {
    cout<<"...Balanceamos..."<<endl;

    NodeBT node;
    //file.seekg(node_pos * sizeof(NodeBT));
    file.seekg(node_pos , ios::beg);

    file.read((char*)&node, sizeof(NodeBT));// Empaquetado para el read
    // Obtenemos el factor de balanceo
    long factor_balanceo = calculate_balance_factor( file , node);
    cout<<"factor_balanceo: "<<factor_balanceo<<endl;

    if (factor_balanceo > 2) { // el nodo está desequilibrado hacia la izquierda
        NodeBT left_node;
        //file.seekg(node.left * sizeof(NodeBT));
        file.seekg(node.left, ios::beg);
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
        //file.seekg(node.right * sizeof(NodeBT));
        file.seekg(node.right, ios::beg);
        file.read((char*)&right_node, sizeof(NodeBT));
        if (height(file , right_node.right) >= height( file , right_node.left)) { // rotación simple a la izquierda
            left_rotation( file ,node_pos);
        }
        else { // rotación doble: derecha-izquierda
            right_rotation( file ,right_node.right);
            left_rotation( file ,node_pos);
        }
    }
    //update_height(file , node_pos); // Actualizamos las alturas
    node.height = 1 + std::max(height(file, node.left), height(file, node.right));

    // Verificacion de balanceo
    if (node_pos != this -> root) {
        NodeBT parent;
        file.seekg(node_pos , ios::beg);
        file.read((char*)&parent, sizeof(NodeBT));
        balance( file , (node_pos == parent.left) ? parent.left : parent.right);
    }
    //valid_balance_recursive(file , node_pos);

}

/* void AVLFile::balance(std::fstream& file, long& node) {
    cout<<"...Balanceamos..."<<endl;
    NodeBT currentNode;
    file.seekg(node);
    file.read((char*)&currentNode, sizeof(NodeBT));

    // Obtenemos las alturas de los subárboles izquierdo y derecho
    long heightLeft = height(file, currentNode.left);
    long heightRight = height(file, currentNode.right);
    cout<<"hl - hr: " << heightLeft << " - " <<heightRight << endl;

    // Calculamos el factor de balance del nodo actual
    long balanceFactor = heightRight - heightLeft;
    cout<<"indice: " << balanceFactor<< endl;

    // Si el factor de balance está fuera de los límites (-1, 0, 1), el árbol está desequilibrado
    if (balanceFactor < -1 || balanceFactor > 1) {
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
} */
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
