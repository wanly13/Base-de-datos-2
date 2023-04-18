// #ifndef BSTREE_H
// #define BSTREE_H
// #include "node.h"

// using namespace std;
// template <typename T>
// class BSTree
// {
// private:
//     NodeBT<T> *root;

// public:
//     BSTree() : root(nullptr) {}
//     void insert(T value)
//     {
//         insert(this->root, value);
//     }
//     bool find(T value)
//     {
//         return find(this->root, value);
//     }
//     void displayInOrder()
//     {
//         displayInOrder(this->root);
//     }
//     void displayPreOrder()
//     {
//         displayPreOrder(this->root);
//     }
//     void displayPostOrder()
//     {
//         displayPostOrder(this->root);
//     }
//     int height()
//     {
//         return height(this->root);
//     }
//     T minValue()
//     {
//         return minValue(this->root);
//     }
//     T maxValue()
//     {
//         return maxValue(this->root);
//     }
//     bool isBalanced()//O(n^2)
//     {
//         return isBalanced(this->root);
//     }
//     bool isBalancedOptimo()//O(n)
//     {
//         if (this->root == nullptr) return true;
//         return isBalancedOptimo(this->root) != -2;//-2 indica que no esta balanceado
//     }
//     int size()
//     {
//         return size(this->root);
//     }
//     void remove(T value)
//     {
//         remove(this->root, value);
//     }

//     ~BSTree(){
//         if(this->root != nullptr){
//             this->root->killSelf();
//         }
//     }

// private:
//     void displayInOrder(NodeBT<T> *node);
//     void displayPreOrder(NodeBT<T> *node);
//     void displayPostOrder(NodeBT<T> *node);
//     void insert(NodeBT<T> *&node, T value);
//     bool find(NodeBT<T> *node, T value);
//     int height(NodeBT<T> *node);
//     bool isBalanced(NodeBT<T> *node);
//     T minValue(NodeBT<T> *node);
//     T maxValue(NodeBT<T> *node);
//     int size(NodeBT<T> *node);
//     void remove(NodeBT<T> *&node, T value);
//     int isBalancedOptimo(NodeBT<T> *node);

// };

// template <typename T>
// void BSTree<T>::insert(NodeBT<T> *&node, T value)
// {
//     if (node == nullptr)
//         node = new NodeBT<T>(value);
//     else if (value < node->data)
//         insert(node->left, value);
//     else
//         insert(node->right, value);              
// }

// template <typename T>
// bool BSTree<T>::find(NodeBT<T> *node, T value)
// {
//     if (node == nullptr)
//         return false;
//     else if (value < node->data)
//         return find(node->left, value);
//     else if (value > node->data)
//         return find(node->right, value);
//     else
//         return true;
// }

// template <typename T>
// int BSTree<T>::height(NodeBT<T> *node)
// {
//     if (node == nullptr)
//         return -1;
//     else
//         return max(height(node->left), height(node->right)) + 1;
// }

// template <typename T>
// bool BSTree<T>::isBalanced(NodeBT<T> *node) //O(n^2)
// {
//     if (node == nullptr)
//         return true;
//     else
//         return abs(height(node->left) - height(node->right)) <= 1 && isBalanced(node->left) && isBalanced(node->right);
// }

// template <typename T>
// int BSTree<T>::isBalancedOptimo(NodeBT<T> *node)//O(n)
// {
//     if (node == nullptr)
//         return -1;
//     else{
//         int hleft = isBalancedOptimo(node->left); 
//         int hright = isBalancedOptimo(node->right);
//         if(hleft == -2 || hright== -2 || abs(hleft - hright) > 1)
//             return -2;//indicador de no-balanceado
//         else
//             return max(hleft,hright) + 1;
//     }
// }

// template <typename T>
// void BSTree<T>::displayPreOrder(NodeBT<T> *node)
// {
//     if (node == nullptr)
//         return;
//     cout << node->data << endl;
//     displayPreOrder(node->left);
//     displayPreOrder(node->right);
// }

// template <typename T>
// void BSTree<T>::displayInOrder(NodeBT<T> *node)
// {
//     if (node == nullptr)
//         return;
//     displayInOrder(node->left);
//     cout << node->data<< endl;
//     displayInOrder(node->right);
// }

// template <typename T>
// void BSTree<T>::displayPostOrder(NodeBT<T> *node)
// {
//     if (node == nullptr)
//         return;
//     displayPostOrder(node->left);
//     displayPostOrder(node->right);
//     cout << node->data<< endl;
// }

// template <typename T>
// T BSTree<T>::minValue(NodeBT<T> *node)
// {
//     if (node == nullptr)
//         throw("The tree is empty");
//     else if (node->left == nullptr)
//         return node->data;
//     else
//         return minValue(node->left);
// }

// template <typename T>
// T BSTree<T>::maxValue(NodeBT<T> *node)
// {
//     if (node == nullptr)
//         throw("The tree is empty");
//     else if (node->right == nullptr)
//         return node->data;
//     else
//         return maxValue(node->right);
// }

// template <typename T>
// int BSTree<T>::size(NodeBT<T> *node)
// {
//     if (node == nullptr)
//         return 0;
//     else
//         return 1 + size(node->left) + size(node->right);
// }

// template <typename T>
void BSTree<T>::remove(NodeBT<T> *&node, T value)
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
            delete node; //free
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
}

// #endif

#ifndef BSTREE_H
#define BSTREE_H

#include "iterator.h"
#include <string>
#include <iostream>
using namespace std;
#include "node.h"

#include <stack>
#include <queue>
template <typename T>
class BSTree
{
public:
    typedef BSTIterator<T> iterator;

private:
    NodeBT<T> *root;
    string inOrder_string;
    string BFS_string;
    string post_string;

public:
    BSTree()
    {
        root = nullptr;
    }
    void insert(T value)
    {
        insert(this->root, value);
    }
    bool find(T value)
    {
        auto trav = root;
        while (true)
        {
            if (trav == nullptr)
            {
                return false;
            }
            else if (value > trav->data)
            {
                trav = trav->right;
            }
            else if (value < trav->data)
            {
                trav = trav->left;
            }
            else if (value == trav->data)
            {
                return true;
            }
        }
    }

    string displayInOrder()
    {
        string vacio;
        displayInOrder(this->root, vacio);
        return vacio;
    }
    string displayPreOrder()
    {
        stack<NodeBT<T> *> guardar;
        guardar.push(root);
        string texto = "";
        while (!guardar.empty())
        {
            NodeBT<T> *tempo = guardar.top();
            texto += to_string(tempo->data);
            texto += " ";
            guardar.pop();
            if (tempo->right != nullptr)
                guardar.push(tempo->right);
            if (tempo->left != nullptr)
                guardar.push(tempo->left);
        }
        return texto;
    }
    string displayPostOrder()
    {
        displayPostOrder(this->root, post_string);
        return post_string;
    }
    // int height();
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
    void remove(T value)
    {
        auto trav = root;
        auto prev = trav;
        bool flag = true;
        while (flag)
        {
            if (value > trav->data)
            {
                prev = trav;
                trav = trav->right;
            }
            else if (value < trav->data)
            {
                prev = trav;
                trav = trav->left;
            }
            else if (value == trav->data)
            {
                // return true; found
                if (trav->right == nullptr && trav->left == nullptr)
                { // it is a leaf
                    // cout << "it is a leaf" << endl;
                    if (prev->left == trav)
                    {
                        prev->left = nullptr;
                    }
                    else if (prev->right == trav)
                    {
                        prev->right = nullptr;
                    }
                    // delete trav;
                    flag = false;
                    // break;
                }
                else if (trav->right != nullptr && trav->left == nullptr)
                {
                    // it has only 1 child
                    // cout <<"it has only one child " << endl;
                    // trav->data = trav->right->data;
                    T data = trav->right->data;
                    remove(trav->right->data);
                    // flag = false;
                    trav->data = data;
                }
                else if (trav->right == nullptr && trav->left != nullptr)
                {
                    // cout <<"it has only one child2 " << endl;
                    // trav->data = trav->left->data;
                    T data = trav->left->data;
                    remove(trav->left->data);
                    // flag = false;
                    trav->data = data;
                    // if(trav->left->data > trav->data){
                    //     trav->right = trav->left;
                    //     trav->left = nullptr;
                    // }
                }
                else if (trav->right != nullptr && trav->left != nullptr)
                {
                    // two child
                    int i = 1;
                    int aux = value - i;
                    while (!find(aux))
                    { // buscar menores
                        i = i + 1;
                        aux = value - i;
                    }
                    remove(aux);
                    trav->data = aux;
                }
                // cout << "so far" << endl;
                if (trav->right != nullptr)
                {
                    if (trav->right->data < trav->data)
                    {
                        // cout << "so far1\n" << endl;
                        T aux = trav->right->data;
                        trav->right = nullptr;
                        insert(aux);
                        // cout << "so far2\n" << endl;
                    }
                }
                flag = false;
            }
        }
    }
    bool isBalanced()
    {
        return isBalanced(this->root);
    }

    int size()
    {
        return size(this->root);
    }
    // int size();
    bool isFull()
    { // es aquel en el que todos los nodos tienen 0 o 2 hijos
        return (isFullt(this->root));
    }
    bool isFullt(NodeBT<T> *&node)
    {
        if (node == nullptr)
        {
            return true;
        }
        if (node->left == nullptr && node->right == nullptr)
        {
            return true;
        }
        if ((node->left) && (node->right))
        {
            return (isFullt(node->left) && isFullt(node->right));
        }
        return false;
    }
    T successor(T value)
    {
        return successor(this->root, value);
    }
    // Retornar el valor siguiente de "value" en el arbol
    T predecessor(T value)
    {
        return predecessor(this->root, value);
    } // Retornar el valor anterior de "value" en el arbol

    void clear()
    {
        clear(this->root);
    } // Liberar todos los nodos (usar root->KillSelf)

    void buildFromOrderedArray(T *array, int n){
        clear();//limpio root
        this->root=buildFromOrderedArray(array, 0,n-1);

    } // dado un array ordenado construir un arbol binario balanceado

    string displayBFS()
    {
        displayBFS(this->root, BFS_string);
        return BFS_string;
    }
    // Recorrido en anchura (BreadthFirstSearch)
    string displayDFS()
    { // Recorrido en profundidad (DepthFirstSearch)
        string result;
        result = DFS(this->root);
        return result;
    }
    string DFS(NodeBT<T> *node)
    {
        string result;

        if (node == nullptr)
        {
            return result;
        }
        result = result + to_string(node->data);
        result = result + " ";
        DFS(node->left);
        DFS(node->right);

        return result;
    }

    iterator begin(BSTIterator<int>::Type _){
        return iterator(this->root);
    } // Retorna el inicio del iterador
    iterator end(){
        return iterator(nullptr);
    }                           // Retorna el final del iterador


    ~BSTree()
    {
        root->KillSelf();
        root = nullptr;
        delete root;
    } // Destructor del arbol

private:
    // void insert(NodeBT<T>* &node, T value){

    //     if(node == nullptr){
    //         NodeBT<T>* temp = new NodeBT<T>();
    //         temp->data=value;
    //         node=temp;
    //     }
    //     else if(value < node->data)
    //          insert(node->left, value);
    //     else if(value > node->data)
    //          insert(node->right, value);

    // }

    NodeBT<T> *insert(NodeBT<T> *&node, T value)
    {
        if (node == nullptr)
        {
            node = new NodeBT<T>();
            node->data = value;
            node->left = node->right = nullptr;
            return node;
        }
        if (value < node->data)
            return insert(node->left, value);

        if (value > node->data)
            return insert(node->right, value);
        return 0;
    }
    int size(NodeBT<T> *node)
    {
        if (node == NULL)
            return 0;
        return size(node->left) + size(node->right) + 1;
    }

    int height(NodeBT<T> *node)
    {

        // if (node == nullptr)
        //     return 0;
        // int left = height(node->left);
        // int right = height(node->right);
        // if (left > right)
        //     return right + 1;
        // else if (right > left)
        //     return right + 1;
        // return right + 1;
        if (node == nullptr)
            return -1;

        return 1 + max(height(node->left), height(node->right));
    }
    bool isBalanced(NodeBT<T> *node)
    {
        //            int th=0;
        //            int rh=0;
        //            if(node== nullptr){
        //                return true;
        //            }
        //            th=height(node->left);
        //            rh=height(node->right);
        //            if(abs(th-rh)<=1 && isBalanced(node->left) && isBalanced(node->right)){
        //                return 1;
        //            }
        //            return 0;
        // int th = 0;
        // int rh = 0;
        if (node == nullptr)
        {
            return true;
        }
        int th = height(node->left);
        int rh = height(node->right);
        if (abs(th - rh) <= 1 && isBalanced(node->left) && isBalanced(node->right))
        {
            return true;
        }
        return false;
    }
    void displayInOrder(NodeBT<T> *node, string &value)
    {

        if (node == nullptr)
            return;
        displayInOrder(node->left, value);
        value = value + to_string(node->data);
        value = value + " ";
        displayInOrder(node->right, value);
    }
    T minValue(NodeBT<T> *&node)
    {
        // el bst tiene los mayores en la derecha
        NodeBT<T> *temp = node;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return (temp->data);
    }
    T maxValue(NodeBT<T> *&node)
    {
        // el bst tiene los mayores en la derecha
        NodeBT<T> *temp = node;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        return (temp->data);
    }
    NodeBT<T>* Buscar_nodo(NodeBT<T>*root, int data) {
        if(root == NULL) return NULL;
        else if(root->data == data)
            return root;
        else if(root->data < data)
            return Buscar_nodo(root->right,data);
        else
            return Buscar_nodo(root->left,data);
    }
    T successor(NodeBT<T> *&node, T data)
    {
        NodeBT<T>* ubicacion = Buscar_nodo(node,data);//busco el nodo donde esta la data
        if(ubicacion == NULL) return 0;// en caso de no encontrar
        if(ubicacion->right != NULL) {  //todavia se puede recorrer
            if(node == NULL) return 0;
            while(node->left != NULL)
                node = node->left;
            return node->data;
        }
        else {
             NodeBT<T>* successor = NULL;
             NodeBT<T>* temp = node;
            while(temp != ubicacion) {
                if(ubicacion->data < temp->data) {
                    successor = temp;
                    temp = temp->left;
                }
                else
                    temp = temp->right;
            }
            return successor->data;
        }
    }

    T predecessor(NodeBT<T> *&node, T value)
    {
        NodeBT<T> *predecesor = NULL;
        NodeBT<T> *temp = node;
        bool inicio = true;
        while (inicio != false)
        {
            if (value < temp->data)
            {
                temp = temp->left;
            }
            else if (value > temp->data)
            {
                predecesor = temp;
                temp = temp->right;
            }
            else
            {
                if (temp->right)
                {
                    while (predecesor->right != nullptr)
                    {
                        predecesor = predecesor->right;
                    }
                }
                inicio = false;
            }
        }
        return predecesor->data;
    }
    string displayBFS(NodeBT<T> *&node, string &BFS_string)
    {
        queue<NodeBT<T> *> kiu;
        BFS_string = BFS_string + to_string(node->data);
        BFS_string = BFS_string + " ";

        if (node->left != nullptr)
            kiu.push(node->left);
        if (node->right != nullptr)
            kiu.push(node->right);

        while (!kiu.empty())
        {
            NodeBT<T> *aux = kiu.front();
            kiu.pop();
            if (aux->left != nullptr)
                kiu.push(aux->left);
            if (aux->right != nullptr)
                kiu.push(aux->right);
            BFS_string = BFS_string + to_string(aux->data);
            BFS_string = BFS_string + " ";
        }
        return BFS_string;
    }
    void clear(NodeBT<T> *&node)
    {
        root->KillSelf();
        root = nullptr;
    }

    void displayPostOrder(NodeBT<T> *node, string &str)
    {
        if (node == nullptr)
            return;

        // str = str + to_string(node->left->data);
        displayPostOrder(node->left, str);

        // str = str + to_string(node->right->data);
        displayPostOrder(node->right, str);

        str = str + to_string(node->data) + " ";
    }

    NodeBT<T>* buildFromOrderedArray(T *array,int inicio, int size){
        if (inicio > size) //no tendria sentido
            return nullptr;
        int mitad_padre = (inicio + size)/2;
        NodeBT<T> *nodo = new NodeBT<T>(array[mitad_padre]);//entra el padre
        nodo->left = buildFromOrderedArray(array, inicio,mitad_padre - 1);//hijo izquierdo //del 0 al padre
        nodo->right = buildFromOrderedArray(array, mitad_padre + 1, size);//hijo derecho  // del padre al final

        return nodo;
    }
};