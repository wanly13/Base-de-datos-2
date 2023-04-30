//
// Created by milagros on 4/28/23.
//

#ifndef RECORDLECTURE_RECORD_H
#define RECORDLECTURE_RECORD_H

#endif //RECORDLECTURE_RECORD_H

#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

#define NAME_SIZE 110
#define TYPE_SIZE 8

struct Record{

public:
    int anime_id;
    char name[110];
    char type[8];
    int episodes;
    float rating;
    int members;

    void set_data(){
        string name, type;

        cout << "ID del anime: ";
        cin >> anime_id;

        cout << "Nombre del anime: ";
        getline(cin, name);
        strncpy(this->name, name.c_str(), NAME_SIZE -1);
        this->name[NAME_SIZE - 1] = '\0';

        cout << "Tipo de anime: ";
        getline(cin, type);
        strncpy(this->type, type.c_str(), TYPE_SIZE - 1);
        this->name[TYPE_SIZE - 1] = '\0';

        cout << "Número de episodios: ";
        cin>> episodes;

        cout << "Rating: ";
        cin >> rating;

        cout << "Número de miembros: ";
        cin >> members;

    }
  

};
