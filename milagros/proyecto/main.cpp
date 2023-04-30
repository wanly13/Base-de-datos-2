#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <cstring>
#include "setavlfile.h"

using namespace std;

int main(){
    AVLFile avl_file;
    read_write_dataset("animedata2.csv", "animedata_avl.dat", avl_file);
    
    read_binary_avl();
}
