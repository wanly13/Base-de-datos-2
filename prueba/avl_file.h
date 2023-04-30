void AVL::insert(const Record& record) {
    Node* new_node = new Node(record);

    if (root == nullptr) {
        root = new_node;
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (true) {
        if (current == nullptr) {
            if (compare_records(record, parent->data) < 0) {
                parent->left = new_node;
            } else {
                parent->right = new_node;
            }
            new_node->parent = parent;

            update_heights(new_node);
            rebalance(new_node);
            break;
        }
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

        parent = current;

        if (compare_records(record, current->data) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    num_records++;
}
