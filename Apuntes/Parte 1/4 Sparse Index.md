# Indexamiento secuencial[Sparce Index-Fil]  
Mayormente se usa cuando los datos ya estan ordenados  

Un valor de indice puede asociarse a un grupo de registros, el indice tiene que estar ordenado, ademas los indices puede estar en una sola pagina,  

Para insertar, usamos el encademaiento de datos

Sparse Index-File comparado a Dense Index-file
- Menos espacio y menos costo de mantenimiento para inserciones y eliminaciones.  
- Generalmente más lento que el índice denso para localizar registros.  

Good trade-off:   
- El sparse index con una entrada de índice para cada bloque en el archivo de datos, correspondiente al menor valor de clave de búsqueda en el bloque (etiqueta del bloque).

OJO: Si la pagina ya est lleno, no se puede hacer movimientos con el padre ya que tratamos de archiv, ejemplo si en un b+ esta lleno el hijo se dividia con el padre, en este caso el padre no puede cambiar  ,


Su objetivo es que no tengamos indices muy grandes, 

## Busqueda  

Localizar paginas, indice 1 O(1), indcie 2 O(1), y el indice de datosO(1)

- open archivo, leer y buscar el y realizar la igualacion O(1)  



## Busqueda por rangos  

```
const TAM_PAGE = 512 // bytes : buffer

struct IndexPage {
    // Si 
    T key[M]
    long children[M+1]
    int count
}



struct DataPage {

}
```

Ejemplo:  

index.dat  
```

search('B15')
 [ 0 , 'A02' , 300 , 'A80' , 600 , 'B15' , 900 , 'B30' , 1200.....]

// Tenemos que recorrer hasta un numero menor o igual mas cercano al B15

```  
- Implementacion de la busqueda

```
    const TAM_PAGE = 512

    struct IndexPage{
    T keys[M]-1;//sizeof(T) = 10
    long children[M]; // M capacidad
    
    int count;// cuantas llaves hay
    };
    //M? 27
    struct DataPage{
    Record records[N];//sizeof(Record) = 60
    int count;
    long next;
    };
    //N? 8

    // Localizar
    busca entre las llaves, pero baja a la pagina respectiva

    // linear_search
    busca en la lista de registro y lo iguala

    /* Algoritmo de Busqueda (search_key)
    --------------------
    - Localizar la pagina de indice en el Index1     O(1) */
    open("index1.dat")
    IndexPage page_ind;
    read(page_ind, sizeof(IndexPage))
    pos_fisica = localizar(page_ind, search_key)   

    /* - Localizar la pagina de indice en el Index2     O(1) */
    open("index2.dat")   
    IndexPage page_ind;
    seek(pos_fisica)
    read(page_ind, sizeof(IndexPage))
    pos_fisica = localizar(page_ind, search_key)
    
    /* - Localizar la pagina de datos en el Index3      O(1) */
    open("index3.dat")   
    IndexPage page_ind;
    seek(pos_fisica)
    read(page_ind, sizeof(IndexPage))
    pos_fisica = localizar(page_ind, search_key)

    /* - Leer la pagina de datos y buscar el o los registros  O(1) 
    que coincidan con la Search-key*/
    open("data.dat")
    DataPage page_dat;
    seek(pos_fisica)
    read(page_dat, sizeof(DataPage))
    vector<Record> result = linear_search(page_dat.records, page_dat.count,search_key) 
    //buscar tambien en el overflow page
    return result;

```  

- Implementación de la insercion  

```
 const TAM_PAGE = 512

struct IndexPage{
T keys[M]-1;//sizeof(T) = 10
long children[M]; // M capacidad

int count;// cuantas llaves hay
};
//M? 27
struct DataPage{
Record records[N];//sizeof(Record) = 60
int count;
long next;
};

/* Algoritmo de Insercion (search_key)
    --------------------

//- Localizar la pagina de indice en el Index1     O(1) 
 open("index1.dat")
IndexPage page_ind;
read(page_ind, sizeof(IndexPage))
pos_fisica = localizar(page_ind, search_key)   

/* - Localizar la pagina de indice en el Index2     O(1) */
open("index2.dat")   
IndexPage page_ind;
seek(pos_fisica)
read(page_ind, sizeof(IndexPage))
pos_fisica = localizar(page_ind, search_key)

/* - Localizar la pagina de datos en el Index3      O(1) */
open("index3.dat")   
IndexPage page_ind;
seek(pos_fisica)
read(page_ind, sizeof(IndexPage))
pos_fisica = localizar(page_ind, search_key)

// Insertar
open("data.dat")
DataPage page_dat;
seek(pos_fisica)
read(page_dat, sizeof(DataPage))
void insert(page_dat.records)




/* - Leer la pagina de datos y buscar el o los registros  O(1) 
que coincidan con la Search-key*/
open("data.dat")
DataPage page_dat;
seek(pos_fisica)
read(page_dat, sizeof(DataPage))
vector<Record> result = linear_search(page_dat.records, page_dat.count,search_key) 
//buscar tambien en el overflow page
return result;



```