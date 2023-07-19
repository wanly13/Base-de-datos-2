[27/04/2023]  
#  Planificacion serializable  

```
Entrada: Grafo de precedencia representado como una lista de adyacencia

Salida: Planificación secuencial equivalente

1. Inicializar un diccionario que contenga el número de predecesores de cada nodo. Para cada nodo en el grafo, inicializar su contador de predecesores en cero.

2. Inicializar una lista vacía para almacenar los nodos disponibles. Para cada nodo en el grafo, si no tiene predecesores, agregarlo a la lista de nodos disponibles.

3. Inicializar una lista vacía para almacenar la planificación secuencial equivalente.

4. Mientras la lista de nodos disponibles no esté vacía, realizar los siguientes pasos:

   a. Seleccionar un nodo disponible de la lista y agregarlo a la planificación secuencial equivalente.

   b. Para cada nodo sucesor del nodo seleccionado, restar uno a su contador de predecesores.

   c. Si el contador de predecesores de un nodo sucesor llega a cero, agregarlo a la lista de nodos disponibles.

   d. Eliminar el nodo seleccionado de la lista de nodos disponibles.

5. Si la lista de planificación secuencial equivalente tiene una longitud menor que el número total de nodos en el grafo, significa que hay ciclos en el grafo y no se puede encontrar una planificación secuencial equivalente. En este caso, el algoritmo debe terminar y mostrar un mensaje de error.

6. Si la lista de planificación secuencial equivalente tiene una longitud igual al número total de nodos en el grafo, significa que se encontró una planificación secuencial equivalente. Devolver la lista de planificación secuencial equivalente.


```

## Verificar que una Planficiacion concurrente es seriezable  
[12:21]  
- Una planificacion serializable tiene conclictos pero no unos conflictos concurrentes  
- un conflicto sucede cuando 2 transacciones diferentes, acceden al mismo recurso con la operacion write.  

## EL grafo de precedencia:  
- Una vez calculado el grafo de precedencia, es serializable cuando no tiene ciclos  


## Bloqueos  
Se usan para modificar la transaccion y convertira  una planificiacion serializable  

TECNICAS  
    - BLoqueo Exclusivo[12:46]:  
        - Se reaaliza una cola, de todos los elementos que quieren acceder a un registro y esperan mientras otra transaccion dea un retorno  

    - BLoqueo Compratido[12:46]:  
        - Se reaaliza una cola, de todos los elementos que quieren acceder a un registro y se crea una copia de lo que se accedio  

    - BLoqueo de Actualizacion[1:00]    
        - Si una transaccion tiene bloqueado con PU(Solo puede tener una )  
