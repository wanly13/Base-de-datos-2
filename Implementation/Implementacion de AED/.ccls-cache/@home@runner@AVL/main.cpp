#include <iostream>
#include "avl.h"
#include "tester.h"
using namespace std;

int main(int argc, char const *argv[])
{
    AVLTree<int> *avl = new AVLTree<int>();

    avl->insert(35);
    avl->insert(30);
    avl->insert(27);
    avl->insert(11);
    avl->insert(16);
    avl->insert(100);
    avl->insert(50);
    avl->insert(91);
    avl->insert(73);
    avl->insert(5);
    //avl->displayPretty();
    cout<<endl;
    ASSERT(avl->isBalanced() == true, "The avl is not working");
    ASSERT(avl->height() == 3, "The avl is not working");
    ASSERT(avl->getPreOrder() == "30 16 11 5 27 50 35 91 73 100 ", "The avl is not working");

    avl->remove(30);
    avl->remove(35);
    avl->remove(100);
    ASSERT(avl->height() == 2, "The avl is not working");

    ASSERT(avl->getPreOrder() == "27 11 5 16 73 50 91 ", "The avl is not working"); 
    //avl->displayPretty();
    return 0;
}

// #include <chrono>
// #include <cmath>
// #include <ctime>
// #include <iostream>
// #include <vector>
// using namespace std;

// void testIntuitivo(string texto, string patron) {
//   auto start = std::chrono::steady_clock::now();
//   // implementar aqui
//   auto n = texto.size();
//   auto m = patron.size();
//   vector<int> results;
//   for (int j = 0; j!= (n - m)+1; j++) {
//     int i = 0;
//     while (patron[i] == texto[i + j] && i < m) {
//       i++;
//     }
//     if (i == m){
        
    
//       results.push_back(j);
//         }
//   }
    
//   cout << "Resultados ";
//   for (const auto i : results) {
//     cout << i << " ";
//   }
//   cout << endl;

//   auto end = std::chrono::steady_clock::now();
//   cout << "Intuitivo:"
//        << chrono::duration_cast<chrono::microseconds>(end - start).count()
//        << endl;
// }

// int *buildPositions(string patron) {
//   int *positions = new int[256];
//   for (int i = 0; i < 256; i++)
//     positions[i] = -1;
//   for (int i = 0; i < (int)patron.size(); i++)
//     positions[(int)patron[i]] = i;

//   return positions;
// }

// void testBoyerMoore(string texto, string patron) {
//   auto start = std::chrono::steady_clock::now();
//   // implementar aqui
//   auto n = texto.size();
//   auto m = patron.size();
//   int *positions = buildPositions(patron);
//   vector<int> results;
//     int i=0;

//     while(i <= (n - m))
//     {
//         int j = m - 1;
//         while(j >= 0 && patron[j] == texto[i + j])
//             j--;
//         if (j < 0)
//         {
//             results.push_back(i);
            
//             i+= (i + m < n)? m-positions[texto[i + m]] : 1;
//         }
//         else
//             i += max(1, j - positions[texto[i + j]]);
            
//     }

//   cout << "Resultados ";
//   for (const auto i : results) {
//     cout << i << " ";
//   }
//   cout << endl;
//   auto end = std::chrono::steady_clock::now();
//   cout << "Intuitivo:"
//        << chrono::duration_cast<chrono::microseconds>(end - start).count()
//        << endl;
// }

// string generarTexto(int N) {
//   string alfabeto = "   ";
//   for (int i = 'a'; i <= 'z'; i++)
//     alfabeto += (char)i;
//   for (int i = 'A'; i <= 'Z'; i++)
//     alfabeto += (char)i;
//   for (int i = '0'; i <= '9'; i++)
//     alfabeto += (char)i;
//   string result = "";
//   for (int i = 0; i < N; i++)
//     result += alfabeto[(int)rand() % alfabeto.size()];
//   return result;
// }
// int main() {
//   string texto = "estas mi amor, hola como estas";
//   string patron = "estas";
//   testIntuitivo(texto, patron);  // 0,14
//   testBoyerMoore(texto, patron); // 0,14

//   //  srand(time(NULL));
//   // for(int i=2;i<=3;i++){
//   //     int N = pow(10, i);
//   //     string texto = generarTexto(N);
//   //     string patron = generarTexto(10);
//   //     cout<<"-- N:"<<N<<endl;
//   //     //testIntuitivo(texto, patron);//0,14
//   //     testBoyerMoore(texto, patron);//0,14
//   //     cout<<endl;
//   // }
// }