[13/04/2023]  
# Random [Direct] File Organization[1:07]  
- Los registros no necesitan estar ordenados  
- Usa diccionaros donde guardamos el key y la ubicacion en el registro  [Index.dat], debe ser pequeño que encaje en un pagina de ram(cache)  
## Ventajas  
- Los accesos a la memoria secundaria seria O(1) ya que se buscaria en el indice y una vez encontrada buscarla en la memoria secundaria seria constante  
- Ya no se haria la ordenacion en el archivo completo, sino en el archivo indice por que es mas pequeño  
- Acceso constante, busqueda constante, eliminacion constante, 

## Problemas  
- Cuando un registro pesa mas que el buffer. Para ello usamos el enlazamiento
Un gestor de base de datos, tiene un componente de administracion de Buffers, la mejor forma de escribir es llegando un buffer (empaquetado)  
- Si se apaga el computador se pierde ya que esta en la RAM, se tendria que guardar un archivo aparte para no perder los indices  
- Problema en la capacidad de RAM (cuando el archivo excede la capacidad del ram)  

Numero maximo de registros --- [1:10]  

