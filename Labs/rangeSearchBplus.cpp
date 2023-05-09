vector<Record> rangeSearch (Record& key1,Record& key2 ){
        vector<Record> results;
        std::fstream file(this->filename, std::ios::in|std::ios::out|std::ios::binary | std::ios::app);        

        rangeSearch(file, this->root, key1.cod, key2.cod, results);

        file.close();
        return results;       
} 

void AVLFile::rangeSearch(std::fstream &file ,long& record_pos, char begin_key[5], char end_key[5] , std::vector<Record> &results){
    if (record_pos == -1)
        throw "El archivo se encuentra vacío";

    NodeBT temp;
    file.seekg(record_pos * sizeof(NodeBT)); // Nos ubicamos en el root
    // IMplementar como cin operator
    file.read((char*)&temp, sizeof(NodeBT)); // Leemos el root

    // SI estamos dentro del rango  agregamos 
    if (strcmp(temp.data.cod, begin_key) >= 0 && strcmp(temp.data.cod, end_key) <= 0) {
        results.push_back(temp.data);
    }

    // buscamos por izquierda
    if (strcmp(temp.data.cod, begin_key) > 0) {
        rangeSearch(file, temp.left, begin_key, end_key, results);
    }

    // buscamos por derecha
    if (strcmp(temp.data.cod, end_key) < 0) {
        rangeSearch(file, temp.right, begin_key, end_key, results);
    }
   // strcmp:  0: si ambas cadenas son iguales.
   // Un valor negativo: si la primera cadena es menor que la segunda.
   // Un valor positivo: si la primera cadena es mayor que la segunda.

}