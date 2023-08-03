#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define INF 999999 // Utilizado para indicar que no se ha encontrado una ruta válida desde el punto de inicio a un determinado nodo en la matriz. Esta constante se utiliza para representar un valor infinito en el algoritmo de búsqueda de la ruta más corta.
//9999999: infinito para este algoritmo específico.
// Es un valor lo suficientemente grande para representar la infinitud.
// Estructura para representar un nodo en el grafo (celda de la matriz)
struct Nodo {
    int fila;
    int columna;
};
// src representa el nodo (celda) de la matriz desde donde comenzará el algoritmo
// para encontrar la ruta más corta a otros nodos.
// Función para calcular el costo entre dos nodos (celdas adyacentes)
int calcularCosto(int matriz[MAX_ROWS][MAX_COLS], struct Nodo src, struct Nodo dest) {
    return matriz[dest.fila][dest.columna];
}

// Función para encontrar el nodo con menor costo entre los nodos no visitados
struct Nodo encontrarNodoMenorCosto(int dist[MAX_ROWS][MAX_COLS], bool visitado[MAX_ROWS][MAX_COLS], int filas, int columnas) {
    struct Nodo nodoMinimo;
    int costoMinimo = INF;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (!visitado[i][j] && dist[i][j] < costoMinimo) {
                costoMinimo = dist[i][j];
                nodoMinimo.fila = i;
                nodoMinimo.columna = j;
            }
        }
    }

    return nodoMinimo;
}

// Función para verificar si un nodo está dentro de los límites de la matriz
bool esNodoValido(int fila, int columna, int filas, int columnas) {
    return (fila >= 0 && fila < filas && columna >= 0 && columna < columnas);
}

// Función para encontrar la ruta más corta desde el punto A al punto B en la matriz
void rutaMasCorta(int matriz[MAX_ROWS][MAX_COLS], struct Nodo src, struct Nodo dest, int filas, int columnas) {
    int dist[MAX_ROWS][MAX_COLS]; // Matriz para almacenar las distancias mínimas desde el punto A a cada celda
    bool visitado[MAX_ROWS][MAX_COLS]; // Matriz para marcar los nodos visitados

    // Inicializar distancias como infinito e inicializar todos los nodos como no visitados
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            dist[i][j] = INF;
            visitado[i][j] = false;
        }
    }
    // La distancia desde el punto A hacia sí mismo es 0
    dist[src.fila][src.columna] = 0;

    // Encontrar la ruta más corta para todos los nodos
    for (int contador = 0; contador < filas * columnas - 1; contador++) {
        // Obtener el nodo con la distancia mínima entre los nodos no visitados
        struct Nodo u = encontrarNodoMenorCosto(dist, visitado, filas, columnas);
        visitado[u.fila][u.columna] = true;

        // Actualizar las distancias de los nodos adyacentes si es más corto
        struct Nodo v;
        for (int f = -1; f <= 1; f++) {
            for (int c = -1; c <= 1; c++) {
                if ((f == 0 || c == 0) && f != c) {
                    v.fila = u.fila + f;
                    v.columna = u.columna + c;
                    if (esNodoValido(v.fila, v.columna, filas, columnas) && !visitado[v.fila][v.columna]) {
                        int costo = calcularCosto(matriz, u, v);
                        if (dist[u.fila][u.columna] + costo < dist[v.fila][v.columna]) {
                            dist[v.fila][v.columna] = dist[u.fila][u.columna] + costo;
                        }
                    }
                }
            }
        }
    }

    // El costo total de la ruta desde A hasta B
    int costoTotal = dist[dest.fila][dest.columna];

    // Imprimir el costo total de la ruta
    printf("El costo total de la ruta es de: %d\n", costoTotal);

    // Imprimir el resultado de los puntos si hay una ruta válida
    if (costoTotal != INF) {
        printf("Resultado de los puntos:\n");
        struct Nodo actual = dest;
        while (actual.fila != src.fila || actual.columna != src.columna) {
            printf("[%d,%d]->%d\n", actual.fila, actual.columna, matriz[actual.fila][actual.columna]);
            int distanciaMinima = INF;
            struct Nodo siguienteNodo;

            // Buscar el nodo adyacente con la distancia mínima (solo movimientos horizontales o verticales)
            for (int f = -1; f <= 1; f++) {
                for (int c = -1; c <= 1; c++) {
                    if ((f == 0 || c == 0) && f != c) {
                        struct Nodo vecino;
                        vecino.fila = actual.fila + f;
                        vecino.columna = actual.columna + c;
                        if (esNodoValido(vecino.fila, vecino.columna, filas, columnas) && dist[vecino.fila][vecino.columna] < distanciaMinima) {
                            distanciaMinima = dist[vecino.fila][vecino.columna];
                            siguienteNodo = vecino;
                        }
                    }
                }
            }

            actual = siguienteNodo;
        }
        printf("[%d,%d]->%d\n", src.fila, src.columna, matriz[src.fila][src.columna]);
    }
}

int main() {
    int filas, columnas;
    printf("Ingrese el numero de filas de la matriz: ");
    scanf("%d", &filas);
    printf("Ingrese el numero de columnas de la matriz: ");
    scanf("%d", &columnas);

    // Leer la matriz desde la entrada estándar
    int matriz[MAX_ROWS][MAX_COLS];
    printf("Ingrese los elementos de la matriz:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    // Mostrar la matriz ingresada
    printf("Matriz ingresada:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    struct Nodo src, dest;
    printf("Ingrese las coordenadas del punto A fila y columna : ");
    scanf("%d , %d", &src.fila , &src.columna);
    printf("Ingrese las coordenadas del punto B fila y columna: ");
    scanf("%d , %d", &dest.fila, &dest.columna);

    // Verificar si las coordenadas de A y B son válidas
    if (!esNodoValido(src.fila, src.columna, filas, columnas) ||!esNodoValido(dest.fila, dest.columna, filas, columnas)) {
        printf("Coordenadas invalidas para el punto A o el punto B.\n");
        return 1;
    }

    rutaMasCorta(matriz, src, dest, filas, columnas);

    return 0;
}
