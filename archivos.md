# Archivos  

Longitu variable -> text , csv , 

## sizeof()  
No trae la cantdiad de bytes exactas,  

## Para escribir en un archivo de texto  

```  
struct Record {
    string nombre, apellido;
    int ciclo;
}
Record recor = load()
file << record.nombre << ',';
file << record.apellido << ','
file << toString(record.ciclo) << ','
```  
## Para escribir en un archivo binario  

Se hace ineficiente por la cantidad de viajes a la memoria secundaria, si tiene mas campos, se hace mas viajes a la memoria secundaria

```  
struct Record {
    string nombre, apellido;
    int ciclo;
}
//registros.write((char*)&matricula, sizeo(Matricula)); // no da con solo uno, tiene que ser para cada campo
ofstream file("data.dat" , ios::binary);
Record record = load_from_console()

file.write(record.nombre.c_str(), record.nomrbe.size()); 
file.write(record.carrera.c_str(), record.carrera.size()); 
file.write((char*)&matricula, sizeo(Matricula));


// Forma de escribir todo el registro en un solo buffer
guardar_funcion(){
    // Empaquetar todos los campos en un arrays de bytes
    // se necesita guardar el tamaño del registro

}


Record record = load()
write(record.guardar_funcion() , red.size_bytes())
```  
## Para leer en un archivo binario  

Se hace ineficiente por la cantidad de viajes a la memoria secundaria, si tiene mas campos, se hace mas viajes a la memoria secundaria

```  
// escritura
ofstream file("data.dat" , ios::binary);
Record record = load_from_console()
file.write((char*) record.nomrbe.size() , sizeof(size_t)); 
file.write(record.nombre.c_str(), record.nomrbe.size()); 
file.write(record.carrera.c_str(), record.carrera.size()); 
file.write((char*)&matricula, sizeo(Matricula));


// Lectura
ifstream file("data.dat" , ios::binary);
Record record;
//file.write(record.nombre.c_str(), record.nomrbe.size()); // Como no se declaro nada trae vacio, para caso de archivo binario se necesita el tamaño  [Para esto al hacer load guardamos el tamño]

size_t size_n;// tamaño real del nombre
file.red((char*)&size_n, sizeof(size_t));
char * buffer = new char[size_n]
record.nombre = buffer

-- Para el ciclo
read((char*)&record.ciclo , sizeof(int))

// Forma de leer todo el registro en un solo buffer [1:00pm - 04 - 04 - 2023]
guardar_funcion(){
    // Empaquetar todos los campos en un arrays de bytes
    // se necesita guardar el tamaño del registro
    
}


Record record = load()
write(record.guardar_funcion() , red.size_bytes())
``` 
Para guardar string es necesario guardar su peso ya que pesa diferente de acuerdo a su valor, pero float, inte, es lo mismo   


## PUT || write  
- put : Un byte
- write: Un bufer completo  



## Indicadores de longitud para Variables  

Poner el tamaño de la columna de cada campo  
- El size of ya no es confiable ya que cada registro tiene una cantidad de bytes diferentes  

Tener un archivo para indices  
Desventajas, mas espacio  
ventajas, facil acceso  

# Como eliminar un registroe n longitud variable  
