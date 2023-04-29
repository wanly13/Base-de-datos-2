[27/04/2023]  
#  Planificacion serializable  

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
