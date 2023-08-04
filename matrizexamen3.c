#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define INF 999999

struct Nodo {
    int fila;
    int columna;
};

// Función que calcula el costo entre dos nodos en la matriz.
int calcularCosto(int matriz[MAX_ROWS][MAX_COLS], struct Nodo src, struct Nodo dest) {
    return matriz[dest.fila][dest.columna];
}

// Función que encuentra el nodo con el costo mínimo entre los nodos no visitados.
struct Nodo encontrarNodoMenorCosto(int dist[MAX_ROWS][MAX_COLS], bool visitado[MAX_ROWS][MAX_COLS], int filas, int columnas) {
    struct Nodo nodoMinimo = { -1, -1 };
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

// Función que verifica si un nodo es válido dentro de la matriz.
bool esNodoValido(int fila, int columna, int filas, int columnas) {
    return (fila >= 0 && fila < filas && columna >= 0 && columna < columnas);
}

// Función que imprime la ruta tomada desde el punto A al punto B.
void imprimirRuta(int matriz[MAX_ROWS][MAX_COLS], struct Nodo ruta[MAX_ROWS * MAX_COLS], int contador) {
    for (int i = contador - 1; i >= 0; i--) {
        printf("[%d,%d]->%d\n", ruta[i].fila, ruta[i].columna, matriz[ruta[i].fila][ruta[i].columna]);
    }
}

// Función que encuentra la ruta más corta entre dos puntos en la matriz usando el algoritmo de Dijkstra.
void rutaMasCorta(int matriz[MAX_ROWS][MAX_COLS], struct Nodo src, struct Nodo dest, int filas, int columnas) {
    int dist[MAX_ROWS][MAX_COLS];
    bool visitado[MAX_ROWS][MAX_COLS] = {false};

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            dist[i][j] = INF;
        }
    }

    dist[src.fila][src.columna] = 0;

    for (int contador = 0; contador < filas * columnas - 1; contador++) {
        struct Nodo u = encontrarNodoMenorCosto(dist, visitado, filas, columnas);
        visitado[u.fila][u.columna] = true;

        for (int f = -1; f <= 1; f++) {
            for (int c = -1; c <= 1; c++) {
                if ((f == 0 || c == 0) && f != c) {
                    struct Nodo v = { u.fila + f, u.columna + c };
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

    int costoTotal = dist[dest.fila][dest.columna];

    printf("El costo total de la ruta es de: %d\n", costoTotal);

    if (costoTotal != INF) {
        printf("Resultado de los puntos:\n");
        struct Nodo ruta[MAX_ROWS * MAX_COLS];
        int contador = 0;
        struct Nodo actual = dest;
        while (actual.fila != src.fila || actual.columna != src.columna) {
            ruta[contador++] = actual;
            int distanciaMinima = INF;
            struct Nodo siguienteNodo;

            for (int f = -1; f <= 1; f++) {
                for (int c = -1; c <= 1; c++) {
                    if ((f == 0 || c == 0) && f != c) {
                        struct Nodo vecino = { actual.fila + f, actual.columna + c };
                        if (esNodoValido(vecino.fila, vecino.columna, filas, columnas) && dist[vecino.fila][vecino.columna] < distanciaMinima) {
                            distanciaMinima = dist[vecino.fila][vecino.columna];
                            siguienteNodo = vecino;
                        }
                    }
                }
            }

            actual = siguienteNodo;
        }
        ruta[contador++] = src;
        imprimirRuta(matriz, ruta, contador);
    }
}

int main() {
    int filas, columnas;
    printf("Ingrese el numero de filas de la matriz: ");
    scanf("%d", &filas);
    printf("Ingrese el numero de columnas de la matriz: ");
    scanf("%d", &columnas);

    int matriz[MAX_ROWS][MAX_COLS];
    printf("\nIngrese los elementos de la matriz:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("Matriz ingresada:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    struct Nodo src, dest;
    printf("Ingrese las coordenadas del punto A fila y columna separados por coma: ");
    scanf("%d,%d", &src.fila, &src.columna);
    printf("Ingrese las coordenadas del punto B fila y columna separados por coma: ");
    scanf("%d,%d", &dest.fila, &dest.columna);

    if (!esNodoValido(src.fila, src.columna, filas, columnas) || !esNodoValido(dest.fila, dest.columna, filas, columnas)) {
        printf("Coordenadas invalidas para el punto A o el punto B.\n");
        return 1;
    }

    rutaMasCorta(matriz, src, dest, filas, columnas);

    return 0;
}

