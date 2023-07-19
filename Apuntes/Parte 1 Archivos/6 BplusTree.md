# Arbol b+  
- Crece de abajo para arriba  
- es un arbol completo y autobalanceado  
- Es un rabol perfecto(tiene todas sus hojas al mismo nivel)  
- Los datos estan en las hojas[En caso de archivos, los datos estan siempre en el archivo]  
- Soporta busquedas por rango de manera eficiente  


NO optimizable:  
- Si solo se busca una pequeña cantidad en un millon de datos(no es conveniente recurrir a buscar entre el millon para encontrar pocas cantidades)  
-  

En archivos:  
- los indices se manejan en memoria secundaria,  
- Es dinamico, puede seguir creciendo(siempre se aplica split ára implementar la agregacion)  
- Existen 2 tipos de indices:  
    - No agrupado[12:49]:  
        - LAs hojas apuntan a registro en el archivo de datos  
        - Para llegar al nivel de los registros, se requiere mas memoria ya que se indexa todos losregistros es menos rapido
    - Agrupado[12:54]:  
        - LAs hojas apuntan a paginas en el archivo de datos  
        - Es mas rapido debido a que las hojas apunta a paginas la busqueda  


Insercion:  
- Si ahy espacio agrega  
- si no hay espaciio, dividimos en dos, y actualizamos al padre

COmplejidades:  
- Si tiene R entradas (mas compacto)  
- Si tiene R/2 entradas es mas disperso  

Ventajas: 
- Se organiza atumomaticamente al insertar y eliminar  
- No se necesita la reorganizacion del archivo para que funcione  



Deficiencia:  
- Si el indice crece se puede degradar, afecta en la insercicion y eliminacion  
-  
Implementacion codigo: [1:45]