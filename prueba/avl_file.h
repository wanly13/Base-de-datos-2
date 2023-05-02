class AVL {
public:
    // Estructura para los registros
    struct Record {
        int anime_id;
        char name[110];
        char type[7];
        int episodes;
        float rating;
        int members;
    };
    
    // Constructor que recibe el nombre del archivo
    AVL(string filename);
    
    // Inserta un registro en el árbol
    void insert(Record record);
    
private:
    // Estructura de los nodos del árbol
    struct Node {
        Record record;
        Node* left;
        Node* right;
        int height;
    };
    
    // Raíz del árbol
    Node* root;
    
    // Nombre del archivo
    string filename;
    
    // Métodos privados para balancear el árbol
    int height(Node* node);
    int balance_factor(Node* node);
    Node* rotate_left(Node* node);
    Node* rotate_right(Node* node);
    Node* rotate_left_right(Node* node);
    Node* rotate_right_left(Node* node);
    void balance(Node* node);
    
    // Método privado para escribir un registro en el archivo
    void write_record(fstream& file, Record record);
    
    // Método privado para leer un registro del archivo
    Record read_record(fstream& file, int offset);
};

void AVL::insert(Record record) {
    // Abrir el archivo en modo lectura y escritura
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        // Si no se puede abrir el archivo, lanzar una excepción
        throw runtime_error("No se pudo abrir el archivo");
    }
    
    // Calcular el tamaño del archivo y la posición donde se va a insertar el registro
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    int record_offset = file_size;
    
    // Escribir el registro en el archivo
    write_record(file, record);
    
    // Insertar el registro en el árbol AVL
    Node* new_node = new Node;
    new_node->record = record;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->height = 1;
    root = insert_node(root, new_node);
    
    // Escribir la posición del registro en el archivo en el campo "offset" del registro
    file.seekp(record_offset + offsetof(Record, offset));
    file.write(reinterpret_cast<char*>(&record_offset), sizeof(record_offset));
    
    // Cerrar el archivo
    file.close();
}


