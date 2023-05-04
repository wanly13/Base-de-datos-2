#ifndef AVLTree_H
#define AVLTree_H
#include "node.h"
#include <string>
#include <cmath>

using namespace std;

template <typename T>
class AVLTree
{
private:
    NodeBT<T> *root;

public:
    AVLTree() : root(nullptr) {}
    void insert(T value)
    {
        insert(this->root, value);
    }
    bool find(T value)
    {
        return find(this->root, value);
    }

    string getPreOrder()
    {
        return getPreOrder(this->root);
    }

    int height()
    {
        return height(this->root);
    }
    T minValue()
    {
        return minValue(this->root);
    }
    T maxValue()
    {
        return maxValue(this->root);
    }
    bool isBalanced()
    {
        return isBalanced(this->root);
    }
    int size()
    {
        return size(this->root);
    }
    void remove(T value)
    {
        remove(this->root, value);
    }
    void displayPretty()
    {
        displayPretty(this->root, 1);
    }

    ~AVLTree()
    {
        if (this->root != nullptr)
        {
            this->root->killSelf();
        }
    }

private:
    string getPreOrder(NodeBT<T> *node);
    void insert(NodeBT<T> *&node, T value); //*
    bool find(NodeBT<T> *node, T value);
    int height(NodeBT<T> *node);      //*
    bool isBalanced(NodeBT<T> *node); //*
    T minValue(NodeBT<T> *node);
    T maxValue(NodeBT<T> *node);
    int size(NodeBT<T> *node);
    void remove(NodeBT<T> *&node, T value); //*
    void displayPretty(NodeBT<T> *node, int level);

    /*add for avl*/
    int balancingFactor(NodeBT<T> *node);
    void updateHeight(NodeBT<T> *node);
    void balance(NodeBT<T> *&node);
    void left_rota(NodeBT<T> *&node);
    void right_rota(NodeBT<T> *&node);
    void right_left_rota(NodeBT<T> *&node);
    void left_right_rota(NodeBT<T> *&node);
    //
    void recursiveUpdateHeight(NodeBT<T> *&node);
};

//============================Implementación=====================================

template <typename T>
void AVLTree<T>::recursiveUpdateHeight(NodeBT<T> *&node)
{
    if (node == nullptr)
        return;
    if (node->left != nullptr)
        recursiveUpdateHeight(node->left);
    if (node->right != nullptr)
        recursiveUpdateHeight(node->right);
    updateHeight(node);
}
/* 
void AVLTree<T>::balanceRecursive(long &node_pos, std::fstream &file) {
    NodeBT node;
    file.seekg(node_pos * sizeof(NodeBT));
    file.read((char*)&node, sizeof(NodeBT));
    int balance_factor = height(node.left) - height(node.right);
    if (balance_factor > 1) { // el nodo está desequilibrado hacia la izquierda
        NodeBT left_node;
        file.seekg(node.left * sizeof(NodeBT));
        file.read((char*)&left_node, sizeof(NodeBT));
        if (height(left_node.left) >= height(left_node.right)) { // rotación simple a la derecha
            rotateRight(node_pos, file);
        }
        else { // rotación doble: izquierda-derecha
            rotateLeft(left_node.left, file);
            rotateRight(node_pos, file);
        }
        // Actualización de altura
        updateHeight(node_pos, file);
        // Verificación de balanceo recursiva
        if (node_pos != root_pos) {
            NodeBT parent;
            file.seekg(node_pos * sizeof(NodeBT));
            file.read((char*)&parent, sizeof(NodeBT));
            balanceRecursive((node_pos == parent.left) ? parent.left : parent.right, file);
        }
    }
    else if (balance_factor < -1) { // el nodo está desequilibrado hacia la derecha
        NodeBT right_node;
        file.seekg(node.right * sizeof(NodeBT));
        file.read((char*)&right_node, sizeof(NodeBT));
        if (height(right_node.right) >= height(right_node.left)) { // rotación simple a la izquierda
            rotateLeft(node_pos, file);
        }
        else { // rotación doble: derecha-izquierda
            rotateRight(right_node.right, file);
            rotateLeft(node_pos, file);
        }
        // Actualización de altura
        updateHeight(node_pos, file);
        // Verificación de balanceo recursiva
        if (node_pos != root_pos) {
            NodeBT parent;
            file.seekg(node_pos * sizeof(NodeBT));
            file.read((char*)&parent, sizeof(NodeBT));
            balanceRecursive((node_pos == parent.left) ? parent.left : parent.right, file);
        }
    }
    else { // el nodo está equilibrado
        // Actualización de altura
        updateHeight(node_pos, file);
        // Verificación de balanceo recursiva
        if (node_pos != root_pos) {
            NodeBT parent;
            file.seekg(node_pos * sizeof(NodeBT));
            file.read((char*)&parent, sizeof(NodeBT));
            balanceRecursive((node_pos == parent.left) ? parent.left : parent.right, file);
        }
    }
}

 */
template <typename T>
string AVLTree<T>::getPreOrder(NodeBT<T> *node)
{
    if (node == nullptr)
        return "";
    string result = "";
    result += std::to_string(node->data) + " ";
    result += getPreOrder(node->left);
    result += getPreOrder(node->right);
    return result;
}

template <typename T>
void AVLTree<T>::insert(NodeBT<T> *&node, T value) //*
{
    if (node == nullptr)
    {
        node = new NodeBT<T>(value);
    }
    else if (value < node->data)
        insert(node->left, value);
    else
        insert(node->right, value);
    updateHeight(node);
    balance(node);
}

template <typename T>
bool AVLTree<T>::find(NodeBT<T> *node, T value){
    if (node == nullptr)
        return false;
    else if (value < node->data)
        return find(node->left, value);
    else if (value > node->data)
        return find(node->right, value);
    else
        return true;
}

template <typename T>
int AVLTree<T>::height(NodeBT<T> *node) //*
{
    if (node == nullptr)
        return -1;
    else
        return node->height;
}

template <typename T>
bool AVLTree<T>::isBalanced(NodeBT<T> *node) //*
{
    if (node == nullptr)
        return true;
    int th = height(node->left);
    int rh = height(node->right);
    if (abs(th - rh) <= 1 && isBalanced(node->left) && isBalanced(node->right))
        return true;
    return false;
}

template <typename T>
T AVLTree<T>::minValue(NodeBT<T> *node)
{
    NodeBT<T> *temp = node;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return (temp->data);
}

template <typename T>
T AVLTree<T>::maxValue(NodeBT<T> *node)
{
    NodeBT<T> *temp = node;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return (temp->data);
}

template <typename T>
int AVLTree<T>::size(NodeBT<T> *node)
{
    if (node == NULL)
        return 0;
    return size(node->left) + size(node->right) + 1;
}

template <typename T>
void AVLTree<T>::remove(NodeBT<T> *&node, T value) //*
{
    if (node == nullptr)
        return;
    else if (value < node->data)
        remove(node->left, value);
    else if (value > node->data)
        remove(node->right, value);
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node; // free
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            T temp = maxValue(node->left);
            node->data = temp;
            remove(node->left, temp);
        }
    }
    updateHeight(node);
    balance(node);
}

template <typename T>
void AVLTree<T>::displayPretty(NodeBT<T> *node, int level)
{
    if (node == nullptr)
        return;
    displayPretty(node->right, level + 1);
    cout << endl;
    if (node == this->root)
        cout << " ROOT -> ";
    else
    {
        for (int i = 0; i < level; i++)
            cout << "         ";
    }
    cout << node->data << " ";
    displayPretty(node->left, level + 1);
}

/*add for avl*/

template <typename T>
int AVLTree<T>::balancingFactor(NodeBT<T> *node)
{
    return height(node->left) - height(node->right);
}

template <typename T>
void AVLTree<T>::updateHeight(NodeBT<T> *node)
{
    if (node == nullptr)
        return;
    node->height = max(height(node->left), height(node->right)) + 1;
}

template <typename T>
void AVLTree<T>::balance(NodeBT<T> *&node)
{
    bool b = false;
    if (node == nullptr)
        return;
    int fb = balancingFactor(node);
    if (fb >= 2)
    {
        b = true;
        if (balancingFactor(node->left) <= -1)
            left_rota(node->left);
        right_rota(node);
    }
    if (fb <= -2)
    {
        b = true;
        if (balancingFactor(node->right) >= 1)
            right_rota(node->right);
        left_rota(node);
    }
    if (b)
        recursiveUpdateHeight(node);
}


template <typename T>
void AVLTree<T>::left_rota(NodeBT<T> *&node)
{
    NodeBT<T> *z = node->right;
    node->right = z->left;
    z->left = node;
    node = z;
}

template <typename T>
void AVLTree<T>::right_rota(NodeBT<T> *&node)
{
    NodeBT<T> *z = node->left;
    node->left = z->right;
    z->right = node;
    node = z;
}

template <typename T>
void AVLTree<T>::right_left_rota(NodeBT<T> *&node)
{
    right_rota(node->right);
    left_rota(node);
}

template <typename T>
void AVLTree<T>::left_right_rota(NodeBT<T> *&node)
{
    left_rota(node->left);
    right_rota(node);
}

#endif
