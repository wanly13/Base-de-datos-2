#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* 
1) Recorremos el arbol y guardamos los grados de entrada de cada nodo (Buscamos el que tiene menor imputs)
2) Luego de haber creado la matris de grados inputs, guardamos en una pila los elementos que tienen menor grado input
3) Recorremos en LIFO los de menor grado, 
    Si: No tiene nada de outputs ->  Agregamos en la lista de secuencia
    si: Si tiene salida de output -> restamos -1 a los elementos quienes apunta 
        4) Si los nodos restados son 0, agregamos al LIFO , y volvemos al paso 3
5) retornamos la lista de secuencias

NO ESTA BLOQUEADO [BLOQCK(X) = 0]
COMPARTIDA [BLOQCK(X) = 1]
EXCLUSIVA [BLOQCK(X) = 2]
ACTUALIZACION [BLOQCK(X) = 3]

Data: ....
Result:  ....
B: if(BLOQCK(X) = 0) { // Acepta por que no esta bloqueado
    BLOQCK(X) <- 1 // Le asignamos que esta bloqueado en compartido
    num_read <- 1; // 
}
else {
    if(BLOQCK(X) = 1) {
        numread <- num_read + 1,
    }
    else {
        wait until( BLOQCK(X) = 0 && iniciamos la transaccion)
        got to B
    }
}




// EJemplo 2
Data: ....
Result: ....

B: if(BLOQCK(X) = 0) { // Acepta porque no está bloqueado
    BLOQCK(X) <- 3 // Le asignamos que está bloqueado en actualización
    num_write <- 1; //
}
else {
    if(BLOQCK(X) = 1 || BLOQCK(X) = 3) { // Esperamos ya que son Exlusivo y update
        wait until(BLOQCK(X) = 0 && iniciamos la transacción)
        got to B
    }
    else { // BLOQCK(X) = 2
        if(num_write = 1){ // Puede compartir (solo una vez)
            num_write <- 1; //
        } else {
            wait until(BLOQCK(X) = 0 && iniciamos la transacción)
            got to B

        }
    }
}
 */
vector<int> planificacion_secuencial(vector<vector<int>>& grafo) {
    vector<int> secuencia;
    int n = grafo.size();
    vector<int> grados_entrada(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grafo[i][j] == 1) {
                grados_entrada[j]++;
            }
        }
    }
    queue<int> tareas_sin_predecesores;
    for (int i = 0; i < n; i++) {
        if (grados_entrada[i] == 0) {
            tareas_sin_predecesores.push(i);
        }
    }
    while (!tareas_sin_predecesores.empty()) {
        int tarea = tareas_sin_predecesores.front();
        tareas_sin_predecesores.pop();
        secuencia.push_back(tarea);
        for (int i = 0; i < n; i++) {
            if (grafo[tarea][i] == 1) {
                grados_entrada[i]--;
                if (grados_entrada[i] == 0) {
                    tareas_sin_predecesores.push(i);
                }
            }
        }
    }
    return secuencia;
}

int main() {
    vector<vector<int>> grafo = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };
    vector<int> secuencia = planificacion_secuencial(grafo);
    for (int i = 0; i < secuencia.size(); i++) {
        cout << secuencia[i] << " ";
    }
    cout << endl;
    return 0;
}
