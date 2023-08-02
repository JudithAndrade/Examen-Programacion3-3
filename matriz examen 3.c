#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define INF 999999 //s utilizado para indicar que no se ha encontrado una ruta válida desde el punto de inicio a un determinado nodo en la matriz 
//Esta constante se utiliza para representar un valor infinito en el algoritmo de búsqueda de la ruta más corta

// Estructura para representar un nodo en el grafo (celda de la matriz)
struct Node {
    int row;
    int col;
};

// Función para calcular el costo entre dos nodos (celdas adyacentes)
//src se utiliza para almacenar las coordenadas del punto de inicio desde el cual se desea encontrar la ruta más corta
int calculateCost(int matrix[MAX_ROWS][MAX_COLS], struct Node src, struct Node dest) {
    return matrix[dest.row][dest.col];
}

// Función para encontrar el nodo con menor costo entre los nodos no visitados
struct Node findMinCostNode(int dist[MAX_ROWS][MAX_COLS], bool visited[MAX_ROWS][MAX_COLS], int rows, int cols) {
    struct Node minNode;
    int minCost = INF;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!visited[i][j] && dist[i][j] < minCost) {
                minCost = dist[i][j];
                minNode.row = i;
                minNode.col = j;
            }
        }
    }

    return minNode;
}

// Función para verificar si un nodo está dentro de los límites de la matriz
bool isValidNode(int row, int col, int rows, int cols) {
    return (row >= 0 && row < rows && col >= 0 && col < cols);
}

// Función para encontrar la ruta más corta desde el punto A al punto B en la matriz
void shortestPath(int matrix[MAX_ROWS][MAX_COLS], struct Node src, struct Node dest, int rows, int cols) {
    int dist[MAX_ROWS][MAX_COLS]; // Matriz para almacenar las distancias mínimas desde el punto A a cada celda
    bool visited[MAX_ROWS][MAX_COLS]; // Matriz para marcar los nodos visitados

    // Inicializar distancias como infinito e inicializar todos los nodos como no visitados
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dist[i][j] = INF;
            visited[i][j] = false;
        }
    }

    // La distancia desde el punto A hacia sí mismo es 0
    dist[src.row][src.col] = 0;

    // Encontrar la ruta más corta para todos los nodos
    for (int count = 0; count < rows * cols - 1; count++) {
        // Obtener el nodo con la distancia mínima entre los nodos no visitados
        struct Node u = findMinCostNode(dist, visited, rows, cols);
        visited[u.row][u.col] = true;

        // Actualizar las distancias de los nodos adyacentes si es más corto
        struct Node v;
        for (int r = -1; r <= 1; r++) {
            for (int c = -1; c <= 1; c++) {
                if ((r == 0 || c == 0) && r != c) {
                    v.row = u.row + r;
                    v.col = u.col + c;
                    if (isValidNode(v.row, v.col, rows, cols) && !visited[v.row][v.col]) {
                        int cost = calculateCost(matrix, u, v);
                        if (dist[u.row][u.col] + cost < dist[v.row][v.col]) {
                            dist[v.row][v.col] = dist[u.row][u.col] + cost;
                        }
                    }
                }
            }
        }
    }

    // El costo total de la ruta desde A hasta B
    int totalCost = dist[dest.row][dest.col];

    // Imprimir el costo total de la ruta
    printf("El costo total de la ruta es de: %d\n", totalCost);

    // Imprimir el resultado de los puntos si hay una ruta válida
    if (totalCost != INF) {
        printf("Resultado de los puntos:\n");
        struct Node current = dest;
        while (current.row != src.row || current.col != src.col) {
            printf("[%d,%d]->%d\n", current.row, current.col, matrix[current.row][current.col]);
            int minDist = INF;
            struct Node nextNode;

            // Buscar el nodo adyacente con la distancia mínima (solo movimientos horizontales o verticales)
            for (int r = -1; r <= 1; r++) {
                for (int c = -1; c <= 1; c++) {
                    if ((r == 0 || c == 0) && r != c) {
                        struct Node neighbor;
                        neighbor.row = current.row + r;
                        neighbor.col = current.col + c;
                        if (isValidNode(neighbor.row, neighbor.col, rows, cols) && dist[neighbor.row][neighbor.col] < minDist) {
                            minDist = dist[neighbor.row][neighbor.col];
                            nextNode = neighbor;
                        }
                    }
                }
            }

            current = nextNode;
        }
        printf("[%d,%d]->%d\n", src.row, src.col, matrix[src.row][src.col]);
    }
}

int main() {
    int rows, cols;
    printf("Ingrese el numero de filas de la matriz: ");
    scanf("%d", &rows);
    printf("Ingrese el numero de columnas de la matriz: ");
    scanf("%d", &cols);

    // Leer la matriz desde la entrada estándar
    int matrix[MAX_ROWS][MAX_COLS];
    printf("Ingrese los elementos de la matriz:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    struct Node src, dest;
    printf("Ingrese las coordenadas del punto A (fila columna): ");
    scanf("%d %d", &src.row, &src.col);
    printf("Ingrese las coordenadas del punto B (fila columna): ");
    scanf("%d %d", &dest.row, &dest.col);

    // Verificar si las coordenadas de A y B son válidas
    if (!isValidNode(src.row, src.col, rows, cols) || !isValidNode(dest.row, dest.col, rows, cols)) {
        printf("Coordenadas inválidas para el punto A o el punto B.\n");
        return 1;
    }

    shortestPath(matrix, src, dest, rows, cols);

    return 0;
}