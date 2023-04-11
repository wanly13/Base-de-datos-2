
Fecha: [11 / 04 / 2023]
- Es mejorar simular la eliminicación y eliminar un elemento cada cierto tiempo  }
- Elimminacion logica: marcar como eliminado

# Tipos de Busqueda  
La mayoria de busquedas se realizan por el valor de un campo  

- Fija: Posicionarnos de manera logica Logica  
- Varialbe: Asociar la llave con su posición real del indice

## Heap File  
Archivo sin índices, 

- No es buena para busqueda para un campo o(n),  
- Se usa donde solo se quiere acceder a la informacion por posicion

Ventajas:  
- Inserción O(n) (Un solo acceso a la memoria secundaria)  

## Busqueda Binaria  
Localizar un registro en un archivo, segun el valor k deseado  
- Es buena para busqeuda de un campo O(log N)
- Update : Buscar O(log N)  

# Secuencia Ordered File Organization  

- PROBLEMA INSERCIÓN:  Cada que se inserta ay que reordenar  
Soluciones:[12:30]  
  
1.- Tener un espacio adicional donde guardemos a los insertados, la inserción se vuelve O(k) , el peor caso es que el auxiliar sea muy grande, la restricción que se haria al espacio auxiliar soporte una cierta cantidad de elementos  
    - Insercion: log(n)[Buscar que no exista] +  O(1)  , O(n*k)[Reconstruir]  
    - Search: O(log N)[Buscar] + O(K) [Buscar archivo auxiliar]   

2.- Mejora en la reconstruccion [Listas Enlazadas], ocupa mas espacio.  Ejm: [12:58]  
- Insercion log(n)[Arriba] + O(k)[Archivo auxiliar]  
- Search : Log (n) [Buscar archivo] + O(k | 1)[Peor caso que recorre todo el archivo, en el mejor caso es que no llegue a recorrer todo el archivo auxiliar]   
- Insert : Search   + O(k)  
- Reconstruir: O(n + k)[Solo recorremos los 2 archivos, se recorre ambas listas]  
- Eliminación[1:19]: Misma que insertar log(n)[Arriba] + O(k)[Archivo auxiliar]     
    Hay punteros que se tiene que modificar, En la reconstruccion ya no se le agrega ya que no se recorre cuando se modifican los punteros, Los punteros son posiciones logicas hacia el registro. 

