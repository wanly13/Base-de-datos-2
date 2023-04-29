//
// Created by milagros on 4/28/23.
//

#ifndef RECORDLECTURE_SETAVLFILE_H
#define RECORDLECTURE_SETAVLFILE_H

#include "avlfile.h"

istream & operator >> (istream & stream, Record & p)
{
    string campo;
    getline(stream, campo,',');
    p.anime_id = stoi(campo);

    getline(stream, campo,',');
    strncpy(p.name, campo.c_str(), NAME_SIZE -1);
    p.name[NAME_SIZE - 1] = '\0';

    getline(stream, campo,',');
    strncpy(p.type, campo.c_str(), TYPE_SIZE -1);
    p.type[TYPE_SIZE - 1] = '\0';

    getline(stream, campo,',');
    p.episodes = stoi(campo);

    getline(stream, campo, ',');
    p.rating = atof(campo.c_str());

    getline(stream, campo);
    p.members = stoi(campo);

    return stream;
}

ostream & operator << (ostream & stream, Record & p)
{
    stream << p.anime_id << "|";
    stream << p.name << "|";
    stream << p.type << "|";
    stream << p.rating << "|";
    stream << p.members;
    stream << "\n";
    stream << flush;
    return stream;
}


//Crear un archivo para el uso del AVL (con nodes) a partir de los Record del dataset
void read_write_dataset(string filename, string avlfilename, AVLFile avl_file){
    fstream file(filename, ios::in | ios::out);
   // create_file_if_doesnt_exist(avlfilename);
    fstream avlfile(avlfilename, ios::in | ios::out | ios::app | ios::binary);

    if (file.fail()) file_not_found("No se pudo abrir el archivo");
    if (avlfile.fail()) file_not_found("No se pudo abrir el archivo");

    avl_file.set_filename(avlfilename);

    avlfile.seekg(0, ios::end);
    if (avlfile.tellg() == 0){
        Record anime{};
        string line;
        getline(file, line);

        while (getline(file, line)){
            stringstream stream(line);
            stream >> anime;
            
            cout<<anime;
            avl_file.insert(anime);
        }

    }
    else ayudame_Dios("El archivo ya ha sido llenado inicialmente");
    file.close();
}


#endif //RECORDLECTURE_SETAVLFILE_H

